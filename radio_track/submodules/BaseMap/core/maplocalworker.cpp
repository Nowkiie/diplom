/*
* Poylov-MV
*/

#include "maplocalworker.h"
#include "urlconverter.h"
#include <QTime>
#include <QThread>

namespace qmapcontrol
{
    MapLocalWorker::MapLocalWorker(const QString & filePath, QObject *parent)
        : filePath(filePath)
        , QObject(parent)
        , indexFile(nullptr)
    {
    }

    MapLocalWorker::~MapLocalWorker()
    {
        if (indexFile)
            delete indexFile;
    }

    void MapLocalWorker::loadImage(int x, int y, int z)
    {
        start();
        QPixmap pm;
        if (indexFile->getImage(pm, z, x, y))
        {
            emit fileLoaded(pm, x, y, z);
        }
        else
        {
            emit loadError(x, y, z);
        }
    }

    void MapLocalWorker::start()
    {
        //просто загрузим файл
        if (!indexFile)
        {
            indexFile = new IndexFile(filePath);
        }
    }

}
