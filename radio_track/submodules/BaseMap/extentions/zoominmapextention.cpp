#include "zoominmapextention.h"

using namespace qmapcontrol;

ZoomInMapExtention::ZoomInMapExtention(MapControl *mapControl, QObject *parent)
: PersistentMapExtention(mapControl, parent)
{
}

ZoomInMapExtention::~ZoomInMapExtention()
{
}

void ZoomInMapExtention::start()
{
    mapControl_->zoomIn();
}

