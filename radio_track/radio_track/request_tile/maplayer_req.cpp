#include "maplayer_req.h"
#include <adapters/localmapadapter.h>

using namespace qmapcontrol;

Maplayer_req::Maplayer_req(QString layername, MapLoader* mapLoader,
                           bool takeevents)
    : Layer_req(layername, new LocalMapAdapter(), mapLoader, Layer::MapLayer,
                takeevents)
{
}