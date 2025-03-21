#include "mapextentionmanager.h"

namespace qmapcontrol
{
MapExtentionManager::MapExtentionManager(QObject* parent)
    : MapExtentionManager(true, parent)
{
}
MapExtentionManager::MapExtentionManager(bool needToStopButLast,
                                         QObject* parent)
    : QObject(parent)
    , needToStopButLast_(needToStopButLast)
{
}

MapExtentionManager::~MapExtentionManager()
{
    mapExtentions_.clear();
}

void MapExtentionManager::AddExtention(MapExtention* extention)
{
    connect(extention, SIGNAL(started(MapExtention*)), this,
            SLOT(started_(MapExtention*)));
    connect(extention, SIGNAL(done(MapExtention*)), this,
            SLOT(done_(MapExtention*)));

    mapExtentions_.append(extention);

    extention->setParent(this);
}

void MapExtentionManager::RemoveExtention(MapExtention* extention)
{
    mapExtentions_.removeAll(extention);
}

void MapExtentionManager::started_(MapExtention* extention)
{
    if (needToStopButLast_)
    {
        QListIterator<MapExtention*> it =
            QListIterator<MapExtention*>(mapExtentions_);

        while (it.hasNext())
        {
            MapExtention* e = it.next();
            if (e != extention)
                e->stop(extention);
        }
    }
}

void MapExtentionManager::done_(MapExtention* extention) {}
}  // namespace qmapcontrol
