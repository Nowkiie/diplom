#include "drawCoverage.h"
#include <geometries/region.h>

using namespace track;

void drawCoverage::drawObjects(qmapcontrol::Layer* layer)
{
    if (own_point_)
    {
        count++;
        drawBrush.setStyle(Qt::BrushStyle::SolidPattern);
        switch (weight_)
        {
            case type_track::closed:
            {
                QColor tmp;
                tmp.setRgb(255, 0, 0);
                tmp.setAlpha(130.);
                drawBrush.setColor(tmp);
                break;
            }
            case type_track::half_closed:
            {
                QColor tmp;
                tmp.setRgb(255, 255, 0);
                tmp.setAlpha(130.);
                drawBrush.setColor(tmp);
                break;
            }
            case type_track::half_open:
            {
                QColor tmp;
                tmp.setRgb(255, 153, 0);
                tmp.setAlpha(130.);
                drawBrush.setColor(tmp);
                break;
            }
            case type_track::open:
            {
                QColor tmp;
                tmp.setRgb(0, 255, 0);
                tmp.setAlpha(130.);
                drawBrush.setColor(tmp);

                break;
            }
            default:
            {
                QColor tmp;
                tmp.setRgb(0, 0, 0);
                tmp.setAlpha(130.);
                drawBrush.setColor(tmp);
                break;
            }
        }

        layer->addGeometry(new qmapcontrol::Region(
            QRectF(own_point_.value().longitude().to_degree(),
                   own_point_.value().latitude().to_degree(), 0.0021, 0.0021),
            drawBrush, "", Qt::NoPen));
    }
}

void drawCoverage::clearObjects()
{
    own_point_ = std::nullopt;
}

QString drawCoverage::controllerName()
{
    return "drawCoverage";
}

void drawCoverage::setOwnPoint(earth_math::earth_point own_point,
                               type_track weight)
{
    own_point_ = own_point;
    weight_ = weight;
    //own_point2_ = own_point2;
}

std::optional<earth_math::earth_point> drawCoverage::ownPoint() const
{
    return own_point_;
}
