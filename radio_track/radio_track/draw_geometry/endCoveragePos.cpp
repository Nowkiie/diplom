#include "endCoveragePos.h"
#include <geometries/place.h>

using namespace track;

void endCoveragePos::drawObjects(qmapcontrol::Layer* layer)
{
    if (own_point_)
    {
        const QPen drawPen(Qt::red);
        layer->addGeometry(new qmapcontrol::Place(
            QPointF(own_point_.value().longitude().to_degree(),
                    own_point_.value().latitude().to_degree()),
            10, "", qmapcontrol::Point::Middle, drawPen));
    }
}

void endCoveragePos::clearObjects()
{
    own_point_ = std::nullopt;
}

QString endCoveragePos::controllerName()
{
    return "endCoverage";
}

void endCoveragePos::setOwnPoint(earth_math::earth_point own_point)
{
    own_point_ = own_point;
}

std::optional<earth_math::earth_point> endCoveragePos::ownPoint() const
{
    return own_point_;
}