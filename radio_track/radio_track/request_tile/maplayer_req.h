#pragma once
#include "layer_req.h"

namespace qmapcontrol
{
class Maplayer_req : public Layer_req
{
public:
    Maplayer_req(QString layername, MapLoader* mapLoader,
                 bool takeevents = true);
};
}  // namespace qmapcontrol
