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
        SETTINGS_LIST, //��������� ��������
        SETTINGS_SET //��������� �������� (�� �����������)
    };

    SERIALIZABLE_STRUCT(SettingsElement,
        (std::string, optionName), //��� ��������� 
        (std::string, optionValue) //�������� ��������� (utf8)
    );

    SERIALIZABLE_STRUCT_MESSAGE(SettingsList, SETTINGS_LIST,
        (std::vector<SettingsElement>, settingsList)     //������ ��������
    );
    SERIALIZABLE_STRUCT_MESSAGE(SettingsSet, SETTINGS_SET,
        (std::vector<SettingsElement>, settingsList)     //������ ��������
    );
}

#undef CURRENT_PROTOCOL
