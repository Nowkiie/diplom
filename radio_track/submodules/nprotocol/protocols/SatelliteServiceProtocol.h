#pragma once

#include <vector>
#include <optional>
#include "serializable.hpp"

namespace SatelliteServiceProtocol
{
const char* const protocolName = "Satellite_service_protocol";
const unsigned short protocolCode = 18;

// все строки в протоколе в utf8
using Id = uint64_t;
enum MessageType
{
    messageTleInfo = 0,
    messageTleQuery,
    messageTleAnswer,
    messageSatelliteTleQuery,
    messageSatelliteTleAnswer
};
//тип запрашиваемого источника данных
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
    std::string name;  //имя спутника
    Id id{};     //Номер спутника в базе данных NORAD
};

struct TLEInfo
{
    time_t time;  //время пакета TLE. UTC
    TLE tle;      //tle пакет
};

// сообщение с информацией (сервер -> клиент)
struct MessageTleInfo
{
    enum
    {
        message = messageTleInfo,
        protocol = protocolCode,
    };
    std::vector<SatelliteTleInfo> avaliableSatellite;  //доступные спутники
};

// запрос данных(клиент -> сервер)
struct MessageTleQuery
{
    enum
    {
        message = messageTleQuery,
        protocol = protocolCode,
    };
    Id id{};  //номер спутника
    time_t time{};    //интересующее время, UTC
};
// запрос данных(клиент -> сервер)
struct MessageSatelliteTleQuery
{
    enum
    {
        message = messageSatelliteTleQuery,
        protocol = protocolCode,
    };
    Id id{};  //номер спутника
};

// ответ с данными (сервер -> клиент)
struct MessageTleAnswer
{
    enum
    {
        message = messageTleAnswer,
        protocol = protocolCode,
    };
    std::optional<TLEInfo> tleInfo;
};

// ответ с данными (сервер -> клиент)
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
