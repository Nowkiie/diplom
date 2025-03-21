#pragma once
#include "serializable.hpp"
#include <string>
#include <vector>


namespace PelengModify
{
    const char * const protocolName = "PelengModify";
    const unsigned short protocolCode = 9;

#define CURRENT_PROTOCOL protocolCode

    enum PelengatorControlMessages
    {
        CLIENT_MODIFY_REQUEST, //�������� ������� (�������) (��� -> ��)
        CLIENT_MODIFY_ANSWER //����� � �����������
    };

    typedef long long ns_time_t;

    SERIALIZABLE_STRUCT(Peleng,
        (float, angle),  // ���� �������
        (unsigned short, quality), // (accuracy) ������ �������
        (unsigned short, range),    // ��������� (� ��)    (��� ���)
        (bool, isShort),  // �������/������� 
        (ns_time_t, timeFrom),  // ����� ������ ������������ ������������ (� ��) UTC
        (ns_time_t, timeTo),  // ����� ��������� ������������ ������������ (� ��) UTC
        (int, freqNegDelta),    // ������� ����� ������ �������� ����������� ��������� � ����������� �������� (� ��)
        (int, freqPosDelta),    // ������� ����� ������� �������� ����������� ��������� � ����������� �������� (� ��)
        (std::vector<unsigned short>, placeAngles),  // ���� �����
        (std::string, iri) //������������� �������������� (����������� ��� ����������� �� �����������)
        );

    SERIALIZABLE_STRUCT(Command,
        (unsigned int, idNk),    // ������������� ������� � �� (������ ���� ��� ������� � ��������� �������)
        (int, idRo),        // ������������� �����������
        (int, idClient),    // ������������� ������� � ��
        (unsigned long long, uniqueId),
        (unsigned int, idPelengator)
        );

    SERIALIZABLE_STRUCT_MESSAGE(CommandModifyRequest, CLIENT_MODIFY_REQUEST,
        (Command, command),
        (std::vector<Peleng>, pelengs)
        );
    SERIALIZABLE_STRUCT_MESSAGE(CommandModifyAnswer, CLIENT_MODIFY_ANSWER,
        (unsigned long long, uniqueId),
        (bool, isSuccess)
        );

#undef CURRENT_PROTOCOL
}
