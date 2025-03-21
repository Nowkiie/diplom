#pragma once

#include <string>
#include <vector>

namespace radiodata_rules_protocol
{

const char* const protocol_name = "RadiodataRules";
const int protocol_code = 43;

#define RADIODATA_RULES_PROTOCOL_MESSAGE(MSG) \
    enum                                      \
    {                                         \
        message = message_type::MSG,          \
        protocol = protocol_code,             \
    };

enum message_type
{
    rules_changed_msg,
    set_rules_msg,
    remove_rules_msg
};

struct radiodata_key
{
    std::string sourceName;
    std::string paramName;
};

struct radiodata_rule
{
    std::string name;
    std::string nameUi;
    bool checkInTask{false};
    bool registrNewInTask{false};
    std::string code;
    std::string sourceName;
    std::string paramName;
    std::string paramNameUi;
    bool isUser{true};
};

//	сервер->клиент
// Оповещение об изменении правил
struct rules_changed
{
    RADIODATA_RULES_PROTOCOL_MESSAGE(rules_changed_msg)
    std::vector<radiodata_rule> inserted;  // данные
    std::vector<radiodata_rule> updated;  // данные
    std::vector<radiodata_key> removed;  // данные
};

// клиент->сервер
// установка правил
struct set_rules
{
    RADIODATA_RULES_PROTOCOL_MESSAGE(set_rules_msg)

    std::vector<radiodata_rule> data;  // данные
};

// клиент->сервер
// установка правил
struct remove_rules
{
    RADIODATA_RULES_PROTOCOL_MESSAGE(remove_rules_msg)

    std::vector<radiodata_key> data;  // данные
};

#undef RADIODATA_RULES_PROTOCOL_MESSAGE

}  // namespace radiodata_rules_protocol
