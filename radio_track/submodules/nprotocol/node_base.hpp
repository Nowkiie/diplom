#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <thread>
#include <mutex>
#include <set>
#include <list>
#include <cstdint>
#include "node_event.hpp"
#include "node_active.hpp"
#include "node_detail.hpp"
#include "node_checksum.hpp"
#include "node_defs.hpp"

namespace nc
{
enum class node_state
{
    started,
    stopped,
};

namespace detail
{
constexpr const uint32_t packet_tag = 0x4B414E5A;       //'ZNAK'
constexpr const uint32_t packet_tag_ping = 0x54535953;  //'SYST'
//размер буфера сокета
constexpr const uint32_t default_buffer_size = 65536 * 8;
//интервал зодирования сети (мс)
constexpr const uint32_t zond_timer_interval = 5000;
//интервал поиска узлов (мс)
constexpr const uint32_t enumerate_interval = 60000;
//размер принимаемой udp датаграммы
constexpr const uint32_t packet_length = 65536;

//порт службы разрешения имён
constexpr const port_t resolver_service_port = 781;

//максимальный размер строки имени узла
constexpr const int max_name_size = 255;

// интервал ожидания для поиска (мс)
constexpr const int find_serves_timeout = 400;

#pragma pack(push, 1)
struct packet_header
{
    uint32_t tag;         //packet_tag
    uint32_t size;        //размер данных
    message_type_t type;  //тип сообщения
    uint32_t checksum;    //контрольная сумма
};
struct enumerator_packet
{
    uint32_t tag;                    //тег
    uint64_t record_key;             //уникальный ключ записи
    uint16_t port;                   //номер порта
    char point_name[max_name_size];  // имя узла
    uint8_t category;                // тип узла
};
#pragma pack(pop)

}  // namespace detail

class node_base
{
public:
    node_base()
        : state_{node_state::stopped}
    {
    }
    // остановить обработку
    void stop()
    {
        auto expected = node_state::started;
        if (state_.compare_exchange_strong(expected, node_state::stopped))
        {
            node_event lock;

            service_->dispatch(
                [&lock, this]()
                {
                    close_all();
                    lock.notify();
                });

            lock.wait();
            service_->stop();
            if (async_thread_.joinable())
            {
                async_thread_.join();
            }
            result_thread_.stop();
            pending_connections_.clear();
            connections_.clear();
            acceptor_.reset();
            // деинициализация родительского класса
            deinit();

            io_work_.reset();
            service_.reset();
        }
    }
    // запустить внутренние потоки обработки
    void start()
    {
        auto expected = node_state::stopped;
        if (state_.compare_exchange_strong(expected, node_state::started))
        {
            service_ = std::make_unique<boost::asio::io_service>();
            io_work_ =
                std::make_unique<boost::asio::io_service::work>(*service_);
            result_thread_.start();

            async_thread_ = std::thread(
                [this]()
                {
                    try
                    {
                        boost::system::error_code errc;
                        service_->run(errc);
                    }
                    catch (...)
                    {
                        // при возникновении непонятных ошибок закрываем все подключения
                        close_all();
                        service_->stop();
                    }
                });
            // инициализация вышестоящего класса
            init();
        }
    }
    // выполнить в потоке возврата результатов
    template <typename Callback>
    void post(Callback&& cb)
    {
        result_thread_.send(cb);
    }

protected:
    boost::asio::io_service& service()
    {
        return *service_;
    }
    // выполнить в потоке service
    template <typename Callback>
    void dispatch(Callback&& cb)
    {
        service_->dispatch(cb);
    }
    // подключить к узлу (возможно несколько путей с разными адресами)
    void start_connection(point_id_t id, address_t address, port_t port)
    {
        if (connections_.count(id))
        {
            return;
        }

        if (pending_connections_.count(id) != 0)
        {
            pending_connections_.at(id).addrlist.insert({address, port});
        }
        else
        {
            pending_connections_.insert({id, {}});
            pending_connections_.at(id).addrlist.insert({address, port});
            start_connection_internal(id, address, port);
        }
    }
    // запуск приёма внешних подключений
    void start_accept()
    {
        std::shared_ptr<boost::asio::ip::tcp::socket> s =
            std::make_shared<boost::asio::ip::tcp::socket>(service());

        auto endpoint = std::make_shared<boost::asio::ip::tcp::endpoint>();
        acceptor_->async_accept(
            *s, *endpoint,
            [endpoint, s, this](boost::system::error_code errc)
            {
                if (errc)
                {
                    return;
                }
                setup_socket(*s);
                address_t address = endpoint->address().to_v4().to_ulong();
                port_t port = endpoint->port();

                auto id = generate_free_key();
                active_connection connection{};
                connection.socket = s;
                connections_.insert({id, connection});

                connected(id, address, port);

                start_receive(id);
                start_accept();
            });
    }
    point_id_t generate_free_key()
    {
        point_id_t result = generate_random_key();
        while (pending_connections_.count(result) || connections_.count(result))
        {
            result = generate_random_key();
        }
        return result;
    }
    point_id_t generate_random_key()
    {
        auto accuracy_time = std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count();
        auto system_time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch())
            .count();

        return system_time ^ (accuracy_time % 10000) ^ rand();
    }
    bool start_send(point_id_t id, message_type_t type, queue_buffer_t stoarge)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            return false;
        }
        queued_message item;
        item.size = static_cast<uint32_t>(stoarge->size());
        item.buffer = std::move(stoarge);
        item.type = type;
        iter->second.send_queue.push_back(std::move(item));
        start_send_queue(id);
        return true;
    }
    port_t acceptor_init(port_t port = 0)
    {
        boost::system::error_code errc;
        acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(service());
        acceptor_->open(boost::asio::ip::tcp::v4(), errc);
        if (errc)
        {
            return {};
        }

        acceptor_->bind(
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port),
            errc);
        if (errc)
        {
            return {};
        }
        acceptor_->listen(boost::asio::socket_base::max_connections, errc);
        if (errc)
        {
            return {};
        }
        port_t server_port = acceptor_->local_endpoint(errc).port();
        if (errc)
        {
            return {};
        }
        return server_port;
    }
    node_state state() const
    {
        return state_;
    }

private:
    virtual void connected(point_id_t id, address_t address, port_t port) = 0;
    virtual void disconnected(point_id_t id) = 0;
    virtual void message(point_id_t id, message_type_t type,
                         queue_buffer_t store) = 0;
    virtual void init() = 0;
    virtual void deinit() = 0;

    void start_receive(point_id_t id)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            return;
        }

        auto header = std::make_shared<detail::packet_header>();

        boost::asio::async_read(
            *iter->second.socket,
            boost::asio::buffer(reinterpret_cast<char*>(header.get()),
                                sizeof(detail::packet_header)),
            [header, id, this](boost::system::error_code errc,
                               std::size_t /*size*/)
            {
                if (errc)
                {
                    close_connection(id);
                    return;
                }
                bool is_data = header->tag == detail::packet_tag;
                bool is_ping = header->tag == detail::packet_tag_ping;
                if (!is_data && !is_ping)
                {
                    close_connection(id);
                    return;
                }
                start_receive_data(id, header->type, header->size, is_data);
            });
    }

    void start_receive_data(point_id_t id, message_type_t type, uint32_t size,
                            bool is_data)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            return;
        }
        auto data = std::make_shared<std::vector<char>>(size);

        boost::asio::async_read(
            *iter->second.socket,
            boost::asio::buffer(data->data(), data->size()),
            [type, id, data, is_data, this](boost::system::error_code errc,
                                            std::size_t /*size*/)
            {
                if (errc)
                {
                    close_connection(id);
                    return;
                }
                if (is_data)
                {
                    message(id, type, data);
                }
                start_receive(id);
            });
    }

    void start_connection_internal(point_id_t id, address_t address,
                                   port_t port)
    {
        auto s = std::make_shared<boost::asio::ip::tcp::socket>(service());

        auto boost_ip = boost::asio::ip::address_v4(address);
        auto endpoint = boost::asio::ip::tcp::endpoint(boost_ip, port);

        s->async_connect(
            endpoint,
            [this, id, address, port, s](boost::system::error_code errc)
            {
                if (errc)
                {
                    //ошибка подключения
                    auto pending_iter = pending_connections_.find(id);
                    if (pending_iter != pending_connections_.end())
                    {
                        pending_connection& connection = pending_iter->second;
                        connection.blacklist.insert({address, port});
                        for (const auto p : connection.addrlist)
                        {
                            if (connection.blacklist.count(p) == 0)
                            {
                                start_connection_internal(id, p.first,
                                                          p.second);
                                return;
                            }
                        }
                        // не нашли альтернатив подключения, удаляем из списка
                        pending_connections_.erase(pending_iter);
                    }
                    return;
                }
                setup_socket(*s);
                active_connection c{};
                c.socket = s;
                connections_.insert({id, c});
                pending_connections_.erase(id);
                connected(id, address, port);
                start_receive(id);
            });
    }

    // отправка данных из очереди
    void start_send_queue(point_id_t id)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            return;
        }
        active_connection& connection = iter->second;
        if (connection.sending_flag)
        {
            // уже производится отправка
            return;
        }
        if (connection.send_queue.empty())
        {
            // нечего отправлять
            return;
        }

        connection.sending_flag = true;

        auto item = connection.send_queue.front();
        iter->second.send_queue.pop_front();

        async_send(
            id, item.type, item.buffer->data(), item.size,
            [item, id, this](bool)
            {
                auto iter = connections_.find(id);
                if (iter != connections_.end())
                {
                    active_connection& connection = iter->second;
                    connection.sending_flag = false;
                    start_send_queue(id);
                }
            });
    }
    // отправка данных, *data должен существовать до завершения операции
    template <typename Callback>
    void async_send(point_id_t id, message_type_t type, const void* data,
                    uint32_t size, Callback&& handler)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            handler(false);
            return;
        }

        auto header = std::make_shared<detail::packet_header>();
        header->tag = detail::packet_tag;
        header->size = size;
        header->type = type;
        header->checksum = adler32mod(static_cast<const uint8_t*>(data), size);

        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(
            boost::asio::buffer(reinterpret_cast<char*>(header.get()),
                                sizeof(detail::packet_header)));
        if (size > 0)
        {
            buffers.push_back(boost::asio::buffer(data, size));
        }

        boost::asio::async_write(
            *iter->second.socket, buffers,
            [handler, header = std::move(header)](
                const boost::system::error_code& errc,
                std::size_t /*bytes_transferred*/)
            {
                handler(!errc);
            });
    }

    void close_all()
    {
        boost::system::error_code errc;
        // останавливаем принятие подключений
        if (acceptor_)
        {
            acceptor_->close(errc);
        }
        // сообщаем об отключении всех подключенных узлов
        while (!connections_.empty())
        {
            close_connection(connections_.begin()->first);
        }
    }

    void close_connection(point_id_t id)
    {
        auto iter = connections_.find(id);
        if (iter == connections_.end())
        {
            return;
        }
        boost::system::error_code errc;
        iter->second.socket->close(errc);
        auto socket = std::move(iter->second);
        disconnected(id);
        connections_.erase(iter);
        service_->poll();
    }
    void setup_socket(boost::asio::ip::tcp::socket& s)
    {
        using namespace boost::asio;
        boost::system::error_code errc;
        // нужно ли?
        s.set_option(boost::asio::ip::tcp::no_delay(true), errc);

        s.set_option(socket_base::send_buffer_size(detail::default_buffer_size),
                     errc);
        s.set_option(
            socket_base::receive_buffer_size(detail::default_buffer_size),
            errc);
        s.set_option(socket_base::keep_alive(true), errc);

        detail::set_keepalive_interval(s.native_handle(),
                                       detail::zond_timer_interval);
    }

    struct queued_message
    {
        queue_buffer_t buffer;
        uint32_t size;
        message_type_t type;
    };
    struct pending_connection
    {
        std::set<std::pair<address_t, port_t>> blacklist;
        std::set<std::pair<address_t, port_t>> addrlist;
    };
    struct active_connection
    {
        std::shared_ptr<boost::asio::ip::tcp::socket> socket;
        std::list<queued_message> send_queue;
        bool sending_flag;
    };

    std::unique_ptr<boost::asio::io_service> service_;
    std::unique_ptr<boost::asio::io_service::work> io_work_;

    std::map<point_id_t, pending_connection> pending_connections_;
    std::map<point_id_t, active_connection> connections_;

    // for server
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;

    std::atomic<node_state> state_;

    // поток для asio
    std::thread async_thread_;

    // поток для возврата результатов
    node_active result_thread_;
};

}  // namespace nc
