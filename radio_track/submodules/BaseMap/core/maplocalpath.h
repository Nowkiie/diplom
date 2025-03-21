#ifndef MAPLOCALPATH_H
#define MAPLOCALPATH_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QPixmap>
#include <QStringList>
#include <QThread>
#include "imagemanager.h"
#include "maploader.h"
#include "maplocalworker.h"

#include <QTime>


namespace qmapcontrol
{
    class ImageManager;

    class MapLocalPath : public MapLoader
    {
        Q_OBJECT

    public:
        MapLocalPath(const QString &filePath, QObject* parent = nullptr);
        ~MapLocalPath();

        void loadImage(int x, int y, int z) override;

        /*!
         * checks if the given url is already loading
         * @param url the url of the image
         * @return boolean, if the image is already loading
         */
        bool imageIsLoading(int x, int y, int z) override;

        /*!
         * Aborts all current loading threads.
         * This is useful when changing the zoom-factor, though newly needed images loads faster
         */
        void abortLoading();

    private:
        void loadNext();
        MapLocalPath& operator=(const MapLocalPath& rhs);
        MapLocalPath(const MapLocalPath& old);

        QThread mapLoaderThread;
        MapLocalWorker mapLoaderWorker;
        QStringList loadingQueue;
        QStringList loadingPassed;
    signals:
        void loadImageSignal(int x, int y, int z);

    private slots:
        void fileLoaded(const QPixmap pixmap, int x, int y, int z);
        void loadError(int x, int y, int z);

    };

}
#endif
