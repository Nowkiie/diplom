#include "zoomleveldistances.h"

namespace qmapcontrol
{

ZoomLevelDistances::ZoomLevelDistances()
    : scaleDistanceList_({
        5000000, 2500000, 1000000,
        500000, 250000, 100000,
        50000, 25000, 10000,
        5000, 2500, 1000,
        500, 250, 100,
        50, 25, 10})
{
}

bool ZoomLevelDistances::hasDistance(int zoomLevel) const
{
    return 0 <= zoomLevel && zoomLevel < scaleDistanceList_.size();
}

int ZoomLevelDistances::distanceFor(int zoomLevel) const
{
    return scaleDistanceList_.at(zoomLevel);
}

} // namespace qmapcontrol