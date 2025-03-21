#include "mapextention.h"

namespace qmapcontrol
{
    MapExtention::MapExtention(MapControl *mapControl, QObject *parent)
        : mapControl_(mapControl), QObject(parent)
    {
    }

    MapExtention::~MapExtention()
    {
    }

    MapExtention::MapExtention(const MapExtention &obj)
    {
    }

    MapExtention &MapExtention::operator =(const MapExtention &obj)
    {
        return *this;
    }

    void MapExtention::start()
    {
        emit(started(this));
    }

    void MapExtention::stop(MapExtention *sender)
    {
        // отправляем сообщение только, если исходный отправитель данный объект
        // для предотвращения повтороного отправления события
        if (this == sender) emit(done(this));
    }
}
