#ifndef MAPLOCALWORKER_H
#define MAPLOCALWORKER_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QPixmap>
#include <QStringList>
#include "imagemanager.h"
#include "maploader.h"

#include <qwaitcondition.h>
#include "maplocalindexfile.h"

/**
        Poylov-MV
 */
namespace qmapcontrol
{
    /*!
    *    Класс для фоновой загрузки изображений карты
    *    @author Maxim Poylov
    */
    class MapLocalWorker : public QObject
    {
        Q_OBJECT
    public:
        MapLocalWorker(const QString &filePath, QObject *parent = 0);
        ~MapLocalWorker();

    public slots:
        void start();
        void loadImage(int x, int y, int z);
    signals:
        void fileLoaded(const QPixmap pixmap, int x, int y, int z);
        void loadError(int x, int y, int z);
    private:
        QString filePath;
        //кластеризованные индексы выпилены, т.к. не доделаны и падают
        IndexFile *indexFile;
    };
}
#endif
