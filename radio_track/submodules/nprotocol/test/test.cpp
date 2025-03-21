#include "testprotocol.h"
#include "nc3.hpp"
#include "nc2.hpp"
#include <iostream>
#include <variant>
#include <vector>
#include <map>
#include <boost/rational.hpp>
#include <variant>
#include <optional>
#include <iomanip>
#ifdef __linux__
#    define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE nprotocol_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(nprotocol_test)

template <typename T>
std::vector<char> struct_to_vector(const T& t)
{
    std::vector<char> data;
    serializer::vector_ostream_archive ar(data);
    serializer::serialize(ar, t);
    return data;
}

template <typename T>
T vector_to_struct(const std::vector<char>& data)
{
    T result{};
    serializer::vector_istream_archive ar(data);
    serializer::serialize(ar, result);
    return result;
}

void print_vector(const std::vector<char>& data)
{
    int couner{};
    for (const char c : data)
    {
        std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex
                  << ((unsigned int)(c)&0xff) << ", ";
        couner++;
        if (couner % 8 == 0)
        {
            std::cout << std::endl;
        }
    }
}

struct test_fields_expand1
{
    int i1;
    int i2;
};
struct test_fields_expand2
{
    int i1;
    int i2;
    int i3 = 4;
};

BOOST_AUTO_TEST_CASE(serializer_fields_expand)
{
    const test_fields_expand1 s1{1, 2};
    std::vector<char> data = struct_to_vector(s1);

    auto s2 = vector_to_struct<test_fields_expand2>(data);
    BOOST_CHECK_EQUAL(s1.i1, s2.i1);
    BOOST_CHECK_EQUAL(s1.i2, s2.i2);
    BOOST_CHECK_EQUAL(4, s2.i3);
}
BOOST_AUTO_TEST_CASE(serializer_fields_reduce)
{
    const test_fields_expand2 s2{1, 2, 3};
    std::vector<char> data = struct_to_vector(s2);

    auto s1 = vector_to_struct<test_fields_expand1>(data);
    BOOST_CHECK_EQUAL(s1.i1, s2.i1);
    BOOST_CHECK_EQUAL(s1.i2, s2.i2);
}

const unsigned char fields_binary_data[] = {
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_fields_binary)
{
    const test_fields_expand2 s2{1, 2, 3};
    std::vector<char> data = struct_to_vector(s2);
    BOOST_CHECK_EQUAL(sizeof(fields_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(fields_binary_data, data.data(), data.size()));
}

struct test_set
{
    std::set<int> set_;
};

const unsigned char fields_set_data[] = {
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_set_binary)
{
    test_set s;
    s.set_.insert(1);
    s.set_.insert(22);
    std::vector<char> data = struct_to_vector(s);
    BOOST_CHECK_EQUAL(sizeof(fields_set_data), data.size());
    BOOST_CHECK(!std::memcmp(fields_set_data, data.data(), data.size()));
}


struct test_multiset
{
    std::multiset<int> set_;
};

const unsigned char fields_multiset_data[] = {
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_multiset_binary)
{
    test_multiset s;
    s.set_.insert(1);
    s.set_.insert(1);
    std::vector<char> data = struct_to_vector(s);
    BOOST_CHECK_EQUAL(sizeof(fields_multiset_data), data.size());
    BOOST_CHECK(!std::memcmp(fields_multiset_data, data.data(), data.size()));
}


struct test_vector_simple
{
    std::vector<int> data;
};

const unsigned char vector_simple_binary_data[] = {
    0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_vector_simple_binary)
{
    const test_vector_simple s1{{2, 3, 4}};
    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(vector_simple_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(vector_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_vector_simple>(data);
    BOOST_CHECK_EQUAL(s2.data[2], s1.data[2]);
}

struct test_array_simple
{
    int v1;
    int arr[4];
    int v2;
};

const unsigned char array_simple_binary_data[] = {
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xb8, 0x0b,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x98, 0x08, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_array_simple_binary)
{
    test_array_simple s1{3000, {5, 7, 9}, 2200};
    std::vector<char> data = struct_to_vector(s1);

    BOOST_CHECK_EQUAL(sizeof(array_simple_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(array_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_array_simple>(data);
    BOOST_CHECK_EQUAL(s2.v2, s1.v2);
    BOOST_CHECK_EQUAL(s2.arr[2], s1.arr[2]);
}

struct test_map_simple
{
    std::map<int, long long> maps;
};

const unsigned char map_simple_binary_data[] = {
    0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x35, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x9c, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_map_simple_binary)
{
    test_map_simple s1{{{1, 33333}, {3, 44444}}};
    std::vector<char> data = struct_to_vector(s1);

    BOOST_CHECK_EQUAL(sizeof(map_simple_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(map_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_map_simple>(data);
    BOOST_CHECK_EQUAL(s2.maps.size(), 2);
    BOOST_CHECK_EQUAL(s2.maps.count(3), 1);
}

struct test_multimap_simple
{
    std::multimap<int, long long> maps;
};

const unsigned char multimap_simple_binary_data[] = {
    0x01, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00,
    
    0x01, 0x00, 0x00, 0x00,
    0x35, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    
    0x01, 0x00, 0x00, 0x00,
    0x9c, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_multimap_simple_binary)
{
    test_multimap_simple s1{{{1, 33333}, {1, 44444}}};
    std::vector<char> data = struct_to_vector(s1);

    BOOST_CHECK_EQUAL(sizeof(multimap_simple_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(multimap_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_multimap_simple>(data);
    BOOST_CHECK_EQUAL(s2.maps.size(), 2);
    BOOST_CHECK_EQUAL(s2.maps.count(1), 2);
}

struct test_optional_simple
{
    std::optional<int> v1;
    std::optional<int> v2;
};

const unsigned char optional_simple_binary_data[] = {
    0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,

};

BOOST_AUTO_TEST_CASE(serializer_optional_simple_binary)
{
    test_optional_simple s1;
    s1.v2 = 10;

    std::vector<char> data = struct_to_vector(s1);

    BOOST_CHECK_EQUAL(sizeof(optional_simple_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(optional_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_optional_simple>(data);
    BOOST_CHECK(s2.v2.has_value());
    BOOST_CHECK(!s2.v1.has_value());
    BOOST_CHECK_EQUAL(s2.v2.value(), 10);
}

struct test_variant_simple
{
    std::variant<int, int, char, float> v1;
    std::variant<int, std::string> v2;
    std::variant<int, int> v3;
};

const unsigned char variant_simple_binary_data[] = {
    0x03, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0xde, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x74, 0x65, 0x73, 0x74, 0x5f, 0x73, 0x74, 0x72, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_variant_simple_binary)
{
    test_variant_simple s1;
    s1.v1.emplace<1>(222);
    s1.v2 = "test_str";

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(variant_simple_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(variant_simple_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_variant_simple>(data);
    BOOST_CHECK_EQUAL(s2.v1.index(), s1.v1.index());
    BOOST_CHECK_EQUAL(std::get<1>(s2.v1), std::get<1>(s1.v1));

    BOOST_CHECK_EQUAL(s2.v2.index(), s1.v2.index());
    BOOST_CHECK_EQUAL(std::get<1>(s2.v2), std::get<1>(s1.v2));
}

struct test_child
{
    std::string v1;
};

struct test_child_expand
{
    std::string v1;
    std::string v2;
};

struct test_complex
{
    int v1;
    std::vector<test_child> v2;
};

struct test_complex_expand
{
    int v1;
    std::vector<test_child_expand> v2;
    std::unordered_map<int, test_child_expand> v3;
    std::optional<std::vector<int>> v4;
};

const unsigned char complex_binary_data[] = {
    0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
    0x34, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x31, 0x06, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x32, 0x02, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x33, 0x06, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x65, 0x34, 0x20, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x35, 0x82, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x74, 0x34, 0x06, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x74, 0x35, 0x18, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
};

BOOST_AUTO_TEST_CASE(serializer_complex_binary)
{
    test_complex_expand s1{};
    s1.v1 = 100;
    s1.v2.push_back(test_child_expand{"e1", "e2"});
    s1.v2.push_back(test_child_expand{"e3", "e4"});
    s1.v3[33333] = test_child_expand{"t4", "t5"};
    s1.v4 = std::vector<int>{9, 9, 9, 10};

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(complex_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(complex_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_complex>(data);
    BOOST_CHECK_EQUAL(s1.v1, s2.v1);
    BOOST_CHECK_EQUAL(s2.v2.size(), 2);
    BOOST_CHECK_EQUAL(s2.v2[0].v1, "e1");
    BOOST_CHECK_EQUAL(s2.v2[1].v1, "e3");

    std::vector<char> data2 = struct_to_vector(s2);
    auto s3 = vector_to_struct<test_complex_expand>(data2);

    BOOST_CHECK_EQUAL(s2.v1, s3.v1);
    BOOST_CHECK_EQUAL(s3.v2.size(), 2);
    BOOST_CHECK_EQUAL(s3.v2[0].v1, "e1");
    BOOST_CHECK_EQUAL(s3.v2[0].v2, "");
    BOOST_CHECK_EQUAL(s3.v2[1].v1, "e3");
    BOOST_CHECK_EQUAL(s3.v2[1].v2, "");
    BOOST_CHECK_EQUAL(s3.v3.size(), 0);
}

struct test_rational
{
    boost::rational<int64_t> r;
    std::string si;
};

const unsigned char test_rational_binary_data[] = {
    0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72,
};

BOOST_AUTO_TEST_CASE(serializer_rational)
{
    test_rational s1{};
    s1.r = boost::rational<int64_t>(1, 3);
    s1.si = "str";

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(test_rational_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(test_rational_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_rational>(data);
    BOOST_CHECK_EQUAL(s1.r, s2.r);
    BOOST_CHECK_EQUAL(s1.si, s2.si);
}

struct test_uuid
{
    boost::uuids::uuid u;
    std::string si;
};

const unsigned char test_uuid_binary_data[] = {
    0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
    0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72};

BOOST_AUTO_TEST_CASE(serializer_uuid)
{
    test_uuid s1{};
    for (int i = 0; i < 16; i++) s1.u.data[i] = i + 2;

    s1.si = "str";

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(test_uuid_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(test_uuid_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_uuid>(data);
    BOOST_CHECK(s1.u == s2.u);
    BOOST_CHECK_EQUAL(s1.si, s2.si);
}

struct test_array
{
    std::array<int, 10> arr;
    std::string si;
};

const unsigned char test_array_binary_data[] = {
    0x02, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x31};

BOOST_AUTO_TEST_CASE(serializer_array)
{
    test_array s1{};
    for (int i = 0; i < 10; i++) s1.arr[i] = i + 2;

    s1.si = "str1";

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(test_array_binary_data), data.size());
    BOOST_CHECK(!std::memcmp(test_array_binary_data, data.data(), data.size()));

    auto s2 = vector_to_struct<test_array>(data);
    BOOST_CHECK(s1.arr[2] == s2.arr[2]);
    BOOST_CHECK_EQUAL(s1.si, s2.si);
}

struct empty_struct
{
    enum
    {
        x = 0
    };
};

const unsigned char test_empty_struct_binary_data[] = {
    0x00,
    0x00,
    0x00,
    0x00,
};

BOOST_AUTO_TEST_CASE(test_empty_struct)
{
    empty_struct s1{};

    std::vector<char> data = struct_to_vector(s1);
    BOOST_CHECK_EQUAL(sizeof(test_empty_struct_binary_data), data.size());
    BOOST_CHECK(
        !std::memcmp(test_empty_struct_binary_data, data.data(), data.size()));

    vector_to_struct<empty_struct>(data);
}

class server_handler
{
public:
    server_handler(nc3::node& server)
        : server(server)
    {
    }
    void connected(nc3::point_id_t /*id*/, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t id, const client_to_server_structure& msg)
    {
        server_to_client_structure answer;
        answer.echo = "#" + msg.echo;
        server.send(id, answer);
    }

private:
    nc3::node& server;
};

class client_handler
{
public:
    client_handler(nc3::node& client)
        : client(client)
        , connected_{}
        , ok_{}
        , check_message_{}
    {
    }
    void connected(nc3::point_id_t id, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
        check_message_ = client.check_message<client_to_server_structure>(id);
        connected_++;
        client_to_server_structure msg;
        msg.childs.resize(10);
        msg.echo = "echo";
        client.send(id, msg);
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t /*id*/, const server_to_client_structure& msg)
    {
        ok_ = msg.echo == "#echo";
    }
    bool check()
    {
        return ok_ && connected_ == 1 && check_message_;
    }

private:
    nc3::node& client;
    int connected_;
    bool ok_;
    bool check_message_;
};

BOOST_AUTO_TEST_CASE(network_connection)
{
    nc3::node_client client(test_procol_name);
    client_handler client_handler(client);

    nc3::node_server server(test_procol_name);
    server_handler server_handler(server);

    client.register_handler<server_to_client_structure>(&client_handler);
    server.register_handler<client_to_server_structure>(&server_handler);

    client.start();
    server.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    BOOST_CHECK_EQUAL(client_handler.check(), true);

    server.stop();
    client.stop();
}

BOOST_AUTO_TEST_CASE(network_start_stop1)
{
    nc3::node_client client(test_procol_name);
    client_handler client_handler(client);

    nc3::node_server server(test_procol_name);
    server_handler server_handler(server);

    client.register_handler<server_to_client_structure>(&client_handler);
    server.register_handler<client_to_server_structure>(&server_handler);

    for (int i = 0; i < 100; i++)
    {
        client.start();
        client.stop();
    }
    client.start();

    server.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    BOOST_CHECK_EQUAL(client_handler.check(), true);

    server.stop();
    client.stop();
}

BOOST_AUTO_TEST_CASE(network_start_stop2)
{
    nc3::node client(nc3::node_type::host_client, test_procol_name);
    client_handler client_handler(client);

    nc3::node server(nc3::node_type::host_server, test_procol_name);
    server_handler server_handler(server);

    client.register_handler<server_to_client_structure>(&client_handler);
    server.register_handler<client_to_server_structure>(&server_handler);

    server.start();
    server.stop();

    client.start();
    server.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    BOOST_CHECK_EQUAL(client_handler.check(), true);

    server.stop();
    client.stop();
}

BOOST_AUTO_TEST_CASE(check_host_name)
{
    BOOST_CHECK(nc3::node::local_host_name().size() > 0);
}

const char handler_buf{22};

struct nc2_server_handler
{
    void connected(nc3::point_id_t id, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
        server.send(id, 10, &handler_buf, sizeof(handler_buf));
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t /*id*/, nc2::message_type_t type,
                 const void* /*data*/, size_t /*size*/)
    {
        if (type == 11)
        {
            answer_recieved = true;
        }
    }
    nc2::node_server& server;
    bool answer_recieved;
};
struct nc2_client_handler
{
    void connected(nc3::point_id_t /*id*/, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t id, nc2::message_type_t type, const char* data,
                 uint32_t size)
    {
        if (type == 10 && size == sizeof(handler_buf) && data[0] == handler_buf)
        {
            client.send(id, 11, 0, 0);
        }
    }
    nc2::node_client& client;
};

/*BOOST_AUTO_TEST_CASE(nc2_test)
{
    nc2::node_server server("ServerMP");
    nc2_server_handler server_handler{server, false};

    nc2::node_client client("127.0.0.1", "ServerMP");
    nc2_client_handler client_handler{client};

    server.register_handler(&server_handler);
    server.start();
    client.register_handler(&client_handler);
    client.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    server.stop();
    client.stop();
    BOOST_CHECK(server_handler.answer_recieved == true);
}
*/

// ! так не использовать !

class nc3_raw_enabler : public nc3::node
{
public:
    nc3_raw_enabler(nc3::node_type type, const std::string& node_name)
        : nc3::node(type, node_name)
    {
    }
    bool send_raw(nc3::point_id_t id, nc3::message_type_t msg_type,
                  const void* data, size_t size)
    {
        return nc3::node::send_raw(id, msg_type, data, size);
    }
    template <typename Handler>
    void register_raw_handler(
        const std::vector<nc3::message_type_t>& message_types, Handler* handler)
    {
        nc3::node::register_raw_handler(message_types, handler);
    }
};

class raw_manager_server
{
public:
    raw_manager_server()
        : node_(nc3::node_type::host_server, test_procol_name)
    {
        node_.register_raw_handler({nc3::detail::convert_message<
                                       client_to_server_structure::protocol,
                                       client_to_server_structure::message>()},
                                   this);
        node_.start();
    }
    ~raw_manager_server()
    {
        node_.stop();
    }
    void connected(nc3::point_id_t /*id*/, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t id, nc3::message_type_t msg_type,
                 const void* data, size_t size)
    {
        client_to_server_structure decoded_message{};

        serializer::serialize(serializer::memory_istream_archive(data, size),
                              decoded_message);

        server_to_client_structure answer;
        answer.echo = "#" + decoded_message.echo;

        node_.send(id, answer);
    }

private:
    nc3_raw_enabler node_;
};

class raw_manager_client
{
public:
    raw_manager_client()
        : node_(nc3::node_type::host_client, test_procol_name)
    {
        ok_ = false;
        node_.register_handler<server_to_client_structure>(this);
        node_.start();
    }
    ~raw_manager_client()
    {
        node_.stop();
    }
    void connected(nc3::point_id_t id, nc3::address_t /*address*/,
                   nc3::port_t /*port*/)
    {
        client_to_server_structure msg{};
        msg.childs.resize(10);
        msg.echo = "echo";

        std::vector<char> stoarge;

        serializer::serialize(serializer::vector_ostream_archive(stoarge), msg);

        node_.send_raw(
            id,
            nc3::detail::convert_message<client_to_server_structure::protocol,
                                         client_to_server_structure::message>(),
            stoarge.data(), stoarge.size());
    }
    void disconnected(nc3::point_id_t /*id*/) {}
    void message(nc3::point_id_t /*id*/, const server_to_client_structure& msg)
    {
        ok_ = msg.echo == "#echo";
    }
    bool check()
    {
        return ok_;
    }

private:
    bool ok_;
    nc3_raw_enabler node_;
};

BOOST_AUTO_TEST_CASE(test_raw)
{
    raw_manager_server server;
    raw_manager_client client;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    BOOST_CHECK_EQUAL(client.check(), true);
}

BOOST_AUTO_TEST_SUITE_END()
