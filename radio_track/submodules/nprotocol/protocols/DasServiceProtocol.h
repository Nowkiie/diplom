#pragma once
/*****************************************************************/ /**
 * \file   DasServiceProtocol.h
 * \brief  Протокол клиента ДАС/АИС/ACARS
 * 
 * \author КрашенинниковКН
 * \date   June 2022
 *********************************************************************/
#include <cstdint>
#include <optional>
#include <vector>
#include <map>
#include <string>
#include <optional>

namespace das_service_protocol
{
const char* const protocol_name = "das_service_protocol";
const int protocol_code = 53;

#define DAS_SERVICE_PROTOCOL_MESSAGE(MSG) \
    enum                                  \
    {                                     \
        message = message_type::MSG,      \
        protocol = protocol_code,         \
    };

enum message_type
{
    start_real_time_msg,
    stop_real_time_msg,
    get_history_msg,

    available_objects_parameters_msg,
    objects_msg,
    remove_objects_msg,
    change_object_request_msg,

    available_rules_parameters_msg,
    state_rules_changed_msg,
    state_rules_removed_msg,
    append_state_rule_request_msg,
    change_state_rule_request_msg,
    remove_state_rule_request_msg,

    dictionary_objects_changed_msg,
    dictionary_objects_removed_msg,
    append_dictionary_object_msg,
    change_dictionary_objects_msg,
    remove_dictionary_objects_msg,

    get_pulse_history_msg,
    pulse_msg,

};
using id_t = uint64_t;
using ns_time_t = int64_t;
using coordinate_t = int32_t;  //геогрфические координаты в милисекундах
enum class object_type_t : int
{
    unknown,   //неизвестный
    ship,      //корабль
    airplane,  //самолет
    radar      //радар
};
enum class state_t : int
{
    unknown,   //неизвестный
    ignore,    //игнориуемый
    important  //важный
};
struct param_t
{
    std::string name;
    std::string value;
};
struct object_info_t
{
    object_type_t type;
    state_t state;
    std::vector<param_t> reference_params;  //справочные параметры
};
struct object_t
{
    id_t id;
    std::vector<param_t> calculated_params;  //принятые,рассчитанные параметры
    object_info_t info;
};

struct point_t
{
    coordinate_t lattitude;
    coordinate_t longitude;
};
enum source_type
{
    acars,       // Декодирование сообщений ACARS
    ais,         // Декодирование сообщений АИС
    das,         // Декодирование сообщений ДАС
    das_peleng,  // ДАС пеленгатор
    gmt_position,  // Расчёт места через пересечение ГМТ
    impulse_time_position,  // Расчёт места методом Молокова
};

struct position_t
{
    point_t coordinates;  //географические координаты
    source_type source;   //источник данных
};

struct peleng_t
{
    point_t rpp;         //местоположение пеленгатора
    source_type source;  //источник данных
    float azimuth;       //пеленг
};

struct height_t
{
    int64_t value_ft;    //высота в футах
    source_type source;  //источник данных
};

struct object_point_t
{
    ns_time_t time_utc;
    std::optional<position_t> position;
    std::optional<peleng_t> peleng;
    std::optional<height_t> height;
    std::optional<float> power;  //мощность сигнала в папугаях
    std::optional<float> speed;   //скорость в км/ч
    std::optional<float> course;  //скорость в градусах
};

struct object_item_t
{
    object_t object;
    std::vector<object_point_t> points;
};

// клиент->сервер
struct start_real_time
{
    DAS_SERVICE_PROTOCOL_MESSAGE(start_real_time_msg)
};
// клиент->сервер
struct stop_real_time
{
    DAS_SERVICE_PROTOCOL_MESSAGE(stop_real_time_msg)
};

// клиент->сервер
struct get_history
{
    DAS_SERVICE_PROTOCOL_MESSAGE(get_history_msg)
    id_t query_id;
    ns_time_t start_time;
    ns_time_t stop_time;
    bool emulated = false;
};

// клиент->сервер
struct change_object_request
{
    DAS_SERVICE_PROTOCOL_MESSAGE(change_object_request_msg)
    id_t object_id;
    object_info_t info;
};

// сервер->клиент
struct objects_data
{
    DAS_SERVICE_PROTOCOL_MESSAGE(objects_msg)
    std::optional<uint64_t> query_id;
    bool last_answer =
        false;  //Говорит о том что более ответом на запрос не будет
    std::vector<object_item_t> objects;
};

// сервер->клиент
struct remove_objects_data
{
    DAS_SERVICE_PROTOCOL_MESSAGE(remove_objects_msg)
    std::vector<id_t> objects_ids;
};

//сервер->клиент
/** Приходит при подключении серверу. Список параметров, доступных для использования при редактировании объекта*/
struct object_parameter_description_t
{
    object_type_t type;
    std::string name;
    std::string ui_name;
    bool is_editable = false;
};
struct available_objects_parameters
{
    DAS_SERVICE_PROTOCOL_MESSAGE(available_objects_parameters_msg)
    std::vector<object_parameter_description_t> params;
};

//Редактирование правил важности
using wildcard_t = std::string;
struct rule_item_t
{
    std::string param_name;
    wildcard_t values;
};
struct state_rule_t
{
    std::string rule_name;
    state_t state;  //определяет правило для объектов(важный, игнорируемый)
    std::vector<rule_item_t>
        rule_items;  //Wildcard выражения объединяются по "И"
};

//клиент->сервер
struct append_state_rule_request
{
    DAS_SERVICE_PROTOCOL_MESSAGE(append_state_rule_request_msg)
    state_rule_t rule;
};
//клиент->сервер
struct change_state_rule_request
{
    DAS_SERVICE_PROTOCOL_MESSAGE(change_state_rule_request_msg)
    id_t id;
    state_rule_t rule;
};
//клиент->сервер
struct remove_state_rule_request
{
    DAS_SERVICE_PROTOCOL_MESSAGE(remove_state_rule_request_msg)
    std::vector<id_t> rules;
};
//сервер->клиент
/** Приходит при подключении серверу. Список параметров, доступных для использования при создании правил*/
struct rule_parameter_description_t
{
    std::string name;
    std::string ui_name;
};
struct available_rules_parameters
{
    DAS_SERVICE_PROTOCOL_MESSAGE(available_rules_parameters_msg)
    std::vector<rule_parameter_description_t> params;
};
/** Приходит в первый моменти и при изменении правил */
struct state_rules_changed
{
    DAS_SERVICE_PROTOCOL_MESSAGE(state_rules_changed_msg)
    std::map<id_t, state_rule_t> rules;
};
//сервер->клиент
struct state_rules_removed
{
    DAS_SERVICE_PROTOCOL_MESSAGE(state_rules_removed_msg)
    std::vector<id_t> removed_rules;
};

//Работа с запросчиками
using mlat_t =
    int64_t;  // млаты = std::chrono::duration<int64_t, std::ratio<1ll, 12000000ll>>;
enum class packet_type_t : int
{
    mode_1 = 1,
    mode_2 = 2,
    mode_a = 3,
    mode_c = 4,
    mode_s = 5,
    mode_4 = 6,
};
enum class pulse_type_t : int
{
    PIID,
    P090,
    P1030
};
struct pulse_t
{
    pulse_type_t pulse_type;
    std::optional<point_t> point;
    mlat_t mlat1;
    mlat_t mlat2;
    packet_type_t packet_type;
};
// клиент->сервер
struct get_pulse_history
{
    DAS_SERVICE_PROTOCOL_MESSAGE(get_pulse_history_msg)
    id_t id_query;
    ns_time_t start_time;
    ns_time_t stop_time;
};
// сервер->клиент
struct pulse_data
{
    DAS_SERVICE_PROTOCOL_MESSAGE(pulse_msg)
    id_t id_query;
    std::vector<pulse_t> pulses;
};
}  // namespace das_service_protocol
