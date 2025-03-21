#pragma once

// (c) Copyright Krasheninnikov 2021

#include <string>
#include <vector>

namespace cpi_channel_protocol
{
// Протокол СОИ для взаимодействия между внешними маршрутизаторами

const char* const protocol_name = "cpi_channel";
const int protocol_code = 39;

#define CPI_CHANNEL_PROTOCOL_MESSAGE(MSG) \
    enum                                  \
    {                                     \
        message = message_type::MSG,      \
        protocol = protocol_code,         \
    };

enum message_type
{
    registration_msg,
    data_msg,
    confirmation_msg
};
using packet_id_t = int64_t;
using byte_array = std::vector<char>;
// в обе стороны при установке соединения
struct registration
{
    CPI_CHANNEL_PROTOCOL_MESSAGE(registration_msg)

    std::string name;  // имя узла маршрутизации
};

struct data_item
{
    std::vector<std::string>
        rpps;  // список конечных узлов, которым может быть направлено сообщение
    byte_array data;  // данные
};

struct data_packet
{
    CPI_CHANNEL_PROTOCOL_MESSAGE(data_msg)

    packet_id_t id;
    std::vector<data_item> data;  // данные
};

struct confirmation
{
    CPI_CHANNEL_PROTOCOL_MESSAGE(confirmation_msg)

    packet_id_t id;
};

#undef CPI_CHANNEL_PROTOCOL_MESSAGE

}  // namespace cpi_channel_protocol
