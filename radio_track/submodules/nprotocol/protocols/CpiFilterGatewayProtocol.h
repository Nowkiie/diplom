#pragma once

// (c) Copyright Krasheninnikov 2021

#include <string>
#include <vector>

namespace cpi_filter_protocol
{
// Протокол СОИ для связи шлюза событий с фильтрами

const char* const protocol_name = "cpi_filter";
const int protocol_code = 40;

#define CPI_FILTER_PROTOCOL_MESSAGE(MSG) \
    enum                                 \
    {                                    \
        message = message_type::MSG,     \
        protocol = protocol_code,        \
    };

enum message_type
{
    filter_name_msg,
    event_to_filter_msg,
    filtered_event_msg
};
using byte_array_t = std::vector<uint8_t>;
using ns_time_t = int64_t;
using id_t = uint64_t;
// фильтр->шлюз
struct filter_name
{
    CPI_FILTER_PROTOCOL_MESSAGE(filter_name_msg)

    std::string name;
};

struct event_t
{
    ns_time_t time_utc;  // время в UTC
    std::string type;    // тип
    std::string route;   // маршрут от источника
    byte_array_t data;   // данные
};
struct event_item
{
    id_t id;
    event_t event;
};
// шлюз->фильтр
struct events_to_filter
{
    CPI_FILTER_PROTOCOL_MESSAGE(event_to_filter_msg)

    std::vector<event_item> events;
};

struct group_event
{
    std::vector<id_t>
        ids;  //список событий, из агрегации которых было сформировано событие
    event_t event;
};
//  фильтр->шлюз
struct filtered_event
{
    CPI_FILTER_PROTOCOL_MESSAGE(filtered_event_msg)

    std::vector<group_event> events;
    std::vector<id_t> filtered_ids;
};

#undef CPI_FILTER_PROTOCOL_MESSAGE

}  // namespace cpi_filter_protocol
