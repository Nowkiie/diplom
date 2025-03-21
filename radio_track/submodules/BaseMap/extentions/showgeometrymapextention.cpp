#include "showgeometrymapextention.h"

using namespace qmapcontrol;

ShowGeometryMapExtention::ShowGeometryMapExtention(MapControl *mapControl, QObject *parent)
: MapExtention(mapControl, parent)
{
}

ShowGeometryMapExtention::~ShowGeometryMapExtention()
{
}

void ShowGeometryMapExtention::start()
{
    QList<Geometry*> geos = geos_->geometries(processorID());
    if (geos.count() == 0) return;

    // вычисляем центр ограничивающего прямоугольника
    QPointF p = geos.at(0)->boundingBox().center();

    mapControl_->setView(p);
}

