#pragma once
#include <vector>
#include <optional>

namespace peleng_das_protocol
{
const char* const protocol_name = "peleng_das_protocol";
const unsigned short protocol_code = 41;

// все строки в протоколе в utf8

enum class id_type : char
{
    query_beam = 0,
    icao = 1,
    squawk = 2,
};

using ns_time_t = uint64_t;  // unix-time в наносекундах
using peleng_id_t = uint64_t;
struct peleng  // пеленг с сопутсвующей информацией
{
    id_type type;    // тип идентификатора
    int id;          // идентификатор
    float peleng;    // пеленг
    ns_time_t time;  // время получения сигнала
    peleng_id_t peleng_id;  // Уникальный идентификатор пеленга
};
using coordinate_t = int32_t;  //географические координаты в милисекундах
struct coordinate  // координаты в градусах
{
    coordinate_t latitude;
    coordinate_t longitude;
};

enum peleng_das_protocol_codes
{
    pelengs_package_msg,
    point_package_msg,
};

// пакеты обмена клиент<->сервер
//------------------------------------
// рассылка пакетов с пеленгами
// ДАС-пеленгатор -> ДАС-сервер
//------------------------------------
struct pelengs_package
{
    enum
    {
        message = pelengs_package_msg,
        protocol = protocol_code,
    };
    std::vector<peleng> pelengs;
};

struct peleng_position
{
    peleng_id_t peleng_id;
    std::optional<coordinate> point;
};
//------------------------------------
// ДАС-сервер -> ДАС-пеленгатор
//------------------------------------
struct point_package
{
    enum
    {
        message = point_package_msg,
        protocol = protocol_code,
    };
    std::vector<peleng_position> positions;
};

}  // namespace peleng_das_protocol
