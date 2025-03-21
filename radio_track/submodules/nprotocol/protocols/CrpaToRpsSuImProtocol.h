#pragma once

#include <string>
#include <vector>
#include "serializable.hpp"

namespace CrpaToRpsSuImProtocol
{
    const char * const crpaToRpsSuImProtocolName = "CrpaToRpsSuImProtocol";
    const unsigned short crpaToRpsSuImProtocolCode = 8;

#define CURRENT_PROTOCOL crpaToRpsSuImProtocolCode

    enum CrpaToRpsSuImMessages
    {
        PELENG,  // �������� �������
    };

    SERIALIZABLE_STRUCT(OnePeleng,
        (int, peleng), // ������
        (int, anglePlace) // ����-�����
    );

    SERIALIZABLE_STRUCT_MESSAGE(Peleng, PELENG,
        (int, sCom)  ,   // �������� ����� �������
        (int, idNk)  ,   // ����������������� ����� �������
        (int, idRo)  ,   // ������������� ��� ��������� �������
        (int, freq) ,    // �������
        (int, pi)    ,    // ��
        (std::vector<OnePeleng>, pelengs)     //������ ��������
    );
}

#undef CURRENT_PROTOCOL
