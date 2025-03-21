#pragma once


#include <mutex>
#include <vector>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QIODevice>
#include "nc3.hpp"
#include "protocols/MapServerProtocol.h"
namespace qmapcontrol
{
struct MapNetworkConnection
{
    nc3::point_id_t id;
    std::string name;
    std::string description;
};

class MapNetworkClient : public QObject
{
    Q_OBJECT
public:
    MapNetworkClient(QObject* parent = nullptr);
    ~MapNetworkClient();
    void start();
    void connected(nc3::point_id_t id, nc3::address_t address,
                   nc3::port_t port);
    void disconnected(nc3::point_id_t id);
    void message(nc3::point_id_t id, const MapServerProtocol::MapInfo& info);
    void message(nc3::point_id_t id,
                 const MapServerProtocol::MapAnswer& answer);
public slots:
    void getImage(QString mapName, int x, int y, int z, int layer);
signals:
    void mapConnected(QString mapName, QString mapNameUi, int layersCount);
    void tileRecieved(QString mapName, int x, int y, int z, int layer,
                      QPixmap image);
    void tileEmpty(QString mapName, int x, int y, int z, int layer);
    // для внутреннего использования
    void mapConnectedInternal(QString mapName, QString mapNameUi,
                              int layersCount);
    void tileRecievedInternal(QString mapName, int x, int y, int z, int layer,
                              QPixmap image);
    void tileEmptyInternal(QString mapName, int x, int y, int z, int layer);

private:
    QPixmap emptyTile;
    std::mutex mapLock;
    unsigned long long requestId;
    std::vector<MapNetworkConnection> connections;
    nc3::node_client client;
};

}  // namespace qmapcontrol
