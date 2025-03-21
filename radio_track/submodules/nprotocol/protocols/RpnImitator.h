#pragma once

#include "shared/PelengEnums.h"

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

namespace rpn_imitator_protocol
{
const int protocol_code = 55;
const char* const protocol_name = "rpn_imitator";

using time_t = uint32_t;        // время в секундах
using rpa_id_t = uint32_t;      // идентификатор пеленгатора
using freq_t = uint64_t;        // частота, Гц

struct coordinate_t  // координаты в градусах
{
    double latitude;  // широта
    double longitude; // долгота
};

struct freq_band_t                 // описание частотного диапазона
{
    freq_t freq_from;              // начало частотного диапазона, Гц
    freq_t freq_to;                // конец частотного диапазона, Гц
};

struct time_band_t                 // описание временного диапазона
{
    time_t time_from;              // время начала вещания с начала суток в секундах
    time_t time_to;               // время окончания вещания с начала суток в секундах
};

struct signal_info_t           // описание характеристик излучаемого сигнала
{
    freq_band_t freq;              // частотный диапазон, Гц
    std::vector<int> pi_codes;     // список ПИ, на которые будет выдаваться пеленг
    std::vector<time_band_t> times;// периоды работы излучения в секундах с начала суток
};

struct rpp_unique_description // уникальное описание РПП
{
    uint32_t id;                            // идентификатор РПП
    std::string name_ui;                    // имя РПП
    peleng_enums::rpp_formation formation;  // исполнение РПП
};

struct rpa_unique_description // уникальное описание РПА
{
    coordinate_t position;                      // координаты РПА
    rpp_unique_description rpp_description;     // описание РПП
    freq_band_t freq_band;                      // частотный диапазон работы пеленгатора
    int answer_delay_sec;                       // задержка ответа в секундах
    int respond_probability;                    // вероятность получить какой-либо ответ в принципе (с вероятность p-1 в ответ не будет ничего), %
    int found_probability;                      // вероятность получить в ответ какие-либо данные (с вероятность p-1 в ответ будет послано сообщение "Not Found"), %
    int good_respond_probability;               // вероятность получить в ответ корректные данные (с вероятность p-1 в ответ будут посланы случайные данные), %
    int max_distance;                           // радиус, в пределах которого пеленгатор дает корректный пеленг, км
    bool broken;                                // РПА регистрируется в сети, но не даёт ответы на команды
    bool enable;                                // если false, РПА не регистрируется в сети
};

struct track_point
{
    coordinate_t position;  //координаты объекта
    time_t       time_mark; //относительное время (сколько секунд прошло относительно первой отметки)
};

struct track_info //описание объекта-излучателя
{
    std::vector<signal_info_t> signal_info;     // характеристики излучаемых сигналов
    std::vector<track_point> points;            // трек движения объекта
    bool enable;                                // если false, излучатель выключен
};

enum peleng_protocol_codes
{
    rpa_infos_msg,
    tracks_msg,
};

//------------------------------------
// отправка информации о пеленгаторах
// клиент -> сервер
//-------------
struct rpa_infos_message
{
    enum
    {
        message = rpa_infos_msg,
        protocol = protocol_code,
    };
    std::vector<rpa_unique_description> rpas; //список пеленгаторов
};

//------------------------------------
// отправка описания объектов-излучателей
// клиент -> сервер
//-------------
struct tracks_message
{
    enum
    {
        message = tracks_msg,
        protocol = protocol_code,
    };
    std::vector<track_info> tracks; //список объектов-излучателей
};

}  // namespace rpn_imitator_protocol
