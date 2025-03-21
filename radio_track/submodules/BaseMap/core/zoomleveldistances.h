#ifndef ZOOMLEVELDISTANCES
#define ZOOMLEVELDISTANCES

#include <QList>

namespace qmapcontrol
{

class ZoomLevelDistances
{
public:
    ZoomLevelDistances();
    bool hasDistance(int zoomLevel) const;
    int distanceFor(int zoomLevel) const;

private:
    QList<int> scaleDistanceList_;
};

} // namespace qmapcontrol

#endif