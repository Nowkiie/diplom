#include "drawVisCoverage.h"
#include <geometries/region.h>

using namespace track;

drawVisCoverage::drawVisCoverage(double valueAlphaBase, double valueAlphaAdd)
{
    this->valueAlphaAdd = valueAlphaAdd;
    this->valueAlphaBase = valueAlphaBase;
}

void drawVisCoverage::drawObjects(qmapcontrol::Layer* layer)
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
                tmp.setRgb(128, 128, 128);
                tmp.setAlpha(0.);
                drawBrush.setColor(tmp);
                break;
            }
            case type_track::half_open:
            {
                QColor tmp;
                tmp.setRgb(0, 255, 0);
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
                break;
        }

        layer->addGeometry(new qmapcontrol::Region(
            QRectF(own_point_.value().longitude().to_degree(),
                   own_point_.value().latitude().to_degree(), 0.0021, 0.0021),
            drawBrush, "", Qt::NoPen));
    }
}

void drawVisCoverage::clearObjects()
{
    own_point_ = std::nullopt;
}

QString drawVisCoverage::controllerName()
{
    return "drawVisCoverage";
}

void drawVisCoverage::setOwnPoint(earth_math::earth_point own_point,
                                  type_track weight)
{
    own_point_ = own_point;
    weight_ = weight;
    //own_point2_ = own_point2;
}

std::optional<earth_math::earth_point> drawVisCoverage::ownPoint() const
{
    return own_point_;
}
