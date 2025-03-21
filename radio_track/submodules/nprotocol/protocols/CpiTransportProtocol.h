#pragma once

// (c) Copyright Krasheninnikov 2021

#include <string>
#include <vector>
#include <optional>

namespace cpi_transport_protocol
{
// Протокол СОИ для связи внешнего маршртуизатора и клиентов

const char* const protocol_name = "cpi_transport";
const int protocol_code = 38;

#define CPI_TRANSPORT_PROTOCOL_MESSAGE(MSG) \
    enum                                    \
    {                                       \
        message = message_type::MSG,        \
        protocol = protocol_code,           \
    };

enum message_type
{
    registration_msg,
    registration_answer_msg,
    rpp_list_msg,
    data_request_msg,
    send_data_msg,
    transfer_data_rpp_list_msg,
    receive_data_msg
};
using byte_array_t = std::vector<char>;
using rpp_list_t = std::vector<std::string>;
// клиент->маршрутизатор
struct registration
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(registration_msg)

    std::string type;  // тип
};
// маршрутизатор->клиент
struct registration_answer
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(registration_answer_msg)

    std::string local_rpp_name;  // имя локального узла маршрутизации
};

//  маршрутизатор->клиент
//на старте и при обновлении таблицы маршрутизации
// список конечных узлов, которым может быть направлено сообщение
struct available_rpp_list
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(rpp_list_msg)

    rpp_list_t rpps;
};
//  клиент->маршрутизатор
//Список рпп, для которых имеются данные на передачу
struct transfer_data_rpp_list
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(transfer_data_rpp_list_msg)

    rpp_list_t rpps;
};
//  маршрутизатор->клиент
//запрос на пакет с данными для перечисленных РПП
struct data_request
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(data_request_msg)

    rpp_list_t rpps;
};

struct data_to_network
{
    std::string
        source_rpp;  // имя источника. Вставляется имя из registration_answer
    rpp_list_t
        rpps;  // список конечных узлов, которым может быть направлено сообщение
    byte_array_t data;  // данные
};
// клиент->маршрутизатор
// ответ на data_request
struct data_answer
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(send_data_msg)

    std::optional<data_to_network> event;
    rpp_list_t
        transfer_data_rpp_list;  //состояние клиента(список РПП для которых есть данные)
};

//  маршрутизатор->клиент
struct data_from_network
{
    CPI_TRANSPORT_PROTOCOL_MESSAGE(receive_data_msg)

    std::string source_rpp;  // имя отправителя
    byte_array_t data;       // данные
};

#undef CPI_TRANSPORT_PROTOCOL_MESSAGE

}  // namespace cpi_transport_protocol
