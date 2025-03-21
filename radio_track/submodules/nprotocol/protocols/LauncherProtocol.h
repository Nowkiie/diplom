#pragma once

#include <memory>
#include <vector>
#include <optional>

namespace LauncherProtocol
{
const char* const protocolName = "LauncherProtocol";
const unsigned short protocolCode = 33;

#define LAUNCHER_HEADER(mt)       \
    enum                          \
    {                             \
        message = mt,             \
        protocol = protocolCode, \
    };

// все строки в протоколе в utf8

enum MessageType
{
    LAUNCHER_REGISTER = 0,
    LAUNCHER_UNIT_ADD,
    LAUNCHER_UNIT_REMOVE,
    LAUNCHER_UNIT_UPDATE,
    LAUNCHER_UNIT_START,
    LAUNCHER_UNIT_STOP,
    LAUNCHER_UNIT_RESTART,
    LAUNCHER_UNIT_STATE,
    LAUNCHER_REBOOT,
    LAUNCHER_SHUTDOWN,
};

// сообщение о подключенном загрузчике
struct LauncherRegister
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_REGISTER )
    std::string id;      // id (may be host name)
    std::string name;    // name (human friendly)
    std::string group;   // group
};

// сообщение об добавлении юнита
struct LauncherAddUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_ADD )
    std::string unit;
    std::vector<char> desktop;
    std::vector<char> icon;
};

// сообщение об удалении юнита
struct LauncherRemoveUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_REMOVE )
    std::string unit;
};

// сообщение об обновлении юнита
struct LauncherUpdateUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_UPDATE )
    std::string unit;
    std::vector<char> desktop;
    std::vector<char> icon;
};

// сообщение старт юнит
struct LauncherStartUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_START )
    std::string unit;    // unit name
};

// сообщение стоп юнит
struct LauncherStopUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_STOP )
    std::string unit;    // unit name
};

// сообщение рестарт юнит
struct LauncherRestartUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_RESTART )
    std::string unit;    // unit name
};

// сообщение состояние юнита
struct LauncherStateUnit
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_UNIT_STATE )
    std::string unit;    // unit name
    std::string state;   // unit state
    int32_t pid;         // pid
};

// сообщение перезагрузка
struct LauncherReboot
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_REBOOT )
};

// сообщение завершение работы
struct LauncherShutdown
{
    LAUNCHER_HEADER( MessageType::LAUNCHER_SHUTDOWN )
};

}  // namespace LauncherProtocol
