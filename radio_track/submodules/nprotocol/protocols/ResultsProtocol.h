#pragma once

#include "shared/PelengEnums.h"

#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <boost/uuid/uuid.hpp>

/*

взаимодействие для передачи сырых данных (на узле protocol_name_to_server)

добывание                           сервер результатов

    register_result_source
----------------------------------------------->
    signal_information
    session_start
----------------------------------------------->
    session_file
    session_parameter
    session_radiodata
    session_end
----------------------------------------------->
    session_commit
<-----------------------------------------------


    session_command
----------------------------------------------->
    command_commit
<-----------------------------------------------
    session_completed
----------------------------------------------->

*/

namespace results_protocol
{
enum results_protocol_codes
{
    register_result_source_msg,
    register_result_handler_msg,
    signal_information_msg,
    signal_parameters_msg,
    radiodata_information_msg,
    session_start_msg,
    session_end_msg,
    session_commit_msg,
    session_file_msg,
    session_parameter_msg,
    session_radiodata_msg,
    session_command_pointer_msg,
    session_command_msg,
    session_error_msg,
    server_status_msg,
    command_commit_msg,
    command_error_msg,
    session_completed_msg,
    session_repeate_msg,
};

const char* const protocol_name_to_server = "results_protocol_to_server";

const int protocol_code = 17;

using ns_time_t = uint64_t;
using id_t = boost::uuids::uuid;
using rpa_id_t = uint32_t;  // идентификатор пеленгатора

enum class signal_type_source : int
{
    undefined = 0,
    hf = 1,
    uhf = 2,
    sat = 3,
};

inline std::string to_string(signal_type_source source)
{
    switch (source)
    {
        case signal_type_source::undefined:
            return "undefined";
        case signal_type_source::hf:
            return "hf";
        case signal_type_source::uhf:
            return "uhf";
        case signal_type_source::sat:
            return "sat";
        default:
            return std::to_string(static_cast<int>(source));
    }
}

enum class parameter_type : int
{
    type_int,
    type_double,
    type_time,
    type_string,
};

inline std::string to_string(parameter_type type)
{
    switch (type)
    {
        case parameter_type::type_int:
            return "int";
        case parameter_type::type_double:
            return "double";
        case parameter_type::type_time:
            return "time";
        case parameter_type::type_string:
            return "string";
        default:
            return std::to_string(static_cast<int>(type));
    }
}

struct parameter_declaration
{
    parameter_type type;      // тип данных
    std::string name;         // имя на латинице (не меняется)
    std::string name_ui;      // имя для отображения пользователю
    std::string description;  // описание
};

struct signal_type_declaration
{
    signal_type_source type_source;  // тип источника (кв\укв\ссс)
    std::string name;                // код вида передачи
    std::string name_ui;             // имя вида передачи
    std::string description;         // описание
};

enum class client_type
{
    realtime,  // в реальном времени
    cached,    // с локальным кэшем (может повторять отправку)
};

inline std::string to_string(client_type type)
{
    switch (type)
    {
        case client_type::realtime:
            return "realtime";
        case client_type::cached:
            return "cached";
        default:
            return std::to_string(static_cast<int>(type));
    }
}

struct rpp_unique_description // уникальное описание РПП
{
    uint32_t id;                            // идентификатор РПП
    std::string name_ui;                    // имя РПП
    peleng_enums::rpp_formation formation;  // исполнение РПП
};

struct ellipse_params {
    float olo;         // относительная линейная ошибка (в км)
    float ellipse_w;   // размер эллипса рассеивания от экватора на север (в км)
    float ellipse_d;   // размер эллипса рассеивания по линии экватора (в км)
};

// регистрация источника результатов
// клиент -> сервер
struct register_result_source
{
    enum
    {
        message = register_result_source_msg,
        protocol = protocol_code,
    };
    std::string host_name;      // имя хоста (компьютера)
    std::string program_name;   // имя программы
    client_type type;           // тип клиента

    std::optional<rpp_unique_description> rpp; // описание РПП, который формирует результаты
};

enum class server_type
{
    primary,   // Основной сервер (отправлет session_commit)
    secondary  // Подписчик (не отправляет session_commit)
};

inline std::string to_string(server_type type)
{
    switch (type)
    {
        case server_type::primary:
            return "primary";
        case server_type::secondary:
            return "secondary";
        default:
            return std::to_string(static_cast<int>(type));
    }
}

// регистрация получателя результатов
// сервер -> клиент
struct register_result_handler
{
    enum
    {
        message = register_result_handler_msg,
        protocol = protocol_code,
    };
    std::string host_name;  // имя хоста (компьютера)
    server_type type;

    std::optional<rpp_unique_description> rpp; // описание РПП, который принимает результаты
};

// пополнение списка видов передач  (может быть отправлено несколько раз)
// может быть отправлена частями, для обновления используется ключ - поле name
struct signal_information
{
    enum
    {
        message = signal_information_msg,
        protocol = protocol_code,
    };
    std::vector<signal_type_declaration> signal_types;
};

// информация о параметрах вида передачи  (может быть отправлено несколько раз)
// может быть отправлена частями, для обновления используется ключ - поле name
struct signal_parameters
{
    enum
    {
        message = signal_parameters_msg,
        protocol = protocol_code,
    };
    std::string signal_type;                        // код вида передачи
    std::vector<parameter_declaration> parameters;  // параметры
};

// информация о радиоданных (может быть отправлено несколько раз)
// может быть отправлена частями, для обновления используется ключ - поле name
struct radiodata_information
{
    enum
    {
        message = radiodata_information_msg,
        protocol = protocol_code,
    };
    std::vector<parameter_declaration> radiodata_types;
};

enum class receive_mode
{
    none,
    usb,
    lsb,
    am,
    fm,
};

inline std::string to_string(receive_mode mode)
{
    switch (mode)
    {
        case receive_mode::none:
            return "none";
        case receive_mode::usb:
            return "usb";
        case receive_mode::lsb:
            return "lsb";
        case receive_mode::am:
            return "am";
        case receive_mode::fm:
            return "fm";
        default:
            return std::to_string(static_cast<int>(mode));
    }
}

// начало сеанса
struct session_start
{
    enum
    {
        message = session_start_msg,
        protocol = protocol_code,
    };
    std::string host_name;     //имя компьютера
    std::string program_name;  // имя программы
    std::string post_name;     // имя поста
    id_t session_id;           // идентификатор сеанса
    receive_mode mode;         // режим работы приёмника
    int64_t frequency;         // частота
    ns_time_t time_start;      // время начала сеанса
    std::string signal_type;   // вид передачи (код вида передачи)
    uint32_t task_id;          // идентификатор задания (0 - не задано)
    std::string radionet_name; // имя радиосети
};

// окончание сеанса
struct session_end
{
    enum
    {
        message = session_end_msg,
        protocol = protocol_code,
    };
    id_t session_id;     // идентификатор сеанса
    ns_time_t time_end;  // время окончания сигнала
    bool save_session;   // сохранять результат
};
// подтверждение получения сеанса
struct session_commit
{
    enum
    {
        message = session_commit_msg,
        protocol = protocol_code,
    };
    id_t session_id;  // идентификатор сеанса
};

// информация о новом файле
struct session_file
{
    enum
    {
        message = session_file_msg,
        protocol = protocol_code,
    };
    id_t session_id;              // идентификатор сеанса
    std::string file_name;        // имя файла (можно с частью пути)
    std::vector<char> file_data;  // данные файла
    std::vector<std::string>
        file_tags;  //дополнительная информация для группировки файлов
};

// тип параметров
using param_t = std::variant<int64_t, double, ns_time_t, std::string>;

// полученный параметр
struct session_parameter
{
    enum
    {
        message = session_parameter_msg,
        protocol = protocol_code,
    };
    id_t session_id;        // идентификатор сеанса
    uint32_t block_number;  // номер блока (для праметра сеанса - 0)
    std::string name;       // имя параметра
    param_t value;          // значение
};

namespace radiodata_names  // значние session_radiodata::name
{
const char* const from = "from";  //отправитель
const char* const to = "to";      // получатель
const char* const text = "text";  // сообщение
}  // namespace radiodata_names

// радиоданные
struct session_radiodata
{
    enum
    {
        message = session_radiodata_msg,
        protocol = protocol_code,
    };
    id_t session_id;        // идентификатор сеанса
    uint32_t block_number;  // номер блока (для праметра сеанса - 0)
    uint32_t group_number;  // номер группы параметров
    std::string name;       // имя радиоданных
    std::string code;       // код радиоданных
    param_t value;          // значение
};

struct coordinate
{
    int32_t latitude;   // широта в секундах
    int32_t longitude;  // долгота в секундах
};

// пеленг
struct peleng_result
{
    rpa_id_t rpa_id;          // идентификатор РПА
    coordinate rpa_position;  // расположение РПА

    float angle;                      // угол пеленга
    std::vector<float> place_angles;  // углы места
        // вероятность попадания в допустимый интервал ошибки, в %
    float probability;
    float forecasted_error;  // предсказанная ошибка, в градусах
    uint16_t range;          // дальность (в км) (для ДАС)
    ns_time_t time_from;  // время начала пеленгования пеленгатором (в нс) UTC
    ns_time_t time_to;  // время окончания пеленгования пеленгатором (в нс) UTC

    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
    int32_t freq_neg_delta;
    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
    int32_t freq_pos_delta;
    // идентификатор радиоизлучения (заполняется при демодуляции на пеленгаторе)
    std::string iri;
};

// место
struct place_result
{
    coordinate position;  // координаты

    uint16_t olo;         // относительная линейная ошибка (в км)
    uint16_t ellipse_w;   // размер эллипса рассеивания от экватора на север (в км)
    uint16_t ellipse_d;   // размер эллипса рассеивания по линии экватора (в км)
    float ellipse_angle;  // наклон эллипса рассеивания (в градусах)

    // список идентификаторов пеленгов на основе которых посчитано место
    std::vector<rpa_id_t> place_peleng_index;
    std::string region_name;        // имя региона
    peleng_enums::place_type type;  // тип места

    float veracity;  // достоверность места от 0 до 100.0

    // уточнения для оло и эллипса рассеивания
    // если не заполнено, то брать параметры выше с типом uint16_t
    std::optional<ellipse_params> ellipse_params_ext;
};

struct rpa_declaration
{
    rpa_id_t rpa_id;                            // идентификатор РПА
    std::string protocol_name;                  // имя протокола
    std::string rpa_name_ui;                    // Имя РПА
    peleng_enums::rpa_type type;                // тип пеленгатора

    rpp_unique_description rpp;                 // описание РПП
};

struct error_result
{
    rpa_id_t rpa_id;                      // идентификатор РПА
    peleng_enums::peleng_error category;  // тип ошибки
    int32_t code;                         // код ошибки
    std::string message;                  // описание ошибки
};

// команда на пеленгование с результатами и местами
// клиент -> сервер
struct session_command
{
    enum
    {
        message = session_command_msg,
        protocol = protocol_code,
    };
    id_t session_id;  // идентификатор сеанса
    id_t command_id;  // уникальный номер команды
    uint32_t scom;    // суточный номер команды

    uint64_t freq;  // центральная частота (Гц)

    // разница между нижней границей частотоного диапазона и центральной частотой (в Гц)
    int32_t freq_neg_delta;
    // разница между верхней границей частотоного диапазона и центральной частотой (в Гц)
    int32_t freq_pos_delta;

    ns_time_t time_from;  // время начала пеленгования (в нс) UTC
    ns_time_t time_to;    // время окончания пеленгования (в нс) UTC

    std::vector<rpa_declaration> rpa_declarations;  // список РПА
    std::vector<peleng_result> pelengs;             // список пеленгов
    std::vector<place_result> places;               // список мест
    std::vector<error_result> errors;               // ошибки

    uint32_t block_number;  // номер блока (для праметра сеанса - 0)
};

enum class error_type : int
{
    data_error,    // ошибка в переданных данных
    server_error,  // ошибка на сервере (может быть исправлена)
    protocol_error, // ошибка в последовательности сообщений (в протоколе)
};

inline std::string to_string(error_type type)
{
    switch (type)
    {
        case error_type::data_error:
            return "data_error";
        case error_type::server_error:
            return "server_error";
        case error_type::protocol_error:
            return "protocol_error";
        default:
            return std::to_string(static_cast<int>(type));
    }
}

// сообщение об ошибке записи сеанса
// сервер -> клиент
struct session_error
{
    enum
    {
        message = session_error_msg,
        protocol = protocol_code,
    };
    id_t session_id;  // идентификатор сеанса
    uint32_t error_code;
    error_type type;
    std::string error_message;
};

enum class server_status_type
{
    ok,
    error,
};

inline std::string to_string(server_status_type type)
{
    switch (type)
    {
        case server_status_type::ok:
            return "ok";
        case server_status_type::error:
            return "error";
        default:
            return std::to_string(static_cast<int>(type));
    }
}

// общий статус сервера
// сервер -> клиент
struct server_status
{
    enum
    {
        message = server_status_msg,
        protocol = protocol_code,
    };
    server_status_type status;
};

// подтверждение получения команды
// сервер -> клиент
struct command_commit
{
    enum
    {
        message = command_commit_msg,
        protocol = protocol_code,
    };
    id_t command_id;  // уникальный номер команды
};

// сообщение об ошибке записи команды
// сервер -> клиент
struct command_error
{
    enum
    {
        message = command_error_msg,
        protocol = protocol_code,
    };
    id_t command_id;  // идентификатор команды
    uint32_t error_code;
    error_type type;
    std::string error_message;
};
// клиент -> сервер
// отправляется, когда все команды на пеленгование отправлены
struct session_completed
{
    enum
    {
        message = session_completed_msg,
        protocol = protocol_code,
    };
    id_t session_id;
};

// клиент -> сервер
// запрос на повторную обработку сеанса
struct session_repeate
{
    enum
    {
        message = session_repeate_msg,
        protocol = protocol_code,
    };
    id_t session_id;
};

}  // namespace results_protocol
