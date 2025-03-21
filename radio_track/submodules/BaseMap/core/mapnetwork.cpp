
#include "mapnetwork.h"
#include "urlconverter.h"
#include <QWaitCondition>
#include <chrono>

namespace qmapcontrol
{

    const int tileLoadTimeout = 2000; //ms

    MapNetwork::MapNetwork(QString mapName, int layer, QObject* parent)
        : MapLoader(parent)
        , mapName_(mapName)
        , layer_(layer)
    {

        timeoutTimer.setInterval(tileLoadTimeout / 2);
        connect(&timeoutTimer, &QTimer::timeout, 
            this, &MapNetwork::removeOldLoadingItems);
        timeoutTimer.start();
    }

    MapNetwork::~MapNetwork()
    {

    }
    void MapNetwork::loadImage(int x, int y, int z)
    {
        LoadingItem item;
        item.requestTime = nowMsTime();
        item.x = x;
        item.y = y;
        item.z = z;
        lodingItems.push_back(item);
        emit loadImageRequest(mapName_, x, y, z, layer_);
    }
    void MapNetwork::abortLoading()
    {
        // не можем прервать загрузку
    }
    void MapNetwork::tileRecieved(const QString mapName,
        int x, int y, int z, int layer, const QPixmap image)
    {
        if (mapName != mapName_ || layer != layer_)
            return;

        for (auto iter = lodingItems.begin(); iter != lodingItems.end();++iter)
        {
            if (iter->x == x && iter->y == y && iter->z == z)
            {
                emit imageLoaded(image, x, y, z);
                lodingItems.erase(iter);
                if (lodingItems.empty())
                {
                    emit imageLoadingComplited();
                }
                break;
            }
        }

    }
    void MapNetwork::tileEmpty(const QString mapName, 
        int x, int y, int z, int layer)
    {
        if (mapName != mapName_ || layer != layer_)
            return;

        for (auto iter = lodingItems.begin(); iter != lodingItems.end(); ++iter)
        {
            if (iter->x == x && iter->y == y && iter->z == z)
            {
                lodingItems.erase(iter);
                emit imageEmpty(x, y, z);
                if (lodingItems.empty())
                {
                    emit imageLoadingComplited();
                }
                break;
            }
        }

    }
    void MapNetwork::removeOldLoadingItems()
    {
        if (lodingItems.empty())
            return;
        for (auto iter = lodingItems.begin(); iter != lodingItems.end();)
        {
            if (nowMsTime() > iter->requestTime + tileLoadTimeout)
            {
                iter = lodingItems.erase(iter);
                continue;
            }
            ++iter;
        }
        if (lodingItems.empty())
            emit imageLoadingComplited();
    }

    uint64_t MapNetwork::nowMsTime()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    bool MapNetwork::imageIsLoading(int x, int y, int z)
    {
        for (const auto & item : lodingItems)
        {
            if (item.x == x && item.y == y && item.z == z)
                return true;
        }
        return false;
    }

}
