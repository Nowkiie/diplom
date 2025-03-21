#include "showallmapextention.h"

using namespace qmapcontrol;

ShowAllMapExtention::ShowAllMapExtention(MapControl *mapControl, QObject *parent)
    : MapExtention(mapControl, parent)
{
}

ShowAllMapExtention::~ShowAllMapExtention()
{
}

void ShowAllMapExtention::start()
{
    // вычисляем общий ограничивающий прямоугольник
    QRectF bb(0, 0, 0, 0);
    for(Geometry *g : geos_->geometries(processorID()))
    {
        bb = bb.united(g->boundingBox());
    }
    
    if (bb.width() == 0 && bb.height() == 0) return;
    
    QList<QPointF> points;
    points << bb.topLeft() << bb.topRight() << bb.bottomRight() << bb.bottomLeft();
    mapControl_->setViewAndZoomIn(points);
}
