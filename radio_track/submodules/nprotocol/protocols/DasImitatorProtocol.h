#pragma once
/*****************************************************************/ /**
 * \file   DasImitatorProtocol.h 
 * \brief  Протокол формирования задания на имитатор ДАС
 * 
 * \author КрашенинниковКН
 * \date   May 2023
 *********************************************************************/
#include <vector>
#include <string>

namespace das_imitator_protocol
{
const char* const protocol_name = "das_imitator_protocol";
const int protocol_code = 56;

#define DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(MSG) \
    enum                                             \
    {                                                \
        message = message_type::MSG,                 \
        protocol = protocol_code,                    \
    };

enum message_type
{
    availables_files_msg,
    server_state_msg,
    set_speed_msg,
    set_cyclic_msg,

    start_task_msg,
    pause_task_msg,
    stop_task_msg,
};
enum server_state_t
{
    stopped = 0,
    started,
    paused
};
struct file_description
{
    std::string name;
    time_t date;
};
struct path_description
{
    std::string name;
    std::vector<file_description> files;
    time_t start_time;
    time_t stop_time;
};
//сервер->клиент
struct availables_files
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(availables_files_msg)
    std::vector<path_description> paths;
};

//сервер->клиент
struct server_state_changed
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(server_state_msg)
    std::string com_port;
    int speed;
    server_state_t state;
    time_t current_imit_time;
    int cycles_done;
    bool is_cyclic;
    std::string task_name;
    time_t startTask;
    time_t stopTask;
};

//клиент->сервер
//ответ - server_state_changed
struct set_speed
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(set_speed_msg)
    int speed; //скорость воспроизведения в процентах от 10 до 500
};
//клиент->сервер
//ответ - server_state_changed
struct set_cyclic
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(set_cyclic_msg)
    bool is_cyclic;
};
//клиент->сервер
//ответ - server_state_changed
struct start_task
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(start_task_msg)
    std::string name;
    time_t begin_time;
    time_t end_time;
    int speed;  //скорость воспроизведения в процентах от 10 до 500
    bool is_cyclic;
};
//клиент->сервер
struct pause_task
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(pause_task_msg)
};
//клиент->сервер
struct stop_task
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(stop_task_msg)
};
}  // namespace das_imitator_protocol
