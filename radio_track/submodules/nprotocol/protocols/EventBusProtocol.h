#pragma once

// (c) Copyright Dmitriy Shikhov 2021

#include <string>
#include <vector>

namespace event_bus_protocol
{
// Протокол шины событий

const char* const protocol_name = "EventBus";
const int protocol_code = 37;

#define EVENT_BUS_PROTOCOL_MESSAGE(MSG) \
    enum                                \
    {                                   \
        message = message_type::MSG,    \
        protocol = protocol_code,       \
    };

enum message_type
{
    event_msg,
    subscription_msg,
};

using ns_time_t = int64_t;

// Событие
// Отправляется в шину источниками событий и из шины подписчикам
struct event
{
    EVENT_BUS_PROTOCOL_MESSAGE(event_msg)

    ns_time_t time_utc;         // время в UTC
    std::string type;           // тип
    std::string route;          // маршрут от источника
    std::vector<uint8_t> data;  // данные
};

struct subscription_element
{
    std::string type_regexp;   // фильтр по типу
    std::string route_regexp;  // фильтр по маршруту
    ns_time_t keep_time;  // время хранения в шине после отключения подписчика
};

// Подписка
// Отправляется в шину для подписки на события; отменяет предыдущую подписку
struct subscription
{
    EVENT_BUS_PROTOCOL_MESSAGE(subscription_msg)

    std::string guid;  // GUID подписчика
    std::vector<subscription_element>
        subscription_elements;  // параметры подписки
};

#undef EVENT_BUS_PROTOCOL_MESSAGE

}  // namespace event_bus_protocol
