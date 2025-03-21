#pragma once

#include <string>
#include <vector>
#include "serializable.hpp"

namespace GlobalSettings
{
    const char * const globalSettingsProtocolName = "GlobalSettings";
    const unsigned short globalSettingsProtocolCode = 7;

#define CURRENT_PROTOCOL globalSettingsProtocolCode

    enum GlobalSettingsMessages
    {
        SETTINGS_LIST, //получение настроек
        SETTINGS_SET //установка настроек (не реализовано)
    };

    SERIALIZABLE_STRUCT(SettingsElement,
        (std::string, optionName), //имя параметра 
        (std::string, optionValue) //значение параметра (utf8)
    );

    SERIALIZABLE_STRUCT_MESSAGE(SettingsList, SETTINGS_LIST,
        (std::vector<SettingsElement>, settingsList)     //список настроек
    );
    SERIALIZABLE_STRUCT_MESSAGE(SettingsSet, SETTINGS_SET,
        (std::vector<SettingsElement>, settingsList)     //список настроек
    );
}

#undef CURRENT_PROTOCOL
