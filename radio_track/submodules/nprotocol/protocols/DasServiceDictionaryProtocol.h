#pragma once
/*****************************************************************/ /**
 * \file   DasServiceDictionaryProtocol.h
 * \brief  Протокол для редактирвоания справочников ДАС/АИС/ACARS
 * 
 * \author КрашенинниковКН
 * \date   June 2022
 *********************************************************************/
#include <cstdint>
#include <optional>
#include <vector>
#include <map>
#include <chrono>
#include <optional>

namespace das_service_dictionary_protocol
{
const char* const protocol_name = "das_service_dictionary_protocol";
const int protocol_code = 54;

#define DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(MSG) \
    enum                                             \
    {                                                \
        message = message_type::MSG,                 \
        protocol = protocol_code,                    \
    };

enum message_type
{
    objects_changed_msg,
    objects_removed_msg,
    append_request_msg,
    change_request_msg,
    remove_request_msg
};
using id_t = uint64_t;
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

//Редактирование справочника объектов
//сервер->клиент
struct dictionary_item_t
{
    id_t id;
    object_info_t info;
};
struct objects_changed
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(objects_changed_msg)
    std::vector<dictionary_item_t> objects;
};
//сервер->клиент
struct objects_removed
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(objects_removed_msg)
    std::vector<id_t> objects;
};
//клиент->сервер
struct append_request
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(append_request_msg)
    object_info_t info;  //справочные параметры
};
//клиент->сервер
struct change_request
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(change_request_msg)
    std::vector<dictionary_item_t> objects;
};
//клиент->сервер
struct remove_request
{
    DAS_SERVICE_DICTIONARY_PROTOCOL_MESSAGE(remove_request_msg)
    std::vector<id_t> objects;
};
}  // namespace das_service_dictionary_protocol
