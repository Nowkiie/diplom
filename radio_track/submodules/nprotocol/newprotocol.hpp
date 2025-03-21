#pragma once
#include <vector>
#include <string>
#include <type_traits>
#include <limits>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_set>
#include <cstdint>
#include "serializer.hpp"
#include "serializable.hpp"
//nc2
#include "nc2point.hpp"

#pragma message ("WARNING: newprotocol.hpp depracated")

/*
    Протокол сетевого обмена
*/

namespace nprotocol
{
namespace detail
{
//шаблон для циклического перебора в type-pack
template <typename Functor>
struct foreach
{
    template <typename... Messages>
    struct foreach_helper;

    template <typename Message, typename... Messages>
    struct foreach_helper<Message, Messages...>
    {
        template <typename... Args>
        static bool call(Args&&... s)
        {
            return Functor::call<Message>(std::forward<Args>(s)...)
                   && foreach_helper<Messages...>::call(
                          std::forward<Args>(s)...);
        }
    };
    template <typename Message>
    struct foreach_helper<Message>
    {
        template <typename... Args>
        static bool call(Args&&... s)
        {
            return Functor::call<Message>(std::forward<Args>(s)...);
        }
    };
};
//сконвертировать код сообщения nc2 из кода протокола и кода сообщения
template <unsigned int ProtocolCode, unsigned int MessageCode>
static nc2::msg_type_t convert_message()
{
    //проверка на выход за границы
    static_assert(MessageCode <= USHRT_MAX && ProtocolCode <= USHRT_MAX,
                  "invalid message code");
    union comp_data
    {
        nc2::msg_type_t ui;
        uint16_t us[2];
    } cd;
    cd.us[0] = MessageCode;
    cd.us[1] = ProtocolCode;
    return cd.ui;
}

}  // namespace detail

const int current_version = 1;

template <typename Node>
class node
{
    struct message_register_struct
    {
        enum
        {
            protocol = 0
        };
        enum
        {
            message = 0
        };
        std::vector<unsigned short> supported_protocols;
        std::vector<nc2::msg_type_t> supported_messages;
        int version;
    };

    //регистрация каждого сообщения
    template <typename Handler>
    struct register_handler_functor
    {
        template <typename Message, typename Handlers, typename Async>
        static bool call(Handlers& message_handlers, Handler& handler,
                         Async& service_async)
        {
            auto message_type =
                detail::convert_message<Message::protocol, Message::message>();
            message_handlers.insert(std::make_pair(
                message_type,
                [&handler, service_async](nc2::point_id_t id, const void* data,
                                          size_t size)
                {
                    try
                    {
                        Message decoded_message{};
                        serializer::serialize(
                            serializer::memory_istream_archive(data, size),
                            decoded_message);
                        service_async->dispatch(
                            [id, &handler, decoded_message]() mutable
                            {
                                handler.message(id, decoded_message);
                            });
                    }
                    catch (...)
                    {
                    }  //игнорируем неверные сообщения
                }));
            return true;
        }
    };
    //накопление идентификаторов сообщений
    struct accumulate_types_functor
    {
        template <typename Message, typename MessagesContainer,
                  typename ProtocolsContainer>
        static bool call(MessagesContainer& messages,
                         ProtocolsContainer& protocols)
        {
            messages.insert(
                detail::convert_message<Message::protocol, Message::message>());
            protocols.insert(Message::protocol);
            return true;
        }
    };

    //обработчики входящих событий
    void register_message(nc2::point_id_t id,
                          const message_register_struct& msg)
    {
        remote_supported_protocols[id] = msg.supported_protocols;
        remote_supported_messages[id] = msg.supported_messages;

        //вызываем обработчики событя подключения
        for (auto& h : interface_handler_connected)
        {
            service_async->dispatch([h, id]()
                                    {
                                        h(id);
                                    });
        }
    }
    template <typename Handler>
    void register_interface_connected(Handler& handler)
    {
        interface_handler_connected.push_back([&handler](nc2::point_id_t id)
                                              {
                                                  handler.connected(id);
                                              });
    }
    template <typename Handler>
    void register_interface_disconnected(Handler& handler)
    {
        interface_handler_disconnected.push_back(
            [&handler](nc2::point_id_t id, nc2::result_t error)
            {
                handler.disconnected(id, error);
            });
    }

public:
    using point_id_type = nc2::point_id_t;

    node(const char* node_name)
        : service(nc2::service_factory())
        , service_async(nc2::service_factory())
        , manager(service)
        , node_name(node_name)
    {
        service->start();
        service_async->start();
        server = std::make_unique<Node>(service);

        auto register_message_type =
            detail::convert_message<message_register_struct::protocol,
                                    message_register_struct::message>();

        message_handlers.insert(std::make_pair(
            register_message_type,
            [this](nc2::point_id_t id, const void* data, size_t size)
            {
                try
                {
                    serializer::memory_istream_archive ia(data, size);
                    message_register_struct decoded_message{};
                    serializer::serialize(ia,
                                          decoded_message.supported_protocols);
                    serializer::serialize(ia,
                                          decoded_message.supported_messages);
                    serializer::serialize(ia, decoded_message.version);
                    if (decoded_message.version < current_version)
                        return;
                    register_message(id, decoded_message);
                }
                catch (...)
                {
                }  //игнорируем неверные сообщения
            }));
        local_supported_protocols.insert(message_register_struct::protocol);
        local_supported_messages.insert(register_message_type);
    }
    //регистрация обработки
    template <typename... Messages, typename Handler>
    void register_message_handler(Handler& handler)
    {
        detail::foreach<register_handler_functor<Handler>>::foreach_helper<
            Messages...>::call(message_handlers, handler, service_async);
        detail::foreach<accumulate_types_functor>::foreach_helper<
            Messages...>::call(local_supported_messages,
                               local_supported_protocols);
        register_interface_connected(handler);
        register_interface_disconnected(handler);
    }
    template <typename... Messages, typename Handler>
    void register_handler(Handler* handler)
    {
        register_message_handler<Messages...>(*handler);
    }
    template <typename Handler>
    void register_node_handler(Handler& handler)
    {
        register_interface_connected(handler);
        register_interface_disconnected(handler);
    }
    //запуск сетевого взаимодействия
    void start()
    {
        server->start(
            node_name, [this](nc2::point_socket socket)
            {
                //складываем сокеты в хранилище
                auto id = manager.add(
                    socket, [this](nc2::point_id_t id, nc2::result_t error)
                    {
                        remote_supported_protocols.erase(id);
                        remote_supported_messages.erase(id);

                        //обработчик отключения
                        for (auto& h : interface_handler_disconnected)
                        {
                            service_async->dispatch([h, id, error]()
                                                    {
                                                        h(id, error);
                                                    });
                        }
                    });
                //запуск обработки получения данных
                socket->start([this, id](nc2::msg_type_t message_type,
                                         const void* data, size_t size)
                              {
                                  //обрабатываем сообщения, на которых подключены обработчики
                                  auto iter =
                                      message_handlers.find(message_type);
                                  while (iter != message_handlers.end()
                                         && iter->first == message_type)
                                  {
                                      iter->second(id, data, size);
                                      iter++;
                                  }
                              });
                //сообщение о регистрации
                std::vector<char> stoarge;
                message_register_struct msg;
                std::copy(local_supported_protocols.begin(),
                          local_supported_protocols.end(),
                          std::back_inserter(msg.supported_protocols));
                std::copy(local_supported_messages.begin(),
                          local_supported_messages.end(),
                          std::back_inserter(msg.supported_messages));
                msg.version = current_version;
                serializer::vector_ostream_archive oa(stoarge);
                serializer::serialize(oa, msg.supported_protocols);
                serializer::serialize(oa, msg.supported_messages);
                serializer::serialize(oa, current_version);
                socket->send(
                    detail::convert_message<message_register_struct::protocol,
                                            message_register_struct::message>(),
                    stoarge.data(), stoarge.size());
            });
    }
    //отправка сообщения
    template <typename Message>
    nc2::result_t send(nc2::point_id_t id, Message& message)
    {
        std::vector<char> stoarge;
        serializer::serialize(serializer::vector_ostream_archive(stoarge),
                              message);
        auto socket = manager.get(id);
        if (socket)
        {
            return socket->send(
                detail::convert_message<Message::protocol, Message::message>(),
                stoarge.data(), stoarge.size());
        }
        else
        {
            return nc2::errc::bad_node_id;
        }
    }
    template <typename Callback>
    void post(Callback&& callback)
    {
        service->post(callback);
    }
    template <typename Callback>
    void dispatch(Callback&& callback)
    {
        service->dispatch(callback);
    }
    //отправить асинхронно
    template <typename Message, typename Callback>
    void async_send(nc2::point_id_t id, Message& message, Callback&& callback)
    {
        std::vector<char> stoarge;
        serializer::serialize(serializer::vector_ostream_archive(stoarge),
                              message);
        service->dispatch(
            [stoarge, id, callback, this]()
            {
                try
                {
                    auto socket = manager.get(id);
                    if (socket)
                    {
                        socket->async_send(
                            detail::convert_message<Message::protocol,
                                                    Message::message>(),
                            stoarge.data(), stoarge.size(), callback);
                    }
                    else
                    {
                        callback(nc2::errc::bad_node_id);
                    }
                }
                catch (...)
                {
                    callback(nc2::errc::unknown_error);
                }
            });
    }
    //проверка, поддержки протокола удалённым узлом
    bool query_protocol(nc2::point_id_t id, unsigned short protocol_id)
    {
        nc2::event lock;
        bool result = false;
        service->dispatch([&]()
                          {
                              auto iter = remote_supported_protocols.find(id);
                              if (iter == remote_supported_protocols.end())
                                  return;
                              result =
                                  std::find(iter->second.begin(),
                                            iter->second.end(), protocol_id)
                                  != iter->second.end();
                              lock.notify();
                          });
        lock.wait();
        return result;
    }
    // проверка поддержки сообщения
    template <typename Message>
    bool check_message(nc2::point_id_t id)
    {
        nc2::event lock;
        bool result = false;
        service->dispatch([&]()
        {
            auto message_type =
                detail::convert_message<Message::protocol, Message::message>();

            auto iter = remote_supported_messages.find(id);
            if (iter == remote_supported_messages.end())
                return;
            result =
                std::find(iter->second.begin(),
                    iter->second.end(), message_type)
                != iter->second.end();
            lock.notify();
        });
        lock.wait();
        return result;
    }
    void stop()
    {
        server->stop();
        manager.clear();
        nc2::event lock;
        service_async->dispatch([&lock]()
                                {
                                    lock.notify();
                                });
        lock.wait();
    }
    ~node()
    {
        stop();
        server.reset();   //останавливаем приём подключений
        manager.clear();  //разрываем существующие подключения
    }

private:
    typedef void(message_handler_t)(nc2::point_id_t id, const void* data,
                                    size_t size);
    typedef void(socket_connected_t)(nc2::point_id_t id);
    typedef void(socket_disconnected_t)(nc2::point_id_t id,
                                        nc2::result_t error);

    std::string node_name;
    nc2::service service;
    nc2::point_manager manager;
    std::unique_ptr<Node> server;
    std::vector<std::function<socket_connected_t>> interface_handler_connected;
    std::vector<std::function<socket_disconnected_t>>
        interface_handler_disconnected;

    std::map<nc2::point_id_t, std::vector<unsigned short>>
        remote_supported_protocols;
    std::map<nc2::point_id_t, std::vector<nc2::msg_type_t>>
        remote_supported_messages;
    std::unordered_set<nc2::msg_type_t> local_supported_messages;
    std::unordered_set<unsigned short> local_supported_protocols;

    std::unordered_multimap<nc2::msg_type_t, std::function<message_handler_t>>
        message_handlers;
    nc2::service service_async;
};

using node_server = node<nc2::point_server>;
using node_client = node<nc2::point_client>;
}  // namespace nprotocol
