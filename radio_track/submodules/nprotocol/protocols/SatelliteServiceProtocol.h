#pragma once

#include <vector>
#include <optional>
#include "serializable.hpp"

namespace SatelliteServiceProtocol
{
const char* const protocolName = "Satellite_service_protocol";
const unsigned short protocolCode = 18;

// ��� ������ � ��������� � utf8
using Id = uint64_t;
enum MessageType
{
    messageTleInfo = 0,
    messageTleQuery,
    messageTleAnswer,
    messageSatelliteTleQuery,
    messageSatelliteTleAnswer
};
//��� �������������� ��������� ������
enum class SourceType : int
{
    tle = 1
};

struct TLE
{
    std::string name;
    std::string line2;
    std::string line3;
};

struct SatelliteTleInfo
{
    std::string name;  //��� ��������
    Id id{};     //����� �������� � ���� ������ NORAD
};

struct TLEInfo
{
    time_t time;  //����� ������ TLE. UTC
    TLE tle;      //tle �����
};

// ��������� � ����������� (������ -> ������)
struct MessageTleInfo
{
    enum
    {
        message = messageTleInfo,
        protocol = protocolCode,
    };
    std::vector<SatelliteTleInfo> avaliableSatellite;  //��������� ��������
};

// ������ ������(������ -> ������)
struct MessageTleQuery
{
    enum
    {
        message = messageTleQuery,
        protocol = protocolCode,
    };
    Id id{};  //����� ��������
    time_t time{};    //������������ �����, UTC
};
// ������ ������(������ -> ������)
struct MessageSatelliteTleQuery
{
    enum
    {
        message = messageSatelliteTleQuery,
        protocol = protocolCode,
    };
    Id id{};  //����� ��������
};

// ����� � ������� (������ -> ������)
struct MessageTleAnswer
{
    enum
    {
        message = messageTleAnswer,
        protocol = protocolCode,
    };
    std::optional<TLEInfo> tleInfo;
};

// ����� � ������� (������ -> ������)
struct MessageSatelliteTleAnswer
{
    enum
    {
        message = messageSatelliteTleAnswer,
        protocol = protocolCode,
    };
    Id satelliteId{};
    std::vector<TLEInfo> tleInfo;
};

}  // namespace AISDASProtocol
