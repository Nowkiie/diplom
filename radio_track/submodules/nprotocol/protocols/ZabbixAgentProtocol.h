#pragma once

#include <vector>
#include <string>
#include <optional>

namespace ZabbixAgentProtocol
{
const char* const protocolName = "Zabbix_Agent_Protocol";
const unsigned short protocolCode = 36;

enum class value_type : int
{
    floating = 0,  // FLOAT
    integer = 3,
    text = 4,  // TEXT
};
enum class trigger_priority : int
{
    not_classified = 0,
    info,
    warning,
    average,
    high,
    disaster,
};

enum MessageType
{
    TEMPLATE_REGISTER = 0,
    SEND_VALUE,
};

struct baseValue
{
    std::string groupName;      //имя группы, в которую входит переменная
    std::string variableName;   //название переменной
    std::string value;          //значение переменной (числа указываются с точкой!)
    std::optional<int64_t> errorCode; //передача кода ошибки для случая строковых триггеров
};

struct baseTrigger
{
    std::string description;    //текст триггера для отображения пользователю
    std::string function;       //специфичная функция zabbix для обработки значения переменной
    std::string expression;     //условие для сработки триггера
    trigger_priority priority{};
    std::optional<int64_t> errorCode;    //код ошибки по умолчанию
};

struct baseVariable
{
    std::string name;       //название переменной на латинице (используется для формирования имени шаблна и переменных)
    std::string nameUi;     //название переменной для отображения пользователю
    value_type type;        //тип переменной
    std::vector<baseTrigger> triggers;
};

struct baseGroup
{
    std::string name;       //название группы на латинице (используется для формирования имени шаблна и переменных)
    std::string nameUi;     //название группы для отображения пользователю
    std::vector<baseVariable> variables;
};

struct baseTemplate
{
    std::string name;       //имя шаблона на латинице (используется для формирования имени шаблна и переменных)
    std::string nameUi;     //имя шаблона для отображения пользователю
    std::string identify;   //идентификатор на латинице (используется, если программ в комплексе несколько)
    std::string identifyUi; //идентификатор для отображения пользователю
                            //если идентификатор не нужен - пустые строки
    std::vector<baseGroup> groups;
};

// регистрация шаблона
struct TemplateRegister
{
    enum
    {
        message = TEMPLATE_REGISTER,
        protocol = protocolCode,
    };

    baseTemplate zabbixTemplate;
    std::string hostName;
};

// передача данных
struct SendValue
{
    enum
    {
        message = SEND_VALUE,
        protocol = protocolCode,
    };

    std::vector<baseValue> values;
};


}  // namespace ZabbixAgentProtocol
