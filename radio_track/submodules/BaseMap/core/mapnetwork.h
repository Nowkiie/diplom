#ifndef MAPNETWORK_H
#define MAPNETWORK_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QPixmap>
#include <QDateTime>
#include <QTimer>
#include "imagemanager.h"
#include "maploader.h"
#include <stdint.h>

namespace qmapcontrol
{
    class ImageManager;
    /*!
    *    Класс для загрузки изображения карт из сети
    */
    class MapNetwork : public MapLoader
    {
        Q_OBJECT

        struct LoadingItem
        {
            QString url;
            uint64_t requestTime;
            int z;
            int x;
            int y;
        };
    public:
        MapNetwork(QString mapName, int layer, QObject* parent = nullptr);
        ~MapNetwork();

        virtual void loadImage(int x, int y, int z) override;

        virtual bool imageIsLoading(int x, int y, int z) override;

        virtual void abortLoading() override;
    signals:
        void loadImageRequest(QString mapName, int x, int y, int z, int layer);
    public slots:
        void tileRecieved(const QString mapName,
            int x, int y, int z, int layer, const QPixmap image);
        void tileEmpty(const QString mapName, int x, int y, int z, int layer);
    private slots:
        void removeOldLoadingItems();
    private:
        MapNetwork& operator=(const MapNetwork& rhs);
        MapNetwork(const MapNetwork& old);
        uint64_t nowMsTime();
        QString mapName_;
        int layer_;
        QList<LoadingItem> lodingItems;
        QTimer timeoutTimer;
    };
}
#endif
