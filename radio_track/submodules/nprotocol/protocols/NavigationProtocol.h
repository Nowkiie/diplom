#pragma once

#include <memory>
#include <vector>
#include <set>
#include <string>
#include <cstdint>

namespace dns_protocol
{
const int protocol_code = 30;
const char* const protocol_name = "navigation_protocol";

using ns_time_t = uint64_t;  // unix-time в наносекундах
using angle_t = int;         // географический угол в секундах

enum dns_protocol_codes
{
    device_info_msg,  //информирование клиента о возможностях устройства 
    set_data_request_msg,  //запрос истории и подписка на текущие изменения
    time_answer_msg,         //история и текущие изменения времени СЕВ
    coord_answer_msg,        //история и текущие изменения координат
    heading_answer_msg       //история и текущие изменения курса
};

enum receive_flags : uint32_t
{
    receive_time = 1,    // получать метки СЕВ
    receive_coordinate,  // получать координаты
    receive_heading,     // получать курс
};

struct device_info  //описание устройства
{
    std::string name;
    bool is_coordinate;
    bool is_time;
    bool is_heading;
};

struct coordinate_t
{
    angle_t latitude;   // широта сек, <0 Ю.Ш.
    angle_t longitude;  // долгота сек, <0 З.Д.
};
struct time_answer  //единичный ответ от устройства
{
    ns_time_t recv_time;  //время приема команды
    ns_time_t sync_time;  //время на устройстве
};
struct coordinate_answer  //единичный ответ от устройства
{
    ns_time_t recv_time;  //время приема команды
    coordinate_t coordinate;
};
struct heading_answer  //единичный ответ от устройства
{
    ns_time_t recv_time;  //время приема команды
    angle_t heading;      // курс, сек
};
//------------------------------------
// изменилось состояние устройств навигации
// клиент <- сервер
//------------------------------------
struct device_info_message
{
    enum
    {
        message = device_info_msg,
        protocol = protocol_code,
    };
    device_info info;
};

//------------------------------------
// запрос на получение истории данных от устройства
//и подписка на изменение данных
// клиент -> сервер
//------------------------------------
struct set_data_request_message
{
    enum
    {
        message = set_data_request_msg,
        protocol = protocol_code,
    };
    std::set<receive_flags> task_type;  // тип запрашиваемых данных(receive_flags)
    ns_time_t time_from;                // время начала (в нс) UTC
};


//------------------------------------
// информаци об истории устройства и изменение текущих данных
// клиент <- сервер
//------------------------------------
struct time_answer_message
{
    enum
    {
        message = time_answer_msg,
        protocol = protocol_code,
    };
    std::vector<time_answer> data;
};
//------------------------------------
// информаци об истории устройства и изменение текущих данных
// клиент <- сервер
//------------------------------------
struct coordinate_answer_message
{
    enum
    {
        message = coord_answer_msg,
        protocol = protocol_code,
    };
    std::vector<coordinate_answer> data;
};
//------------------------------------
// информаци об истории устройства и изменение текущих данных
// клиент <- сервер
//------------------------------------
struct heading_answer_message
{
    enum
    {
        message = heading_answer_msg,
        protocol = protocol_code,
    };
    std::vector<heading_answer> data;
};

}  // namespace dns_protocol
