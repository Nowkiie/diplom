#include "zoomoutmapextention.h"

using namespace qmapcontrol;

ZoomOutMapExtention::ZoomOutMapExtention(MapControl *mapControl, QObject *parent)
    : PersistentMapExtention(mapControl, parent)
{
}

ZoomOutMapExtention::~ZoomOutMapExtention()
{
}

void ZoomOutMapExtention::start()
{
    mapControl_->zoomOut();
}

