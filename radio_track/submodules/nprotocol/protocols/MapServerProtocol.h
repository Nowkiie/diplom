#pragma once
#include <string>
#include <vector>

namespace MapServerProtocol
{
const char* const protocolName = "MapServerNode";
const unsigned short protocolCode = 12;

enum MapServerMessages
{
    MAP_SERVER_INFO,  //информация о сервере (список карт)
    MAP_SERVER_REQUEST,  //запрос тайлов
    MAP_SERVER_ANSWER,   //ответ на запрос
    MAP_SERVER_UPDATE,  //перечитать список карт с диска
};

struct MapInfoEntry
{
    std::string mapName;  //имя карты (латиница, для внутренней идентификации)
    std::string mapDescription;  //описание карты для вывода пользователю, utf8
    unsigned int layersCount;  //количество слоёв
};

struct MapInfo
{
    enum
    {
        message = MAP_SERVER_INFO,
        protocol = protocolCode,
    };
    std::vector<MapInfoEntry> mapList;
};

//один элемент заказа тайла
//координаты индексируются от нуля
struct MapRequestEntry
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int layer;  // номер слоя (от 0)
};

//один элемент ответа на заказ тайла
struct MapAnswerEntry
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int layer;
    std::vector<char> imageData;  //данные тайла
};

struct MapRequest
{
    enum
    {
        message = MAP_SERVER_REQUEST,
        protocol = protocolCode,
    };
    unsigned long long reuestId;
    std::string mapName;
    std::vector<MapRequestEntry> entries;
};

struct MapAnswer
{
    enum
    {
        message = MAP_SERVER_ANSWER,
        protocol = protocolCode,
    };
    unsigned long long reuestId;
    std::string mapName;
    std::vector<MapAnswerEntry> entries;
};

struct MapUpdate
{
    enum
    {
        message = MAP_SERVER_UPDATE,
        protocol = protocolCode,
    };
};

}  // namespace MapServerProtocol
