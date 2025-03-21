#pragma once
#include <string>
#include <cstdint>
#include "shared/PelengEnums.h"

namespace identification_protocol
{
const int protocol_code = 25;
const char* const protocol_name = "identification_protocol";

enum peleng_protocol_codes
{
    identification_message_msg,
};

// пакеты обмена клиент<->сервер
//------------------------------------
// запрос на регистрацию
// клиент -> сервер
//------------------------------------
struct identification_message
{
    enum
    {
        message = identification_message_msg,
        protocol = protocol_code,
    };
    int32_t rpp_id;                             // идентификатор локального РПП
    std::string rpp_name_ui;                    // имя локального РПП
    peleng_enums::rpp_formation rpp_formation;  // исполнение РПП
};

}  // namespace identification_protocol
