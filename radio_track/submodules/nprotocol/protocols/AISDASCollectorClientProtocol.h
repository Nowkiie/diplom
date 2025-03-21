#pragma once
//ПРОТОКОЛ ОТ AcasrServer К AISDASCollector
#include <memory>
#include <vector>
#include <optional>

namespace AISDASCollectorClientProtocol
{
const char* const protocolName = "AISDASCollectorClientProtocol";
const unsigned short protocolCode = 21;

// все строки в протоколе в utf8

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
    float longitude{};  // долгота (градусы)
    float latitude{};   // широта (градусы)
};

struct AcarsMessage
{
    char mode;
    std::string addr;  //рег.номер
    char ack;
    std::string label;
    char bid;
    std::string no;
    std::string fid;  //Рейс
    std::string txt;  //Max 220 символов
};

struct AcarsServerMessageStruct
{
    uint64_t time;     //(в нс) UTC - юникстайм! Время приема сообщения
    AcarsMessage msg;  //Целиком сообщение ACARS
    int icao;
    //Данные, которые были найдены в сообщении
    std::optional<Coordinates> coordinates;
    std::optional<float> course;      //Курс в градусах,
    std::optional<int32_t> speed;     //Скорость в узлах
    std::optional<int32_t> altitude;  //Высота в футах
    std::optional<uint64_t>
        airTime;  //(в нс) UTC - юникстайм! Время, содержащееся в сообшении
    SourceType source;
};

// сообщение с информацией (сервер -> клиент)
struct ServerMessage
{
    enum
    {
        message = messageServer,
        protocol = protocolCode,
    };
    std::string host;  //имя машины
    std::string name;  //имя программы
};

// ответ с данными (клиент -> сервер)
struct ClientMessage
{
    enum
    {
        message = messageClient,
        protocol = protocolCode,
    };
    uint64_t Id{};  //для ответов по подписке заполнено 0
    AcarsServerMessageStruct AcarsServerMsg;
};

}  // namespace AISDASCollectorClientProtocol
