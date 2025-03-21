#pragma once

#include <string>
#include <cstdint>

namespace InformerPackets_v01
{
const unsigned short InformerProtocolCode = 31;
const char* const InformerProtocolName = "ManagerDNSMNS";

enum EPositionInformerMessages
{
    Registration = 1,
    RegistrationCommit,
    PositionData,
    NavigationInfo,
};

struct RegistrationStructure
{
    std::string name;
    std::string host;

    enum
    {
        protocol = InformerProtocolCode
    };
    enum
    {
        message = Registration
    };
};

struct RegistrationCommitStructure
{
    bool commited;

    enum
    {
        protocol = InformerProtocolCode
    };
    enum
    {
        message = RegistrationCommit
    };
};

// структуры ниже дублируют (без методов) аналогичные структуры
// из structs.h, чтобы не было зависимости от этого файла

struct Coordinates
{
    int latitude{-400};   // широта сек, <0 Ю.Ш.
    int longitude{-400};  // долгота сек, <0 З.Д.
};

struct Time
{
    uint64_t time;  // время в мс с начала эпохи от источника навигации
    int zoneOffset;  // смещение временной зоны (0 - если стройство не передает зону) в минутах
};

template <typename ValueType>
struct NavigationData
{
    // само значение (координаты, курс или время)
    ValueType value{};

    // может ли устройство в принципе возвращать такие данные?
    bool available{false};

    // когда были получены данные с устройства? мс с начала эпохи
    uint64_t dataReceiveTime;
};

struct NavInfoStructure
{
    std::string deviceName{};  // имя устройства
    bool deviceReady{};        // статус готовности устройства

    // системное время запроса к устройству в мс с начала эпохи
    // Оно заполняется в device.cpp при вызове метода scan
    uint64_t requestSystemTime;

    NavigationData<Coordinates> coordinates{};
    NavigationData<int> course{};       // курс, сек
    NavigationData<Time> deviceTime{};  // время от источника навигации
    NavigationData<int> speed{};        // скорость*10, км/ч

    enum
    {
        protocol = InformerProtocolCode
    };
    enum
    {
        message = NavigationInfo
    };
};
}  // namespace InformerPackets_v01
