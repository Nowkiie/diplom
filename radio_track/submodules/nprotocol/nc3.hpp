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
#include <condition_variable>
#include <set>
#include <unordered_set>
#include <queue>
#include <atomic>
#include <cstdint>
#include <iostream>
#include "node_base.hpp"
#include "node_address.hpp"
#include "serializer.hpp"
#include "node_logger.hpp"

namespace nc3
{
using nc::address_t;
using nc::message_type_t;
using nc::node_state;
using nc::point_id_t;
using nc::port_t;
using nc::queue_buffer_t;

namespace detail
{
using namespace nc::detail;

enum node_category
{
    node_local = 0,   // локальный узел
    node_global = 1,  // глобальный узел
    node_remote = 2,  // удалённый узел
};

}  // namespace detail

enum class node_type
{
    undefined,
    local_client,
    local_server,
    global_client,
    global_server,
    host_client,
    host_server,
};

namespace detail
{
//сконвертировать код сообщения nc3 из кода протокола и кода сообщения
template <unsigned int ProtocolCode, unsigned int MessageCode>
static message_type_t convert_message()
{
    //проверка на выход за границы
    constexpr auto ushort_max = std::numeric_limits<unsigned short>::max();
    static_assert(MessageCode <= ushort_max && ProtocolCode <= ushort_max,
                  "invalid message code");

    return static_cast<message_type_t>(ProtocolCode) << 16
           | static_cast<message_type_t>(MessageCode);
}

}  // namespace detail

constexpr int node_current_version = 1;

using nc::address_to_string;

inline std::string address_to_string(address_t address, port_t port)
{
    return address_to_string(address) + ":" + std::to_string(port);
}

using nc::node_active;
using nc::node_event;

class node : public nc::node_base
{
public:
    using point_id_type = point_id_t;

    node(node_type type, const std::string& node_name)
        : type_{type}
        , category_{}
        , host_node_{false}
        , node_name_{node_name}
        , server_port_{}
        , server_key_{}
    {
        if (detail::is_log_enabled())
        {
            // создаём лог при необходимости
            logger_ = std::make_unique<nc::node_logger>(node_name);
        }

        if (type_ == node_type::host_server || type_ == node_type::host_client)
        {
            // узел взаимодействует только внутри хоста
            host_node_ = true;
        }

        // обработчик сообщения о регистрации
        message_handlers_.insert(
            std::make_pair(
                0, [this](point_id_t id, const void* data, size_t size)
                {
                    try
                    {
                        std::vector<unsigned short> remote_supported_protocols;
                        std::vector<message_type_t> remote_supported_messages;
                        int remote_version{};

                        serializer::memory_istream_archive ia(data, size);
                        serializer::serialize(ia, remote_supported_protocols);
                        serializer::serialize(ia, remote_supported_messages);
                        serializer::serialize(ia, remote_version);

                        auto iter = connections_.find(id);
                        if (iter == connections_.end())
                        {
                            return;
                        }
                        for (const auto msg : remote_supported_messages)
                        {
                            iter->second.remote_supported_messages.insert(msg);
                        }
                        for (const auto prot : remote_supported_protocols)
                        {
                            iter->second.remote_supported_protocols.insert(
                                prot);
                        }
                        iter->second.notify_connected = true;

                        if (logger_)
                        {
                            logger_->connected(id, iter->second.address);
                        }

                        point_connected(id, iter->second.address,
                                        iter->second.port);
                    }
                    catch (...)
                    {
                    }  //игнорируем неверные сообщения
                }));
    }
    ~node()
    {
        stop();
    }

    // отправка сообщний
    template <typename Message>
    bool send(point_id_t id, const Message& message)
    {
        auto stoarge = serialize(message);

        if (stoarge->size() >= std::numeric_limits<uint32_t>::max())
        {
            return false;
        }

        if (state() != node_state::started)
        {
            return false;
        }

        if (logger_)
        {
            logger_->outgoing(id, Message::message, message);
        }

        dispatch(
            [this, id, stoarge = std::move(stoarge)]()
            {
                message_type_t msg_type =
                    detail::convert_message<Message::protocol,
                                            Message::message>();
                start_send(id, msg_type, stoarge);
            });
        return true;
    }

    // регистрация обработчиков (выполнять до вызова start)
    template <typename... Messages, typename Handler>
    void register_handler(Handler* handler)
    {
        if constexpr (sizeof...(Messages) != 0)
        {
            (register_handler_internal<Messages>(handler), ...);
        }
        register_interface_connected(handler);
        register_interface_disconnected(handler);
    }

    template <typename Message>
    bool check_message(point_id_t id)
    {
        const auto message_type =
            detail::convert_message<Message::protocol, Message::message>();
        return check_message_raw(id, message_type);
    }

    // поиск серверов в сети (для предотвращения повторного запуска)
    static std::vector<std::pair<address_t, port_t>> check_servers(
        const std::string& node_name)
    {
        std::set<std::pair<address_t, port_t>> servers;
        {
            node n(node_type::undefined, node_name);
            n.start();
            n.start_process_enumerator_messages(
                [&](const detail::enumerator_packet* packet, address_t address)
                {
                    if (packet->port)
                    {
                        if (node_name == packet->point_name
                            && (packet->category == detail::node_global
                                || packet->category == detail::node_local))
                        {
                            servers.insert({address, packet->port});
                        }
                    }
                });
            // запрос на поиск
            n.send_enumerator_record(0, 0, detail::node_local, node_name);
            std::this_thread::sleep_for(
                std::chrono::milliseconds(detail::find_serves_timeout));
        }
        std::vector<std::pair<address_t, port_t>> result;
        for (const auto pair : servers)
        {
            result.push_back(pair);
        }
        return result;
    }

    static std::string local_host_name()
    {
        boost::system::error_code errc;
        return boost::asio::ip::host_name(errc);
    }

protected:
    bool send_raw(point_id_t id, message_type_t msg_type, const void* data,
                  size_t size)
    {
        auto stoarge = std::make_shared<std::vector<char>>(size);
        memcpy(stoarge->data(), data, size);

        if (state() != node_state::started)
        {
            return false;
        }

        if (logger_)
        {
            uint16_t message_id = msg_type;
            logger_->outgoing(id, message_id, data, size);
        }

        dispatch(
            [this, id, msg_type, stoarge = std::move(stoarge)]()
            {
                start_send(id, msg_type, stoarge);
            });
        return true;
    }
    template <typename Handler>
    void register_raw_handler(const std::vector<message_type_t>& message_types,
                              Handler* handler)
    {
        for (const auto message_type : message_types)
        {
            register_raw_handler_internal(message_type, handler);
        }
        register_interface_connected(handler);
        register_interface_disconnected(handler);
    }
    bool check_message_raw(point_id_t id, message_type_t message_type)
    {
        if (state() != node_state::started)
        {
            return false;
        }
        node_event event;
        bool result{};
        dispatch(
            [&event, &result, id, message_type, this]()
            {
                auto iter = connections_.find(id);
                if (iter != connections_.end())
                {
                    result = iter->second.remote_supported_messages.count(
                                 message_type)
                             > 0;
                }
                event.notify();
            });
        event.wait();
        return result;
    }

private:
    void connected(point_id_t id, address_t address, port_t port) final
    {
        connection new_connection{};
        new_connection.address = address;
        new_connection.port = port;
        connections_.insert({id, new_connection});

        //сообщение о регистрации
        std::shared_ptr<std::vector<char>> stoarge =
            std::make_shared<std::vector<char>>();

        std::vector<unsigned short> supported_protocols;
        std::vector<message_type_t> supported_messages;
        int version = node_current_version;

        std::copy(local_supported_protocols_.begin(),
                  local_supported_protocols_.end(),
                  std::back_inserter(supported_protocols));
        std::copy(local_supported_messages_.begin(),
                  local_supported_messages_.end(),
                  std::back_inserter(supported_messages));

        serializer::vector_ostream_archive oa(*stoarge);
        serializer::serialize(oa, supported_protocols);
        serializer::serialize(oa, supported_messages);
        serializer::serialize(oa, version);

        start_send(id, 0, std::move(stoarge));
    }
    void disconnected(point_id_t id) final
    {
        auto iter = connections_.find(id);
        if (iter != connections_.end())
        {
            if (iter->second.notify_connected)
            {
                if (logger_)
                {
                    logger_->disconnected(id);
                }
                point_disconnected(id);
            }
            connections_.erase(iter);
        }
    }
    void message(point_id_t id, message_type_t type, queue_buffer_t store) final
    {
        uint32_t size = static_cast<uint32_t>(store->size());
        point_message(id, type, store->data(), size);
    }
    void init() final
    {
        boost::asio::ip::address_v4 recv_address =
            boost::asio::ip::address_v4::any();

        recv_socket_ = make_udp_socket(
            service(), boost::asio::ip::udp::endpoint(
                           recv_address, detail::resolver_service_port));

        query_timer_ = std::make_unique<boost::asio::deadline_timer>(service());

        // задание категории узла (передаётся в пакете поиска)
        switch (type_)
        {
            case node_type::local_client:
            case node_type::host_client:
                category_ = detail::node_local;
                start_client();
                break;
            case node_type::local_server:
            case node_type::host_server:
                category_ = detail::node_local;
                start_server();
                break;
            case node_type::global_client:
                category_ = detail::node_global;
                start_client();
                break;
            case node_type::global_server:
                category_ = detail::node_global;
                start_server();
                break;
            case node_type::undefined:
                break;
        }
    }
    void deinit() final
    {
        connections_.clear();
        recv_socket_.reset();
        udp_sockets_.clear();
        query_timer_.reset();
        server_port_ = 0;
        server_key_ = 0;
    }
    template <typename Message>
    inline queue_buffer_t serialize(const Message& message)
    {
        uint32_t archive_size{};
        serializer::archive_versioned<serializer::size_calculator> calc_archive(
            archive_size);
        serializer::serialize(calc_archive, message);
        auto stoarge = std::make_shared<std::vector<char>>();
        stoarge->reserve(archive_size);
        serializer::serialize(serializer::vector_ostream_archive(*stoarge),
                              message);
        return stoarge;
    }

    void start_client()
    {
        start_resend_query_loop();
        start_process_enumerator_messages(
            [this](const detail::enumerator_packet* packet, address_t address)
            {
                if (detail::ip_ignored(address))
                {
                    return;
                }

                //ответ на поиск
                if ((category_ == detail::node_local
                     && packet->category != detail::node_remote)
                    || category_ == detail::node_global)
                {
                    if (packet->port != 0 && node_name_ == packet->point_name)
                    {
                        start_connection(packet->record_key, address,
                                         packet->port);
                    }
                }
            });
    }

    void start_server()
    {
        server_key_ = generate_random_key();

        server_port_ = acceptor_init();

        if (server_port_ == 0)
        {
            return;
        }

        // иформируем клиента - на случай если сервер запущен позже чем клиент
        send_enumerator_record(server_key_, server_port_, category_,
                               node_name_);
        start_process_enumerator_messages(
            [this](const detail::enumerator_packet* packet, address_t address)
            {
                if (detail::ip_ignored(address))
                {
                    return;
                }
                // пакет поиска
                if ((category_ == detail::node_local
                     && packet->category != detail::node_remote)
                    || category_ == detail::node_global)
                {
                    if (server_port_ && packet->port == 0
                        && node_name_ == packet->point_name)
                    {
                        send_enumerator_record(server_key_, server_port_,
                                               category_, node_name_);
                    }
                }
            });
        start_accept();
    }

    static std::unique_ptr<boost::asio::ip::udp::socket> make_udp_socket(
        boost::asio::io_service& service,
        boost::asio::ip::udp::endpoint endpoint)
    {
        boost::system::error_code errc;
        auto socket_ = std::make_unique<boost::asio::ip::udp::socket>(service);
        socket_->open(boost::asio::ip::udp::v4(), errc);
        socket_->set_option(boost::asio::socket_base::broadcast(true), errc);
        //разрешаем использовать сокет нескольким программам
        socket_->set_option(boost::asio::socket_base::reuse_address(true),
                            errc);
        socket_->bind(endpoint, errc);
        if (errc)
        {
            std::cerr << "nc3 bind error: " << errc.message()  << std::endl;
        }
        return socket_;
    }

    void send_enumerator_record(uint64_t record_key, port_t port,
                                uint8_t category, const std::string& point_name)
    {
        detail::enumerator_packet packet{};
        packet.record_key = record_key;
        packet.port = port;
        packet.tag = detail::packet_tag;
        packet.category = category;
        std::memcpy(packet.point_name, point_name.c_str(),
                    std::min(sizeof(packet.point_name) - 1, point_name.size()));
        send_enumerator_to_all(&packet, sizeof(detail::enumerator_packet));
    }

    static std::vector<address_t> get_local_ips()
    {
        return detail::get_local_ips();
    }

    bool send_enumerator_to_all(const void* data, size_t size)
    {
        boost::system::error_code errc;
        std::vector<address_t> ips;
        if (host_node_)
        {
            ips.push_back(boost::asio::ip::address_v4::loopback().to_ulong());
        }
        else
        {
            ips = get_local_ips();
        }

        for (const auto& ip : ips)
        {
            if (detail::ip_ignored(ip))
            {
                continue;
            }

            if (udp_sockets_.count(ip) == 0)
            {
                udp_sockets_.insert(
                    {ip, make_udp_socket(service(),
                                         boost::asio::ip::udp::endpoint(
                                             boost::asio::ip::address_v4(ip),
                                             detail::resolver_service_port))});
            }
            if (size != 0)
            {
                udp_sockets_.at(ip)->send_to(
                    boost::asio::buffer(static_cast<const char*>(data), size),
                    boost::asio::ip::udp::endpoint(
                        boost::asio::ip::address_v4::broadcast(),
                        detail::resolver_service_port),
                    0, errc);
            }
        }
        return true;
    }

    void start_resend_query_loop()
    {
        send_enumerator_record(0, 0, category_, node_name_);
        query_timer_->expires_from_now(
            boost::posix_time::milliseconds(detail::enumerate_interval));
        query_timer_->async_wait(
            [this](boost::system::error_code errc)
            {
                if (errc)
                {
                    return;
                }
                start_resend_query_loop();
            });
    }
    template <typename Callback>
    void start_process_enumerator_messages(Callback&& cb)
    {
        auto packet_data =
            std::make_shared<std::vector<char>>(detail::packet_length);
        std::memset(packet_data->data(), 0, detail::packet_length);
        auto endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(
            boost::asio::ip::address_v4::any(), detail::resolver_service_port);

        recv_socket_->async_receive_from(
            boost::asio::buffer(packet_data->data(), detail::packet_length),
            *endpoint,
            [this, packet_data, endpoint, cb = std::forward<Callback>(cb)](
                boost::system::error_code errc, std::size_t)
            {
                if (errc)
                {
                    return;
                }

                if (host_node_
                    && endpoint->address().to_v4()
                           != boost::asio::ip::address_v4::loopback())
                {
                    start_process_enumerator_messages(cb);
                    return;
                }

                const auto* packet =
                    reinterpret_cast<const detail::enumerator_packet*>(
                        packet_data->data());

                if (packet->tag == detail::packet_tag)
                {
                    cb(packet, endpoint->address().to_v4().to_ulong());
                }
                start_process_enumerator_messages(cb);
            });
    }

    void point_connected(point_id_t id, address_t address, port_t port)
    {
        for (const auto& handler : interface_handler_connected_)
        {
            handler(id, address, port);
        }
    }

    void point_disconnected(point_id_t id)
    {
        for (const auto& handler : interface_handler_disconnected_)
        {
            handler(id);
        }
    }

    void point_message(point_id_t id, message_type_t type, const void* data,
                       uint32_t size)
    {
        auto range = message_handlers_.equal_range(type);
        for (auto iter = range.first; iter != range.second; ++iter)
        {
            iter->second(id, data, size);
        }
    }

    template <typename Message, typename Handler>
    void register_handler_internal(Handler* handler)
    {
        auto message_type =
            detail::convert_message<Message::protocol, Message::message>();

        local_supported_messages_.insert(message_type);
        local_supported_protocols_.insert(Message::protocol);

        message_handlers_.insert(
            std::make_pair(
                message_type,
                [handler, this](point_id_t id, const void* data, size_t size)
                {
                    try
                    {
                        Message decoded_message{};

                        serializer::serialize(
                            serializer::memory_istream_archive(data, size),
                            decoded_message);

                        if (logger_)
                        {
                            logger_->incoming(id, Message::message,
                                              decoded_message);
                        }

                        post(
                            [handler, id,
                             decoded_message = std::move(decoded_message)]()
                            {
                                handler->message(id,
                                                 std::move(decoded_message));
                            });
                    }
                    catch (...)
                    {
                    }  //игнорируем неверные сообщения
                }));
    }
    template <typename Handler>
    void register_raw_handler_internal(message_type_t message_type,
                                       Handler* handler)
    {
        local_supported_messages_.insert(message_type);
        local_supported_protocols_.insert(message_type >> 16);

        message_handlers_.insert(
            std::make_pair(
                message_type, [handler, message_type, this](
                                  point_id_t id, const void* data, size_t size)
                {
                    try
                    {
                        if (logger_)
                        {
                            uint16_t message_code = message_type;
                            logger_->incoming(id, message_code, data, size);
                        }
                        auto stoarge =
                            std::make_shared<std::vector<char>>(size);
                        memcpy(stoarge->data(), data, size);
                        post(
                            [handler, id, message_type,
                             stoarge = std::move(stoarge)]()
                            {
                                handler->message(id, message_type,
                                                 stoarge->data(),
                                                 stoarge->size());
                            });
                    }
                    catch (...)
                    {
                    }  //игнорируем неверные сообщения
                }));
    }
    template <typename Handler>
    void register_interface_connected(Handler* handler)
    {
        interface_handler_connected_.push_back(
            [handler, this](point_id_t id, address_t address, port_t port)
            {
                post(
                    [handler, id, address, port]()
                    {
                        handler->connected(id, address, port);
                    });
            });
    }

    template <typename Handler>
    void register_interface_disconnected(Handler* handler)
    {
        interface_handler_disconnected_.push_back(
            [handler, this](point_id_t id)
            {
                post(
                    [handler, id]()
                    {
                        handler->disconnected(id);
                    });
            });
    }

    struct connection
    {
        bool notify_connected;
        std::set<message_type_t> remote_supported_messages;
        std::set<unsigned short> remote_supported_protocols;
        address_t address;
        port_t port;
    };

    node_type type_;
    uint8_t category_;
    bool host_node_;

    std::string node_name_;

    std::unique_ptr<nc::node_logger> logger_;

    //for enumerator
    std::unique_ptr<boost::asio::ip::udp::socket> recv_socket_;
    std::map<address_t, std::unique_ptr<boost::asio::ip::udp::socket>>
        udp_sockets_;

    // for client
    std::unique_ptr<boost::asio::deadline_timer> query_timer_;

    // for server
    port_t server_port_;
    point_id_t server_key_;

    std::map<point_id_t, connection> connections_;

    typedef void(message_handler_t)(point_id_t id, const void* data,
                                    size_t size);
    typedef void(socket_connected_t)(point_id_t id, address_t address,
                                     port_t port);
    typedef void(socket_disconnected_t)(point_id_t id);

    std::vector<std::function<socket_connected_t>> interface_handler_connected_;
    std::vector<std::function<socket_disconnected_t>>
        interface_handler_disconnected_;
    std::unordered_multimap<message_type_t, std::function<message_handler_t>>
        message_handlers_;

    std::set<message_type_t> local_supported_messages_;
    std::set<unsigned short> local_supported_protocols_;
};

class node_server : public node
{
public:
    node_server(const std::string& node_name)
        : node(node_type::local_server, node_name)
    {
    }
};

class node_client : public node
{
public:
    node_client(const std::string& node_name)
        : node(node_type::local_client, node_name)
    {
    }
};

}  //namespace nc3
