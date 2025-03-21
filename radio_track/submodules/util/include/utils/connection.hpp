#pragma once

// (c) Copyright Dmitriy Shikhov 2023
// (c) Copyright Ivan Chauzov 2023

#include <map>
#include <memory>
#include <mutex>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace utils
{
template <typename Node, typename Logger>
class sender
{
public:
    using node_type = Node;
    using point_id_type = typename Node::point_id_type;

    sender(point_id_type id, Node* node, Logger* logger)
        : id_{id}
        , node_{node}
        , logger_{logger}
    {
    }

    template <typename Message>
    void send(Message const& message)
    {
        logger_->send(id_, message);
        node_->send(id_, message);
    }

    template <typename Message>
    void send(std::vector<Message> const& messages)
    {
        for (Message const& message : messages)
        {
            send(message);
        }
    }

private:
    point_id_type id_;
    Node* node_ = nullptr;
    Logger* logger_ = nullptr;
};

template <template <typename> typename SingleConnection, typename Logger,
          typename Node>
class connection
{
    template <typename>
    struct register_helper;

    template <typename... Args>
    struct register_helper<std::tuple<Args...>>
    {
        template <typename Handler>
        static void register_handler(Node* node, Handler* handler)
        {
            node->template register_handler<Args...>(handler);
        }
    };

protected:
    using point_id_type = typename Node::point_id_type;
    using sender_type = sender<Node, Logger>;
    using single_connection_type = SingleConnection<sender_type>;
    using single_connection_ptr_type = std::shared_ptr<single_connection_type>;
    using node_pointer_type = std::shared_ptr<Node>;

public:
    template <typename... LoggerArgs>
    explicit connection(node_pointer_type node, LoggerArgs&&... logger_args)
        : node_{std::move(node)}
        , logger_{std::forward<LoggerArgs>(logger_args)...}
    {
    }

    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;
    connection(connection&&) = delete;
    connection& operator=(connection&&) = delete;

    virtual ~connection()
    {
        try
        {
            stop();
        }
        catch (...)
        {
        }
    }

    void start()
    {
        if (!is_started_)
        {
            register_helper<typename single_connection_type::messages>::
                register_handler(node_.get(), this);
            start_before();
            node_->start();
            logger_.start();
            is_started_ = true;
        }
    }

    void stop()
    {
        if (is_started_)
        {
            node_->stop();
            stop_after();
            logger_.stop();
            is_started_ = false;
        }
    }

protected:
    template <typename Action>
    auto with_connections_do(Action&& action) const
    {
        using return_type = decltype(action(connections_.begin()->second));
        constexpr bool is_no_void_return = !std::is_same_v<void, return_type>;

        std::lock_guard guard(connections_mutex_);
        for (auto const& [_, connection] : connections_)
        {
            if constexpr (is_no_void_return)
            {
                const auto result = action(connection);
                if (static_cast<bool>(result))
                {
                    return result;
                }
            }
            else
            {
                action(connection);
            }
        }
        if constexpr (is_no_void_return)
        {
            return return_type{};
        }
    }

    Logger logger_;

private:
    friend Node;

    virtual void start_before() {}
    virtual void stop_after() {}

    virtual auto create_single_connection(point_id_type id, sender_type sender)
        -> single_connection_ptr_type = 0;

    template <typename... AddressAndPort>
    void connected(point_id_type id, AddressAndPort&&... address_and_port)
    {
        logger_.connected(id,
                          std::forward<AddressAndPort>(address_and_port)...);
        std::lock_guard guard(connections_mutex_);
        sender_type sender{id, node_.get(), &logger_};
        connections_[id] = create_single_connection(id, std::move(sender));
    }

    void disconnected(point_id_type id)
    {
        logger_.disconnected(id);
        std::lock_guard guard(connections_mutex_);
        connections_.erase(id);
    }

    template <typename Message>
    void message(point_id_type id, Message const& message)
    {
        logger_.message(id, message);
        connections_[id]->message(message);
    }

    mutable std::mutex connections_mutex_;
    std::map<point_id_type, single_connection_ptr_type> connections_;
    node_pointer_type node_;
    bool is_started_ = false;
};

class null_logger
{
public:
    static void start() {}
    static void stop() {}
    template <typename... Args>
    static void connected(Args...)
    {
    }
    template <typename... Args>
    static void disconnected(Args...)
    {
    }
    template <typename... Args>
    static void message(Args...)
    {
    }
    template <typename... Args>
    static void send(Args...)
    {
    }
};

}  // namespace utils
