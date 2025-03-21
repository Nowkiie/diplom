
// (c) Copyright Dmitriy Shikhov 2023

#include <memory>
#include <string>
#include <boost/test/unit_test.hpp>
#include <utils/connection.hpp>

BOOST_AUTO_TEST_SUITE(connection)

// Протокол

struct add_message
{
    int value;
};

struct sub_message
{
    int value;
};

struct connect_message
{
    int id;
};

// Фейк нода для тестирования

class fake_node
{
public:
    using point_id_type = int;

    void start()
    {
        is_started = true;
    }
    void stop()
    {
        is_started = false;
    }

    void send(point_id_type id, connect_message const& msg)
    {
        BOOST_TEST(id == msg.id);
        last_connected_message_id = id;
    }

    template <typename... Messages, typename Handler>
    void register_handler(Handler* handler)
    {
        static_assert(std::is_same_v<std::tuple<add_message, sub_message>,
                                     std::tuple<Messages...>>);

        connect = [handler](point_id_type id, std::string const& address)
        {
            handler->connected(id, address);
        };

        disconnect = [handler](point_id_type id)
        {
            handler->disconnected(id);
        };

        send_add_message = [handler](point_id_type id, add_message const& msg)
        {
            handler->message(id, msg);
        };

        send_sub_message = [handler](point_id_type id, sub_message const& msg)
        {
            handler->message(id, msg);
        };
    }

    std::function<void(point_id_type, std::string const&)> connect;
    std::function<void(point_id_type)> disconnect;
    std::function<void(point_id_type, add_message const&)> send_add_message;
    std::function<void(point_id_type, sub_message const&)> send_sub_message;

    bool is_started = false;
    point_id_type last_connected_message_id = 0;
};

// Класс единичного подключения

template <typename Sender>
class single_calculator_connection
{
public:
    // Набор сообщений, на которые будет подписка
    using messages = std::tuple<add_message, sub_message>;

    // Конструктор вызывается при новом подключении
    single_calculator_connection(fake_node::point_id_type id, Sender sender)
        : id(id)
    {
        sender.send(connect_message{id});
    }

    // Обработчики сообщений

    void message(add_message const& msg)
    {
        result += msg.value;
    }

    void message(sub_message const& msg)
    {
        result -= msg.value;
    }

    // etc.

    fake_node::point_id_type id;
    int result = 0;
};

// Класс множественного подключения

class calculators_connection final
    : public utils::connection<single_calculator_connection, utils::null_logger,
                               fake_node>
{
public:
    using connection::connection;

    // Функция, использующая 'with_connections_do'
    // для циклической обработки единичных подключений.
    //
    // Может возвращать значение (должно преобразовываться в bool
    // и при true прерывание цикла и возврат значения исходного типа)
    auto current_results() const
    {
        std::map<point_id_type, int> results;
        with_connections_do(
            [&results](auto const& connection)
            {
                results[connection->id] = connection->result;
            });
        return results;
    }

private:
    // Функция создания единичного подключения.
    // Можно передать дополнительные данные
    auto create_single_connection(point_id_type id, sender_type sender)
        -> single_connection_ptr_type override
    {
        return std::make_shared<single_connection_type>(id, sender);
    }
};

BOOST_AUTO_TEST_CASE(main)
{
    auto node = std::make_shared<fake_node>();
    BOOST_TEST(!node->is_started);

    calculators_connection connection(node);

    connection.start();
    BOOST_TEST(node->is_started);

    BOOST_TEST(connection.current_results().empty());

    {
        BOOST_TEST(node->last_connected_message_id == 0);
        node->connect(1, "");
        BOOST_TEST(node->last_connected_message_id == 1);
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 1);
        BOOST_TEST(results.at(1) == 0);
    }
    {
        node->send_add_message(1, {10});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 1);
        BOOST_TEST(results.at(1) == 10);
    }
    {
        node->send_add_message(1, {10});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 1);
        BOOST_TEST(results.at(1) == 20);
    }
    {
        node->send_sub_message(1, {3});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 1);
        BOOST_TEST(results.at(1) == 17);
    }
    {
        BOOST_TEST(node->last_connected_message_id == 1);
        node->connect(2, "");
        BOOST_TEST(node->last_connected_message_id == 2);
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 2);
        BOOST_TEST(results.at(1) == 17);
        BOOST_TEST(results.at(2) == 0);
    }
    {
        node->send_add_message(2, {1337});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 2);
        BOOST_TEST(results.at(1) == 17);
        BOOST_TEST(results.at(2) == 1337);
    }
    {
        node->send_sub_message(2, {300});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 2);
        BOOST_TEST(results.at(1) == 17);
        BOOST_TEST(results.at(2) == 1037);
    }
    {
        node->send_sub_message(2, {30});
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 2);
        BOOST_TEST(results.at(1) == 17);
        BOOST_TEST(results.at(2) == 1007);
    }
    {
        node->disconnect(1);
        const auto results = connection.current_results();
        BOOST_TEST(results.size() == 1);
        BOOST_TEST(results.at(2) == 1007);
    }
    {
        node->disconnect(2);
        const auto results = connection.current_results();
        BOOST_TEST(results.empty());
    }

    connection.stop();
    BOOST_TEST(!node->is_started);
}

BOOST_AUTO_TEST_SUITE_END()
