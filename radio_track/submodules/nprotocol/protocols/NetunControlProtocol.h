#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace netun::control
{
const int protocol_code = 51;
const char* const protocol_name = "NetunControlProtocol";

enum protocol_codes
{
    settings_info_msg = 0,
    settings_update_msg,
    counters_request_msg,
    counters_info_msg,
    statistics_request_msg,
    statistics_info_msg,
};

enum class transport_type : uint32_t
{
    udp,
    tcp,
};

struct setting_node
{
    uint32_t remote_address;   // удалённый адрес
    uint16_t remote_port;       // удалённый порт
    transport_type transport;  // тип транспорта
    std::string node_name;     // имя узла
};

// сервер -> клиент
// список актуальных настроек (отправляется при подключении и изменении)
struct settings_info
{
    enum
    {
        message = settings_info_msg,
        protocol = protocol_code,
    };
    uint16_t local_port;
    std::vector<setting_node> settings;
};
// клиент -> сервер
// обновление настроек
struct settings_update
{
    enum
    {
        message = settings_update_msg,
        protocol = protocol_code,
    };
    uint16_t local_port;
    std::vector<setting_node> settings;
};

struct counters_item
{
    uint32_t remote_address;
    transport_type transport;
    int32_t input_connections;
    int32_t output_connections;
};

// клиент -> сервер
// запрос счётчиков
struct counters_request
{
    enum
    {
        message = counters_request_msg,
        protocol = protocol_code,
    };
    uint64_t user_id;
};

// сервер -> клиент
// счётчики
struct counters_info
{
    enum
    {
        message = counters_info_msg,
        protocol = protocol_code,
    };
    uint64_t user_id;
    std::vector<counters_item> counters;
};

struct statistics_item
{
    int32_t connections_count{};
    uint32_t external_ip{};
    uint16_t external_port{};
    uint32_t internal_ip{};
    uint16_t internal_port{};
    uint16_t local_port{};
    uint64_t incoming_bytes{};
    uint64_t outgoing_bytes{};
    uint64_t incoming_speed{};
    uint64_t outgoing_speed{};
    std::string node_name;
};

// клиент -> сервер
// запрос статистики
struct statistics_request
{
    enum
    {
        message = statistics_request_msg,
        protocol = protocol_code,
    };
    uint64_t user_id;
};

// сервер -> клиент
// статистика
struct statistics_info
{
    enum
    {
        message = statistics_info_msg,
        protocol = protocol_code,
    };
    uint64_t user_id;
    std::vector<statistics_item> statistics;
};

}  // namespace netun::control
