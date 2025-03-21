/*
* Poylov-MV
*/

#include "maplocalpath.h"
#include "urlconverter.h"
#include <QTime>

namespace qmapcontrol
{
    MapLocalPath::MapLocalPath(const QString &filePath, QObject* parent)
        : MapLoader(parent)
        , mapLoaderWorker(filePath)
    {
        mapLoaderWorker.moveToThread(&mapLoaderThread);

        connect(&mapLoaderThread, &QThread::started, &mapLoaderWorker, 
            &MapLocalWorker::start);

        // Qt::QueuedConnection - переносит выполнение в основной поток
        connect(&mapLoaderWorker, &MapLocalWorker::fileLoaded, this, 
            &MapLocalPath::fileLoaded, Qt::QueuedConnection);

        connect(&mapLoaderWorker, &MapLocalWorker::loadError, this, 
            &MapLocalPath::loadError, Qt::QueuedConnection);

        //асинхронная передача запроса
        connect(this, &MapLocalPath::loadImageSignal, &mapLoaderWorker,
            &MapLocalWorker::loadImage, Qt::QueuedConnection);

        mapLoaderThread.start();
    }

    MapLocalPath::~MapLocalPath()
    {
        mapLoaderThread.quit();
        mapLoaderThread.wait();
    }

    void MapLocalPath::loadImage(int x, int y, int z)
    {
        // помещаем в очередь
        QString url = tilesToUrl(x, y, z, this);
        loadingQueue.push_back(url);
        //пока загружаем одновременно только один тайл
        if (loadingPassed.isEmpty())
        {
            loadNext();
        }
    }

    void MapLocalPath::abortLoading()
    {
        loadingQueue.clear();
    }

    bool MapLocalPath::imageIsLoading(int x, int y, int z)
    {
        QString url = tilesToUrl(x, y, z, this);
        return loadingQueue.contains(url) || loadingPassed.contains(url);
    }

    void MapLocalPath::fileLoaded(const QPixmap pixmap, int x, int y, int z)
    {
        // отправка события загрузки всем обработчикам
        emit imageLoaded(pixmap, x, y, z);
        QString url = tilesToUrl(x, y, z, this);
        loadingPassed.removeOne(url);
        if (loadingQueue.empty())
        {
            //все тайлы загружены
            emit imageLoadingComplited();
        }
        else
        {
            loadNext();
        }
    }
    void MapLocalPath::loadError(int x, int y, int z)
    {
        QString url = tilesToUrl(x, y, z, this);
        loadingPassed.removeOne(url);
        if (!loadingQueue.empty())
        {
            loadNext();
        }
        imageEmpty(x, y, z);
    }
    void MapLocalPath::loadNext()
    {
        if (!loadingQueue.empty())
        {
            QString url = loadingQueue.front();
            loadingPassed.push_back(url);
            loadingQueue.pop_front();
            int x, y, z;
            urlToTiles(url, x, y, z);

            emit loadImageSignal(x, y, z);
        }
    }
}
