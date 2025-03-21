#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QObject>
#include <QPixmap>
/*!
    Poylov-MV

    virtual class for implementing different loaders
*/
namespace qmapcontrol
{
    /*!
    *    Виртуальный класс для механизма загрузки изображения карт из источника
    *    @author Maxim Poylov
    */
    class MapLoader : public QObject
    {
        Q_OBJECT

    public:
        MapLoader(QObject *parent = nullptr) : QObject(parent) {}
        virtual ~MapLoader() { };

        virtual void loadImage(int x, int y, int z) = 0;

        /*!
         * checks if the given url is already loading
         * @param url the url of the image
         * @return boolean, if the image is already loading
         */
        virtual bool imageIsLoading(int x, int y, int z) = 0;

        /*!
         * Aborts all current loading threads.
         * This is useful when changing the zoom-factor, though newly needed images loads faster
         */
        virtual void abortLoading() = 0;
    signals:

        /**
         \brief Событие загрузки изображения
        
         \param pixmap  The pixmap.
         \param url     URL of the document.
         */

        void imageLoaded(const QPixmap pixmap, int x, int y, int z);
        void imageEmpty(int x, int y, int z);
        /** \brief Image loading complited */
        void imageLoadingComplited();
    };
}
#endif
