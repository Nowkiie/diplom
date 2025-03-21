#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <map>
#include <set>
#include <string>
#include <list>
#include <memory>
#include "node_base.hpp"

namespace nc2
{
using nc::address_t;
using nc::message_type_t;
using nc::node_active;
using nc::node_state;
using nc::point_id_t;
using nc::port_t;
using nc::queue_buffer_t;

namespace detail
{
using namespace nc::detail;
}

enum class node_type
{
    server,
    client,
};

const address_t localhost_ip = 0x7F000001;  //ip адрес локального узла

namespace detail
{
const int resolver_connect_interval = 1000;
const int max_name_size = 256;
#pragma pack(push, 1)
//структура обмена со службой (запрос)
struct message_command
{
    enum
    {
        type = 0x0f101
    };
    unsigned int flags;
    char node_name[max_name_size];  //имя узла (без пути)
    char node_info[max_name_size];  //информация, предоставленная узлом
    unsigned short port;            //номер порта
    unsigned int user_data;  //пользовательские данные - переносятся в ответ
};
struct message_answer_record
{
    char node_name[max_name_size];
    char node_info[max_name_size];
    unsigned short port;
};
struct message_answer
{
    enum
    {
        type = 0x0f103
    };
    unsigned int result;
    unsigned int records_count;
    unsigned int user_data;
    //message_answer_record records[records_count];
};
#pragma pack(pop)

//коды ошибок
namespace result
{
enum resolver_result_codes
{
    success = 0,
    bad_request = 1,
    already_registred = 2,
    not_found = 3
};

}  //namespace result

//флаги запроса
namespace flags
{
enum resolver_message_flags
{
    command_test_port = 1,  //проверять на соответствие порт
    command_test_name = 2,  //проверять на соответствие имя узла

    command_query = 4,       //сообщение - запрос
    command_register = 8,    //регистрация узла
    command_unregister = 16  //разрегистрация узла

};

}  //namespace flags
}  // namespace detail

class node_server_resolver : public nc::node_base
{
public:
    node_server_resolver(port_t server_port, const std::string& node_name)
        : server_port_(server_port)
        , node_name_(node_name)
    {
    }
    ~node_server_resolver()
    {
        stop();
    }

private:
    void connected(point_id_t id, address_t /*address*/, port_t /*port*/) override
    {
        detail::message_command command{};
        command.flags =
            detail::flags::command_register | detail::flags::command_test_name;
        std::memcpy(command.node_name, node_name_.c_str(),
                    std::min(sizeof(command.node_name) - 1, node_name_.size()));

        command.port = server_port_;

        queue_buffer_t buffer = std::make_shared<std::vector<char>>(
            sizeof(detail::message_command));
        std::memcpy(buffer->data(), &command, sizeof(detail::message_command));

        start_send(id, detail::message_command::type, buffer);
    }
    void disconnected(point_id_t /*id*/) override {}
    void message(point_id_t /*id*/, message_type_t /*type*/,
                 queue_buffer_t /*store*/) override
    {
    }
    void init() override
    {
        connect_timer_ =
            std::make_unique<boost::asio::deadline_timer>(service());
        start_timer();
    }
    void deinit() override
    {
        connect_timer_.reset();
    }
    void start_timer()
    {
        connect_timer_->expires_from_now(
            boost::posix_time::milliseconds(detail::resolver_connect_interval));
        connect_timer_->async_wait(
            [this](boost::system::error_code /*errc*/)
            {
                start_connection(1, localhost_ip,
                                 detail::resolver_service_port);
                start_timer();
            });
    }

    std::unique_ptr<boost::asio::deadline_timer> connect_timer_;
    port_t server_port_;
    std::string node_name_;
};

class node_client_resolver : public nc::node_base
{
public:
    using resolve_handler = std::function<void(address_t, port_t)>;

    node_client_resolver(const std::string& server_name,
                         const std::string& node_name, resolve_handler handler)
        : node_name_(node_name)
        , server_name_(server_name)
        , handler_(handler)
        , server_address_{}
    {
    }

    void connected(point_id_t /*id*/, address_t /*address*/, port_t /*port*/) override
    {
        send_query();
    }
    void disconnected(point_id_t /*id*/) override {}
    void message(point_id_t /*id*/, message_type_t type,
                 queue_buffer_t store) override
    {
        if (type == detail::message_answer::type)
        {
            if (store->size() >= sizeof(detail::message_answer)
                                     + sizeof(detail::message_answer_record))
            {
                detail::message_answer answer;
                std::memcpy(&answer, store->data(),
                            sizeof(detail::message_answer));
                if (answer.records_count != 0)
                {
                    detail::message_answer_record record;
                    std::memcpy(&record,
                                store->data() + sizeof(detail::message_answer),
                                sizeof(detail::message_answer_record));

                    handler_(server_address_, record.port);
                }
            }
        }
    }
    void init() override
    {
        connect_timer_ =
            std::make_unique<boost::asio::deadline_timer>(service());
        resolver_ = std::make_unique<boost::asio::ip::tcp::resolver>(service());
        start_timer();
    }
    void deinit() override
    {
        connect_timer_.reset();
        resolver_.reset();
        server_address_ = 0;
    }

private:
    void connect_resolver()
    {
        boost::asio::ip::tcp::resolver::query query(
            server_name_, "0",
            boost::asio::ip::tcp::resolver::query::canonical_name);
        resolver_->async_resolve(
            query, [this](const boost::system::error_code& /*ec*/,
                          boost::asio::ip::tcp::resolver::iterator iterator)
            {
                while (iterator != boost::asio::ip::tcp::resolver::iterator())
                {
                    if (iterator->endpoint().protocol()
                        != boost::asio::ip::tcp::v4())
                    {
                        ++iterator;
                        continue;
                    }
                    address_t addr =
                        iterator->endpoint().address().to_v4().to_ulong();
                    server_address_ = addr;
                    start_connection(0, addr, detail::resolver_service_port);
                    break;
                }
                start_timer();
            });
    }
    void send_query()
    {
        detail::message_command command{};
        command.flags =
            detail::flags::command_query | detail::flags::command_test_name;
        std::memcpy(command.node_name, node_name_.data(),
                    std::min(sizeof(command.node_name) - 1, node_name_.size()));
        command.port = 0;
        command.user_data = 0;
        queue_buffer_t buffer =
            std::make_shared<std::vector<char>>(sizeof(command));
        std::memcpy(buffer->data(), &command, sizeof(command));

        start_send(0, detail::message_command::type, buffer);
    }
    void start_timer()
    {
        connect_timer_->expires_from_now(
            boost::posix_time::milliseconds(detail::resolver_connect_interval));
        connect_timer_->async_wait(
            [this](boost::system::error_code /*errc*/)
            {
                connect_resolver();
                send_query();
            });
    }
    std::unique_ptr<boost::asio::ip::tcp::resolver> resolver_;
    std::unique_ptr<boost::asio::deadline_timer> connect_timer_;
    std::string node_name_;
    std::string server_name_;
    resolve_handler handler_;
    address_t server_address_;
};

class node : public nc::node_base
{
public:
    template <typename Handler>
    void register_handler(Handler* handler)
    {
        handler_connected_.push_back(
            [this, handler](point_id_t id, address_t address, port_t port)
            {
                post(
                    [handler, id, address, port]()
                    {
                        handler->connected(id, address, port);
                    });
            });
        handler_disconnected_.push_back(
            [this, handler](point_id_t id)
            {
                post(
                    [handler, id]()
                    {
                        handler->disconnected(id);
                    });
            });
        handler_message_.push_back(
            [this, handler](point_id_t id, message_type_t message,
                            queue_buffer_t store)
            {
                post(
                    [handler, id, message, store]()
                    {
                        handler->message(id, message, store->data(),
                                         (uint32_t)(store->size()));
                    });
            });
    }
    bool send(point_id_t id, message_type_t message, const void* data,
              uint32_t size)
    {
        if (state() != node_state::started)
        {
            return false;
        }
        queue_buffer_t store = std::make_shared<std::vector<char>>(size);
        std::memcpy(store->data(), data, size);
        dispatch(
            [this, id, message, store = std::move(store)]()
            {
                return start_send(id, message, store);
            });
        return true;
    }

private:
    void connected(point_id_t id, address_t address, port_t port) final
    {
        for (const auto& h : handler_connected_)
        {
            h(id, address, port);
        }
    }
    void disconnected(point_id_t id) final
    {
        for (const auto& h : handler_disconnected_)
        {
            h(id);
        }
    }
    void message(point_id_t id, message_type_t type, queue_buffer_t store) final
    {
        for (const auto& h : handler_message_)
        {
            h(id, type, store);
        }
    }

    typedef void(message_handler_t)(point_id_t id, message_type_t message,
                                    queue_buffer_t store);
    typedef void(socket_connected_t)(point_id_t id, address_t address,
                                     port_t port);
    typedef void(socket_disconnected_t)(point_id_t id);

    std::vector<std::function<socket_connected_t>> handler_connected_;
    std::vector<std::function<socket_disconnected_t>> handler_disconnected_;
    std::vector<std::function<message_handler_t>> handler_message_;
};

class node_server : public node
{
public:
    node_server(const std::string& node_name)
        : node_name_(node_name)
        , server_port_{}
    {
    }
    ~node_server()
    {
        stop();
    }

private:
    void init() final
    {
        port_t port = acceptor_init();
        if (port == 0)
        {
            return;
        }
        start_accept();

        resolver_ = std::make_unique<node_server_resolver>(port, node_name_);
        resolver_->start();
    }
    void deinit() final
    {
        if (resolver_)
        {
            resolver_->stop();
            resolver_.reset();
        }
        server_port_ = 0;
    }
    void start_client() {}

    std::unique_ptr<node_server_resolver> resolver_;
    std::string node_name_;
    port_t server_port_;
};

class node_client : public node
{
public:
    node_client(const std::string& server_name, const std::string& node_name)
        : server_name_(server_name)
        , node_name_(node_name)
    {
    }
    ~node_client()
    {
        stop();
    }

private:
    void init() final
    {
        resolver_ = std::make_unique<node_client_resolver>(
            server_name_, node_name_,
            [this](address_t address, port_t port)
            {
                dispatch(
                    [this, address, port]()
                    {
                        start_connection(0, address, port);
                    });
            });
        resolver_->start();
    }
    void deinit() final
    {
        if (resolver_)
        {
            resolver_->stop();
            resolver_.reset();
        }
    }

    std::unique_ptr<node_client_resolver> resolver_;
    std::string server_name_;
    std::string node_name_;
};

}  // namespace nc2
