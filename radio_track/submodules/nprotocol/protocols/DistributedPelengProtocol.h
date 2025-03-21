#pragma once

#include <vector>
#include <set>
#include <string>
#include <cstdint>

namespace distributed_peleng_protocol
{
const int protocol_code = 49;
const char* const protocol_name = "distributed_peleng_calcer";

using ns_time_t = uint64_t;     // unix-time в наносекундах
using frequency_t = uint64_t;   // частота в Гц
using command_id_t = uint64_t;  // идентификатор команды
using calcer_id_t = uint32_t;   // идентификатор модуля расчета

enum distributed_protocol_codes
{
    register_request_msg,
    peleng_request_msg,
    peleng_answer_msg,
    thread_info_msg
};

// пакеты обмена клиент<->сервер
// тут и далее:
// -- сервер - сервис расчёта пеленгов (СРП)
// -- клиент - тот кто раздаёт задачи на пеленгование (ЦПРА2)
//------------------------------------

struct thread_info_t
{
    uint32_t calcer_id{};           //id модуля расчёта, 0 -- не задан
    int thread_worked = 0;          //потоков в работе
    int thread_all = 0;             //всего потоков
};

//описание одного вычислителя на СРП (плагина пеленгования)
struct calcer_info_t
{
    uint32_t calcer_id{};           //id модуля расчёта, 0 -- не задан
    std::set<int> pi_list;          // доступные для обработки ПИ
    uint64_t freq_from{};           // начало частотного интервала
    uint64_t freq_to{};             // конец частотного интервала;
};

struct channel_measure
{
    // разности фаз, в радианах
    float dphase{};
    // относительная амплитуда
    float amplitude{};
};

//пеленг с диагностическими данными
struct rpk_peleng_t
{
    ns_time_t time_from{};  //<- начала пеленгования пеленгатором (в нс) UTC
    ns_time_t time_to{};  //<- окончание пеленгования пеленгатором (в нс) UTC
    int32_t freq_neg_delta{}; //<-левая частотная граница пеленга
    int32_t freq_pos_delta{};  //<-правая частотная граница пеленга

    float angle{};               //<- пеленг
    std::vector<float> placeAngles;  // углы места
                                 //измерения по каналам
    std::vector<channel_measure> channelsMeasurement;
    // ОСШ по гистограмме
    float snr1{};
    // ОСШ по спектру
    float snr2{};
    //ширина диаграммы основного лепестка
    float pelengGistWidth{};
    // угол поляризации  в градусах, вертикальная 0
    float polarization{};
    // признаки ближней волны
    std::vector<float> rangeParams;
    float probability = 100;  //<-вероятность попадания в
        //  допустимый интервал ошибки, в %
    float forecastedError{};  //<предсказанная ошибка, в градусах(accuracy)
    unsigned short range{};  // дальность (в км)
};

enum class result_status : int
{
    success,             //все хорошо
    calc_peleng_error,   //ошибка расчета пеленга
    command_check_error  //неверная команда
};

// СРП регистрируется на ЦРПА2 с указанием ПИ и диапазонов, которые он может обслуживать
// сервер -> клиент
//------------------------------------
struct register_request {
    enum {
        message = register_request_msg,
        protocol = protocol_code,
    };

    std::vector<calcer_info_t> calcer_infos; //список вычислителей на сервере
    int32_t priority = 10; //приоритет, насколько активно использовать этот сервер. Чем больше цифра, тем больше команд будет на него подано
};

// посылка команды на расчёт пеленга
//------------------------------------
// клиент -> сервер
struct peleng_request
{
    enum
    {
        message = peleng_request_msg,
        protocol = protocol_code,
    };
    command_id_t command_id;
    bool hide = false;             //скрывать при отображении ####
    std::vector<char> peleng_file; //файл для расчёта, zpf
};

//------------------------------------
// посылка ответа с результатами расчёта
//------------------------------------
struct peleng_answer
{
    enum
    {
        message = peleng_answer_msg,
        protocol = protocol_code,
    };
    command_id_t command_id;
    result_status status = result_status::success;
    std::vector<rpk_peleng_t> pelengs;
};

//------------------------------------
// посылка сообщения с текущей загрузкой потоков
//------------------------------------
struct thread_info
{
    enum
    {
        message = thread_info_msg,
        protocol = protocol_code,
    };
    thread_info_t thread_info;
};

}  // namespace distributed_peleng_protocol
