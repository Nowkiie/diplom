#ifndef MAPEMPTY_H
#define MAPEMPTY_H

#include <QObject>
#include "maploader.h"


namespace qmapcontrol
{

    /** \brief Пустой класс карты */
    class MapEmpty : public MapLoader
    {
        Q_OBJECT

    public:
        MapEmpty() { };
        virtual ~MapEmpty() { };

        virtual void loadImage(int x,int y, int z) override {};
        virtual bool imageIsLoading(int x, int y, int z) override { return false;  };
        virtual void abortLoading() override {};
    };
}
#endif
