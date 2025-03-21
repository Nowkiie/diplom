#include "geometryprocessormapextention.h"

namespace qmapcontrol
{
    Geometries::Geometries(QObject *parent)
        : QObject(parent)
        , nextID_(0)
    {
    }

    Geometries::~Geometries()
    {
    }

    void    Geometries::beginGeometriesUpdate()
    {
        lock_.lock();
    }

    void    Geometries::endGeometriesUpdate()
    {
        lock_.unlock();

        emit(updated());
    }

    int        Geometries::getGeometryProcessorID()
    {
        return nextID_++;
    }

    void    Geometries::setCache(int processorID, QVariant value)
    {
        cache_[processorID] = value;
    }

    bool    Geometries::isCached(int processorID) const
    {
        return cache_.contains(processorID);
    }

    QVariant    Geometries::cache(int processorID) const
    {
        return cache_[processorID];
    }
}
