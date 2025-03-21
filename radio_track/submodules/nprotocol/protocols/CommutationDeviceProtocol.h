#pragma once
#include <string>
#include <variant>
#include <vector>
#include <map>
#include <optional>

namespace commutation_device_protocol
{
const char* const protocol_name = "CommutationDeviceProtocol";
const unsigned short protocol_code = 45;

using device_id_t = int;
using parameter_name = std::string;
using parameter_value = std::variant<std::string, int, float>;
enum class parameter_type : int
{
    intType = 0,
    floatType,
    stringType,
    boolType
};

struct value_description  //Описание возможных значений параметра
{
    parameter_value value;
    std::string value_ui;
};

struct parameter_description
{
    std::string name;
    std::string name_ui;  //имя в графическом интерфейсе
    std::string description;  //описание, Tooltip для виджета
    std::vector<value_description> values;  //список возможных значений
    std::optional<parameter_value> default_value;  //значение по умолчанию
    std::optional<parameter_value>
        max_inclusive;  //максимальное значение (для числовых типов)
    std::optional<parameter_value>
        min_inclusive;  //минимальное значение (для числовых типов)
    parameter_type type;  //тип данных (int\string\...)
    bool isSystem;  //видимость для пользователя true-невидима
    bool isEditable;
};

struct device_description
{
    std::string type;
    std::string name_ui;
    std::vector<parameter_description> stateParameters;
};

enum message_type
{
    msg_server_description = 1,
    msg_device_connect_state_changed,
    msg_device_param_changed,
    msg_set_device_param
};
//сервис->клиент
struct server_description
{
    enum
    {
        protocol = protocol_code,
        message = msg_server_description
    };
    std::string server_name;
    std::map<device_id_t, device_description> devices;
};
//сервис->клиент
struct device_connect_state_changed
{
    enum
    {
        protocol = protocol_code,
        message = msg_device_connect_state_changed
    };
    device_id_t device_id;
    bool connect_state;
};
//сервис->клиент
struct device_param_changed
{
    enum
    {
        protocol = protocol_code,
        message = msg_device_param_changed
    };
    device_id_t device_id;
    parameter_name param_name;
    parameter_value param_value;
};
//клиент->сервер
struct set_device_param
{
    enum
    {
        protocol = protocol_code,
        message = msg_set_device_param
    };
    device_id_t device_id;
    parameter_name param_name;
    parameter_value param_value;
};

}  // namespace commutation_device_protocol
