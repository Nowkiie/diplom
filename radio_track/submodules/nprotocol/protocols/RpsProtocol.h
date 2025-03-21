#pragma once

#include "shared/PelengEnums.h"

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

namespace rps_protocol {

const int protocol_code = 28;
const char* const protocol_name = "client_to_rps_protocol";

using ns_time_t = uint64_t;     // unix-time в наносекундах
using rpa_id_t = uint32_t;      // идентификатор пеленгатора
using source_id_t = uint32_t;   // идентификатор отправителя
using command_id_t = uint32_t;  // идентификатор команды

struct coordinate  // координаты в секундах
{
    int latitude;
    int longitude;
};

enum rps_protocol_codes {
    rpa_description_message_msg,

    rpa_connected_message_msg,
    rpa_disconnected_message_msg,
    rpa_state_changed_message_msg,
    rpa_signal_sources_changed_message_msg,

    register_source_message_msg,

    command_request_msg,
    command_error_msg,
    peleng_answer_msg,
    error_answer_msg,
};

struct rpp_unique_description // уникальное описание РПП
{
    uint32_t id;                            // идентификатор РПП
    std::string name_ui;                    // имя РПП
    peleng_enums::rpp_formation formation;  // исполнение РПП
};

struct rpa_unique_description // уникальное описание РПА
{
    std::string name_ui;                        // Имя РПА

    std::string protocol_name;                  // имя протокола подключения
    peleng_enums::rpa_type type;                // тип пеленгатора

    rpp_unique_description rpp_description;     // описание РПП
};

struct source_unique_description // уникальное описание Источника команд
{
    std::string host_name;                      // имя станции
    std::string program_name;                   // имя программы
    std::string post_name;                      // имя поста

    rpp_unique_description rpp_description;     // описание РПП
};

enum class rpa_status : int32_t {
    rpa_ready = 0,
    rpa_warning,
    rpa_error,
};

struct rpa_state_t // уникальное описание РПА
{
    coordinate position;    // координаты РПА
    rpa_status status;      // общий статус
};

struct rpa_signal_source_t // описание источника сигнала
{
    uint64_t freq_from;              // начало частотного интервала
    uint64_t freq_to;                // конец частотного интервала
    ns_time_t time_history_depth;    // глубина истории
};

struct rpa_description_t {
    rpa_id_t id; // идентификатор РПА внутри протокола

    rpa_unique_description description; // информация, определяющая уникальность РПА

    std::vector<int> pi_codes;        // доступные для обработки ПИ
    rpa_state_t state;  // состояние РПА на момент отправки описания
    std::vector<rpa_signal_source_t> signal_sources; // список источников сигнала
};

// пакеты обмена клиент<->сервер

//------------------------------------
// список подключенных рпа
// клиент <- сервер
//    Формируется при установке соединения
//------------------------------------
struct rpa_description_message {
    enum {
        message = rpa_description_message_msg,
        protocol = protocol_code,
    };

    std::vector<rpa_description_t> rpa_descriptions;
};

//------------------------------------
// событие подключения нового РПА
// клиент <- сервер
//------------------------------------
struct rpa_connected_message {
    enum {
        message = rpa_connected_message_msg,
        protocol = protocol_code,
    };

    rpa_description_t rpa_description;
};

//------------------------------------
// событие отключения РПА
// клиент <- сервер
//------------------------------------
struct rpa_disconnected_message {
    enum {
        message = rpa_disconnected_message_msg,
        protocol = protocol_code,
    };

    rpa_id_t rpa_id;        // идентификатор РПА внутри протокола
};

//------------------------------------
// событие измения состояния пеленгатора
// клиент <- сервер
//------------------------------------
struct rpa_state_changed_message {
    enum {
        message = rpa_state_changed_message_msg,
        protocol = protocol_code,
    };

    rpa_id_t rpa_id;        // идентификатор РПА внутри протокола
    rpa_state_t rpa_state;    // состояние РПА
};

// обновление списка доступных УРС РПА
// сервер -> клиент
struct rpa_signal_sources_changed_message
{
    enum
    {
        message = rpa_signal_sources_changed_message_msg,
        protocol = protocol_code,
    };

    rpa_id_t rpa_id;  // идентификатор РПА
    std::vector<rpa_signal_source_t> signal_sources; // список источников сигнала
};

//------------------------------------
// если необходимо идентифицировать источник команды, то его можно зарегистрировать
// клиент -> сервер
//------------------------------------
struct register_source_message {
    enum {
        message = register_source_message_msg,
        protocol = protocol_code,
    };

    source_id_t source_id;      // идентификатор отправителя внутри соединения
    source_unique_description description;   // описание источника
};

//------------------------------------
// запрос на получение пеленга по команде
// клиент -> сервер
//------------------------------------
struct command_request {
    enum {
        message = command_request_msg,
        protocol = protocol_code,
    };

    std::vector<rpa_id_t> rpa_id;    // рпа, для отработки команды
    command_id_t command_request_id; // номер команды внутри протокола
    source_id_t source_id;           // источник команды внутри соединения

    uint64_t frequency;              // частота
    int vp_code;                     // номер вп
    int pi_code;                     // номер пи
    int32_t freq_neg_delta;          // частотные границы относительно частоты
    int32_t freq_pos_delta;          // подаваемой команды
    ns_time_t time_from;             // время начала пеленгования (в нс) UTC
    ns_time_t time_to;               // время окончания пеленгования (в нс) UTC
};

//------------------------------------
// результат-пеленг по команде
//------------------------------------
struct peleng_result  //один пеленг
{
    float angle;                      // пеленг
    std::vector<float> place_angles;  // углы места

    float probability;  // вероятность попадания в допустимый интервал ошибки
    float forecasted_error;  // предсказанная ошибка, в градусах(accuracy)
    uint16_t range;          // дальность (в км)

    ns_time_t time_from;  // начало пеленгования пеленгатором (в нс) utc
    ns_time_t time_to;    // окончание пеленгования пеленгатором (в нс) utc

    int32_t freq_neg_delta;  //частотные границы относительно частоты
    int32_t freq_pos_delta;  //подаваемой команды

    std::string iri;  //идентификатор излучения
};

//------------------------------------
// результат-ошибка пеленгатора по команде
//------------------------------------
struct error_result {
    peleng_enums::peleng_error category;  // тип ошибки
    int32_t code;                         // код ошибки
    std::string message;                  // описание ошибки
};

//------------------------------------
// результат: набор пеленгов от РПА
// клиент <- сервер
//------------------------------------
struct peleng_answer {
    enum {
        message = peleng_answer_msg,
        protocol = protocol_code,
    };

    rpa_id_t rpa_id;                    // идентификатор РПА внутри протокола
    command_id_t command_request_id;    // номер команды внутри протокола

    coordinate rpa_position;            // расположение РПА
    std::vector<peleng_result> pelengs; // пеленга
};

//------------------------------------
// результат: ошибка от РПА
// клиент <- сервер
//------------------------------------
struct error_answer {
    enum {
        message = error_answer_msg,
        protocol = protocol_code,
    };

    rpa_id_t rpa_id;                    // идентификатор РПА внутри соединения
    command_id_t command_request_id;    // номер команды внутри соединения

    error_result error;                 // ошибка пеленгования
};

struct command_error {
    enum {
        message = command_error_msg,
        protocol = protocol_code,
    };
    command_id_t command_request_id;    // клиентский номер команды

    std::string error_message;          // описание ошибки
};

}  // namespace rps_protocol
