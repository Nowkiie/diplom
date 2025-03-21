#include "mapnetworkfactory.h"
#include "mapnetwork.h"

using namespace qmapcontrol;




MapNetworkFactory::MapNetworkFactory(QObject * parent)
    : QObject(parent)

{
    //событие подключения
    connect(&networkClient, &MapNetworkClient::mapConnected, 
        this, &MapNetworkFactory::mapConnected);
}

void MapNetworkFactory::startConnection()
{
    networkClient.start();
}

MapLoader * MapNetworkFactory::makeLoader(QString mapName, 
    int layer, QObject * parent)
{
    MapNetwork *mapLoader = new MapNetwork(mapName, layer, parent);

    // событие заказа тайла
    connect(mapLoader, &MapNetwork::loadImageRequest, 
        &networkClient, &MapNetworkClient::getImage);

    //событие ответа с тайлом
    connect(&networkClient, &MapNetworkClient::tileRecieved,
        mapLoader, &MapNetwork::tileRecieved);

    //событие ответа без тайла
    connect(&networkClient, &MapNetworkClient::tileEmpty,
        mapLoader, &MapNetwork::tileEmpty);

    return mapLoader;
}
