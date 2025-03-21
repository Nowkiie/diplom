#pragma once
//ПРОТОКОЛ получения клиентами информации от  AKS ITS сервера с машины ИТС
#include <memory>
#include <vector>
#include <optional>

namespace AKSITSProtocol
{
const char* const protocolName = "AKSITSProtocol";
const unsigned short protocolCode = 29;

// все строки в протоколе в utf8

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
    int64_t time;  //(в мс) UTC - юникстайм! Время начала работы на частоте
};

struct ServerRegister
{
    enum
    {
        message = messageServerRegister,
        protocol = protocolCode,
    };
    std::string host;  //имя машины
    std::string name;  //имя программы
};

// сообщение с информацией (сервер -> клиент)
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
