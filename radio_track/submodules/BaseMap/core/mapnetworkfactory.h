#pragma once
#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include "mapnetworkclient.h"
#include "mapnetwork.h"

namespace qmapcontrol
{


class MapNetworkFactory : public QObject
{
    Q_OBJECT
public:
    MapNetworkFactory(QObject * parent);
    void startConnection();
    MapLoader *makeLoader(QString mapName, 
        int layer, QObject * parent = nullptr);
signals:
    //событие обнаружения карты в сети
    void mapConnected(QString mapName, QString mapNameUi, int layersCount);
private slots:
    
private:
    MapNetworkClient networkClient;
};


}
