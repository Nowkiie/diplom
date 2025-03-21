#include "BeginPosition.h"
#include <geometries/place.h>

using namespace track;

void BeginPosition::drawObjects(qmapcontrol::Layer* layer)
{
    if (own_point_)
    {
        const QPen drawPen(Qt::blue);
        layer->addGeometry(new qmapcontrol::Place(
            QPointF(own_point_.value().longitude().to_degree(),
                    own_point_.value().latitude().to_degree()),
            10, "", qmapcontrol::Point::Middle, drawPen));
    }
}

void BeginPosition::clearObjects()
{
    if (own_point_)
    {
        own_point_ = std::nullopt;
    }
}

QString BeginPosition::controllerName()
{
    return "OwnPosition";
}

void BeginPosition::setOwnPoint(earth_math::earth_point own_point)
{
    own_point_ = own_point;
}

std::optional<earth_math::earth_point> BeginPosition::ownPoint() const
{
    return own_point_;
}