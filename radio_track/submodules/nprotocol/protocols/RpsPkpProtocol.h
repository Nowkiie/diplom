#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace pkp
{
const char* const protocol_name = "RpsPkpProtocol";
const unsigned short protocol_code = 44;

enum message_types
{
    msg_register_client,
    msg_command_request,
    msg_command_answer,
    msg_signal_type_table,
    msg_map_info_table,
    msg_map_request,
    msg_map_answer,
    msg_status_message,
};

enum class peleng_error : int32_t
{
    not_found = 1,     // Не обнаружено (НО)
    transport_error,   // Ошибка передачи (ОКС)
    service_error,     // Ошибка службы пеленгования (НПК)
    pelengator_error,  // Ошибка пеленгатора (РЗ, ОРП, НДК)
};


struct register_client
{
    enum
    {
        protocol = protocol_code,
        message = msg_register_client
    };
    std::string host_name;
    std::string post_name;
};

struct coordinate
{
    int latitude;   // координаты в секундах
    int longitude;  // координаты в секундах
};

struct peleng_result
{
    uint32_t rpp_id;  // идентификатор РПП
    coordinate rpa_position;  // положение РПА
    float angle;              // пеленг
};

struct place_result
{
    coordinate position;  // координаты места
    uint16_t ellipse_w;  // ширина эллипса рассеивания (в км)
    uint16_t ellipse_d;  // длина эллипса рассеивания (в км)
    float ellipse_angle;  // наклон эллипса рассеивания (в градусах)
    std::string region_name;  // имя региона
};

struct error_result
{
    uint32_t rpp_id;  // идентификатор РПП
    peleng_error error_type;
};

struct command_request
{
    enum
    {
        protocol = protocol_code,
        message = msg_command_request
    };
    uint32_t request_id;
    uint64_t frequency;  // частота
    int vp_code;         // номер вп
};

struct command_answer
{
    enum
    {
        protocol = protocol_code,
        message = msg_command_answer
    };
    uint32_t request_id;
    uint64_t frequency;  // частота
    int vp_code;         // номер вп
    uint64_t time_from;  // время начала пеленгования (в нс) UTC
    uint64_t time_to;  // время окончания пеленгования (в нс) UTC
    uint32_t scom;
    uint32_t local_rpp;  // идентификатор локального РПП
    std::vector<peleng_result> pelengs;
    std::vector<place_result> places;
    std::vector<error_result> errors;
};

struct signal_type_item
{
    int vp_code;       // номер вп
    std::string name;  // имя ВП
};

struct signal_type_table
{
    enum
    {
        protocol = protocol_code,
        message = msg_signal_type_table
    };
    std::vector<signal_type_item> signal_types;  // список ВП
};

struct map_info_item
{
    std::string name;  // имя карты (латиница)
    std::string description;  // описание карты для пользователя
    int layers;               // количество солёв
};
struct map_info_table
{
    enum
    {
        protocol = protocol_code,
        message = msg_map_info_table
    };
    std::vector<map_info_item> map_infos;  // инфо о карте
};

struct map_request
{
    enum
    {
        protocol = protocol_code,
        message = msg_map_request
    };
    uint32_t request_id;  // идентификатор запроса
    std::string name;     // имя карты
    int x;
    int y;
    int z;
    int l;
};

struct map_answer
{
    enum
    {
        protocol = protocol_code,
        message = msg_map_answer
    };
    uint32_t request_id;  // идентификатор запроса
    std::string name;     // имя карты
    int x;
    int y;
    int z;
    int l;
    std::vector<char> data;  // данные тайла (картинка)
};


struct status_message
{
    enum
    {
        protocol = protocol_code,
        message = msg_status_message
    };
    bool has_errors;
};

}  // namespace pkp
