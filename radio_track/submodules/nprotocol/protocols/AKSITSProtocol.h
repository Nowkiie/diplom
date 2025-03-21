#pragma once
//�������� ��������� ��������� ���������� ��  AKS ITS ������� � ������ ���
#include <memory>
#include <vector>
#include <optional>

namespace AKSITSProtocol
{
const char* const protocolName = "AKSITSProtocol";
const unsigned short protocolCode = 29;

// ��� ������ � ��������� � utf8

enum MessageType
{
    messageClient = 0,
    messageServerRegister,
    messageServerFrequencyList,
    messageServerStatus

};

struct AKSITSItem
{
    int64_t frequency;
    int64_t time;  //(� ��) UTC - ���������! ����� ������ ������ �� �������
};

struct ServerRegister
{
    enum
    {
        message = messageServerRegister,
        protocol = protocolCode,
    };
    std::string host;  //��� ������
    std::string name;  //��� ���������
};

// ��������� � ����������� (������ -> ������)
struct ServerFrequencyList
{
    enum
    {
        message = messageServerFrequencyList,
        protocol = protocolCode,
    };
    std::vector<AKSITSItem> AKSITSList;
};

struct ServerStatus
{
    enum
    {
        message = messageServerStatus,
        protocol = protocolCode,
    };
    bool AKSConnected;
    bool AKSStatus;
};

}  // namespace AKSITSProtocol
