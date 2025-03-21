#pragma once

#include "shared/PelengEnums.h"

#include <memory>
#include <vector>
#include <string>
#include <cstdint>
#include <optional>

namespace peleng_protocol
{
const int protocol_code = 24;
const char* const protocol_name = "pel_client_connection_node2";

using ns_time_t = uint64_t;     // unix-time в наносекундах
using rpa_id_t = uint32_t;      // идентификатор пеленгатора
using source_id_t = uint32_t;   // идентификатор отправителя
using command_id_t = uint32_t;  // идентификатор команды

struct coordinate  // координаты в секундах
{
    int latitude;
    int longitude;
};

struct rpp_unique_description  // уникальное описание РПП
{
    uint32_t id;                            // идентификатор РПП
    std::string name_ui;                    // имя РПП
    peleng_enums::rpp_formation formation;  // исполнение РПП
};

struct source_unique_description  // уникальное описание Источника команд
{
    std::string host_name;                   // имя станции
    std::string program_name;                // имя программы
    std::string post_name;                   // имя поста
    rpp_unique_description rpp_description;  // описание РПП
};

struct ellipse_params {
    float olo;         // относительная линейная ошибка (в км)
    float ellipse_w;   // размер эллипса рассеивания от экватора на север (в км)
    float ellipse_d;   // размер эллипса рассеивания по линии экватора (в км)
};

enum peleng_protocol_codes
{
    register_source_message_msg,
    scom_request_msg,
    scom_answer_msg,
    command_request_msg,
    command_answer_msg,
    command_error_msg,
    rpa_declaration_update_msg,
    rpa_state_update_msg,
    rpa_signal_sources_update_msg,
    service_status_msg,
    place_command_request_msg,
};

//------------------------------------
// запрос на регистрацию источника
// клиент -> сервер
// При необходимости отправки команды от специфического источника
//  его можно зарегистрировать дополнительно
// Это позволит внутри одного подключения подавать команды от имени
//  различных клиентов
// При отсутсвии регистрации источника, информация берется из register_message
// Включение описания РПП в источник обеспечивает работу сопряжений
//  с внешними РПП
//------------------------------------
struct register_source_message
{
    enum
    {
        message = register_source_message_msg,
        protocol = protocol_code,
    };

    source_id_t source_id;

    source_unique_description source;
};

//------------------------------------
// запрос scom для команды для учета
// клиент -> сервер
// Возврат scom происходит не на каждую команду, а только по запросу клиента
// Это позволит выполнять допеленгование сигнала пеленгаторами и накопление
//  результатов пеленгования клиентом для последующего сохранения в БД под
//  номером scom, запрошенным только один раз
//------------------------------------
struct scom_request
{
    enum
    {
        message = scom_request_msg,
        protocol = protocol_code,
    };
    int32_t scom_request_id;  // ид-запроса ском
};
//------------------------------------
// возврат scom
// сервер -> клиент
//------------------------------------
struct scom_answer
{
    enum
    {
        message = scom_answer_msg,
        protocol = protocol_code,
    };
    int32_t scom_request_id;  // ид-запроса ском
    int32_t scom;             // суточный номер на су
};

//------------------------------------
// команда на пеленг
// клиент -> сервер
//------------------------------------
struct command_request
{
    enum
    {
        message = command_request_msg,
        protocol = protocol_code,
    };
    command_id_t command_request_id;  // клиентский номер команды

    source_id_t source_id;  // клиентский идентификатор источника

    int vp_code;  // номер вп
    int pi_code;  // номер пи

    uint64_t frequency;      // частота
    int32_t freq_neg_delta;  // частотные границы относительно частоты
    int32_t freq_pos_delta;  // подаваемой команды
    ns_time_t time_from;     // время начала пеленгования (в нс) UTC
    ns_time_t time_to;       // время окончания пеленгования (в нс) UTC

    std::vector<rpa_id_t> rpa_list;  // список рпа, для отработки команды
};

struct peleng_result  //один пеленг
{
    rpa_id_t rpa_id;          // идентификатор РПА
    coordinate rpa_position;  // расположение РПА

    float angle;                      // пеленг
    std::vector<float> place_angles;  // углы места

    float probability;  // вероятность попадания в допустимый интервал ошибки
    float forecasted_error;  // предсказанная ошибка, в градусах(accuracy)
    uint16_t range;          // дальность (в км)

    int32_t freq_neg_delta;  //частотные границы относительно частоты
    int32_t freq_pos_delta;  //подаваемой команды
    ns_time_t time_from;     // начало пеленгования пеленгатором (в нс) utc
    ns_time_t time_to;       // окончание пеленгования пеленгатором (в нс) utc

    std::string iri;  //идентификатор излучения
};

struct place_result
{
    coordinate position;  // координаты места
    uint16_t olo;         // относительная линейная ошибка (в км)
    uint16_t ellipse_w;   // ширина эллипса рассеивания (в км)
    uint16_t ellipse_d;   // длина эллипса рассеивания (в км)
    float ellipse_angle;  // наклон эллипса рассеивания (в градусах)

    // список индексов пеленгов на основе которых посчитано место
    std::vector<uint32_t> peleng_index;

    std::string region_name;  // имя региона

    peleng_enums::place_type type;  // тип места
    float veracity; // достоверность места от 0 до 100.0

    // уточнения для оло и эллипса рассеивания
    // если не заполнено, то брать параметры выше с типом uint16_t
    std::optional<ellipse_params> ellipse_params_ext;
};

struct error_result
{
    rpa_id_t rpa_id;  // идентификатор РПА

    peleng_enums::peleng_error category;  // тип ошибки
    int32_t code;                         // код ошибки
    std::string message;                  // описание ошибки
};

enum class place_status : int32_t
{
    computing = 0,  // Считается
    computed,       // Сосчитано
    error,          // Ошибка сервиса
};
//------------------------------------
// команда на расчет места по известным результатам пеленгования
// клиент -> сервер
//------------------------------------
struct place_command_request
{
    enum
    {
        message = place_command_request_msg,
        protocol = protocol_code,
    };
    command_id_t command_request_id;  // клиентский номер команды

    source_id_t source_id;  // клиентский идентификатор источника

    std::vector<peleng_result> pelengs;  //результаты пеленгования
};
struct command_answer
{
    enum
    {
        message = command_answer_msg,
        protocol = protocol_code,
    };
    command_id_t command_request_id;  // клиентский номер команды

    bool last_answer;                    // флаг последнего ответа
    std::vector<peleng_result> pelengs;  // пеленга
    std::vector<error_result> errors;    // ошибки
    std::vector<place_result> places;    // места
};

struct command_error
{
    enum
    {
        message = command_error_msg,
        protocol = protocol_code,
    };
    command_id_t command_request_id;  // клиентский номер команды

    std::string error_message;  // описание ошибки
};

enum class rpa_status : int32_t
{
    rpa_ready = 0,
    rpa_warning,
    rpa_error,
    rpa_disconnected,
};

struct rpa_state
{
    coordinate position;  // координаты РПА
    rpa_status status;    // статус РПА
};

struct rpa_signal_source // описание источника сигнала
{
    uint64_t freq_from;              // начало частотного интервала
    uint64_t freq_to;                // конец частотного интервала
    ns_time_t time_history_depth;    // глубина истории
};

struct rpa_declaration
{
    rpa_id_t rpa_id;  // идентификатор РПА

    std::string name_ui;  // имя РПА

    std::string protocol_name;               // имя протокола подключения
    peleng_enums::rpa_type type;             // тип пеленгатора
    rpp_unique_description rpp_description;  // описание РПП

    std::vector<int> pi_codes;        // доступные для обработки ПИ
    rpa_state state;  // состояние РПА на момент отправки описания
    std::vector<rpa_signal_source> signal_sources; // список источников сигнала

    bool rpp_hidden;                // флаг скрытия РПП
    bool rpp_exclude_place_calc;    // флаг исключения РПП из расчета места
};

// сообщение с информацией о пеленгаторах
// сервер -> клиент
struct rpa_declaration_update
{
    enum
    {
        message = rpa_declaration_update_msg,
        protocol = protocol_code,
    };
    std::vector<rpa_declaration> rpa_declarations;
};

// обновление состояния РПА
// сервер -> клиент
struct rpa_state_update
{
    enum
    {
        message = rpa_state_update_msg,
        protocol = protocol_code,
    };
    rpa_id_t rpa_id;  // идентификатор РПА

    rpa_state state;  // состояние РПА
};

// обновление списка доступных УРС РПА
// сервер -> клиент
struct rpa_signal_sources_update
{
    enum
    {
        message = rpa_signal_sources_update_msg,
        protocol = protocol_code,
    };
    rpa_id_t rpa_id;  // идентификатор РПА

    std::vector<rpa_signal_source> signal_sources; // список источников сигнала
};

// обновление статуса Сервиса
// сервер -> клиент
struct service_status
{
    enum
    {
        message = service_status_msg,
        protocol = protocol_code,
    };

    bool rps_available;     // флаг доступности
    bool place_available;   // флаг доступности
    bool region_available;  // флаг доступности
};

}  // namespace peleng_protocol
