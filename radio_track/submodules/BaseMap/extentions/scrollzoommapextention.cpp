#include "scrollzoommapextention.h"

using namespace qmapcontrol;

ScrollZoomMapExtention::ScrollZoomMapExtention(MapControl *mapControl, QObject *parent)
    : PersistentMapExtention(mapControl, parent)
{
    connect(mapControl_, SIGNAL(mouseWheelEvent(QWheelEvent*)), this, SLOT(mouseWheelEvent_(QWheelEvent*)));
}

ScrollZoomMapExtention::~ScrollZoomMapExtention()
{
}

void ScrollZoomMapExtention::mouseWheelEvent_(QWheelEvent *e)
{
    if (e->delta() < 0)
    {
        mapControl_->zoomOut(e->pos());
    }
    else
    {
        mapControl_->zoomIn(e->pos());
    }
}
