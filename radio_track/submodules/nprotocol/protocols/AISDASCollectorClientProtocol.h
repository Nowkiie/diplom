#pragma once
//�������� �� AcasrServer � AISDASCollector
#include <memory>
#include <vector>
#include <optional>

namespace AISDASCollectorClientProtocol
{
const char* const protocolName = "AISDASCollectorClientProtocol";
const unsigned short protocolCode = 21;

// ��� ������ � ��������� � utf8

enum MessageType
{
    messageClient = 0,
    messageServer
};

enum class SourceType : int
{
    acars = 0,
    hfdl
};

struct Coordinates
{
    float longitude{};  // ������� (�������)
    float latitude{};   // ������ (�������)
};

struct AcarsMessage
{
    char mode;
    std::string addr;  //���.�����
    char ack;
    std::string label;
    char bid;
    std::string no;
    std::string fid;  //����
    std::string txt;  //Max 220 ��������
};

struct AcarsServerMessageStruct
{
    uint64_t time;     //(� ��) UTC - ���������! ����� ������ ���������
    AcarsMessage msg;  //������� ��������� ACARS
    int icao;
    //������, ������� ���� ������� � ���������
    std::optional<Coordinates> coordinates;
    std::optional<float> course;      //���� � ��������,
    std::optional<int32_t> speed;     //�������� � �����
    std::optional<int32_t> altitude;  //������ � �����
    std::optional<uint64_t>
        airTime;  //(� ��) UTC - ���������! �����, ������������ � ���������
    SourceType source;
};

// ��������� � ����������� (������ -> ������)
struct ServerMessage
{
    enum
    {
        message = messageServer,
        protocol = protocolCode,
    };
    std::string host;  //��� ������
    std::string name;  //��� ���������
};

// ����� � ������� (������ -> ������)
struct ClientMessage
{
    enum
    {
        message = messageClient,
        protocol = protocolCode,
    };
    uint64_t Id{};  //��� ������� �� �������� ��������� 0
    AcarsServerMessageStruct AcarsServerMsg;
};

}  // namespace AISDASCollectorClientProtocol
