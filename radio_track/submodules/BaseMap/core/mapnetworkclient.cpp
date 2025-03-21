#include "mapnetworkclient.h"
#include <QDebug>

using namespace qmapcontrol;

MapNetworkClient::MapNetworkClient(QObject * parent)
    : QObject(parent)
    , client(MapServerProtocol::protocolName)
    , requestId{}
    , emptyTile(1, 1)
{
    emptyTile.fill(Qt::transparent);

    connect(this, &MapNetworkClient::mapConnectedInternal,
        this, &MapNetworkClient::mapConnected, Qt::QueuedConnection);

    connect(this, &MapNetworkClient::tileRecievedInternal,
        this, &MapNetworkClient::tileRecieved, Qt::QueuedConnection);

    connect(this, &MapNetworkClient::tileEmptyInternal,
        this, &MapNetworkClient::tileEmpty, Qt::QueuedConnection);

    client.register_handler<MapServerProtocol::MapInfo,
                            MapServerProtocol::MapAnswer>(this);
}

MapNetworkClient::~MapNetworkClient()
{
    client.stop();
}

void MapNetworkClient::start()
{
    client.start();
}

void MapNetworkClient::getImage(QString mapName, int x, int y, int z, int layer)
{
    std::lock_guard<std::mutex> lg(mapLock);
    for (auto & con : connections)
    {
        if (con.name == mapName.toStdString())
        {
            MapServerProtocol::MapRequest requestMessage;
            MapServerProtocol::MapRequestEntry entry;
            requestMessage.reuestId = requestId++;
            requestMessage.mapName = con.name;
            entry.x = x;
            entry.y = y;
            entry.z = z;
            entry.layer = layer;
            requestMessage.entries.push_back(entry);
            client.send(con.id, requestMessage);
            break; //отправляем запрос только на один сервер
        }
    }
}

void MapNetworkClient::connected(nc3::point_id_t id, nc3::address_t address,
                                 nc3::port_t port)
{

}
void MapNetworkClient::disconnected(nc3::point_id_t id)
{
    std::lock_guard<std::mutex> lg(mapLock);

    for (auto iter = connections.begin(); iter != connections.end();)
    {
        if (iter->id == id)
        {
            iter = connections.erase(iter);
            continue;
        }
        ++iter;
    }
}

void MapNetworkClient::message(nc3::point_id_t id,
    const MapServerProtocol::MapInfo & info)
{
    std::lock_guard<std::mutex> lg(mapLock);
    for (const auto & mapInfo : info.mapList)
    {
        MapNetworkConnection connection;
        connection.description = mapInfo.mapDescription;
        connection.name = mapInfo.mapName;
        connection.id = id;
        connections.push_back(connection);

        mapConnectedInternal(QString::fromStdString(mapInfo.mapName),
            QString::fromStdString(mapInfo.mapDescription), mapInfo.layersCount);
    }
}

void MapNetworkClient::message(nc3::point_id_t id,
    const MapServerProtocol::MapAnswer & answer)
{
    for (const auto & entry : answer.entries)
    {
        QPixmap baseImage;
        if (entry.imageData.size())
        {
            baseImage.loadFromData(
                reinterpret_cast<const uchar*>(entry.imageData.data()),
                static_cast<uint>(entry.imageData.size()));
            tileRecievedInternal(QString::fromStdString(answer.mapName),
                entry.x, entry.y, entry.z, entry.layer, baseImage);
        }
        else
        {
            tileEmptyInternal(QString::fromStdString(answer.mapName),
                entry.x, entry.y, entry.z, entry.layer);
        }

    }

}


