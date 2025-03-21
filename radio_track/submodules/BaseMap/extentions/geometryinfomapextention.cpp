#include "geometryinfomapextention.h"
#include "geometries/point.h"

#include <QMessageBox>

#include "geometries/sector.h"
#include "geometries/place.h"
#include "geometries/peleng.h"
#include "geometries/ellipse.h"
#include "geometries/image.h"
#include "geometries/rpp.h"
#include "geometries/region.h"

//---------------------------------------------------------------------------------------------------------------------------------
// GeometryInformationExtractor
//---------------------------------------------------------------------------------------------------------------------------------

void GeometryInformationExtractor::visit(qmapcontrol::Place *object)
{
    info_ = "Place";
}

void GeometryInformationExtractor::visit(qmapcontrol::Image *object)
{
    info_ = "Image";
}

void GeometryInformationExtractor::visit(qmapcontrol::Peleng *object)
{
    info_ = "Peleng";
}

void GeometryInformationExtractor::visit(qmapcontrol::Ellipse *object)
{
    info_ = "Ellipse";
}

void GeometryInformationExtractor::visit(qmapcontrol::Rpp *object)
{
    info_ = "Rpp";
}

void GeometryInformationExtractor::visit(qmapcontrol::Region *object)
{
    info_ = "Region";
}

void GeometryInformationExtractor::visit(qmapcontrol::Sector *object)
{
    info_ = "Sector";
}

void GeometryInformationExtractor::visit(qmapcontrol::Point *object)
{
    info_ = QString("Point: Position {%1, %2}").arg(object->position().x()).arg(object->position().y());
}

void GeometryInformationExtractor::visit(qmapcontrol::Geometry *object)
{
    QRectF r = object->boundingBox();
    info_ = QString("Geometry: BoundingBox {%1, %2} {%3 %4}").arg(r.left()).arg(r.top()).arg(r.width()).arg(r.height());
}

QString GeometryInformationExtractor::info()
{
    return info_;
}




//---------------------------------------------------------------------------------------------------------------------------------
// GeometryInfoMapExtention
//---------------------------------------------------------------------------------------------------------------------------------

GeometryInfoMapExtention::GeometryInfoMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: MapExtention(mapControl, parent), layer_(layer)
{
    connect(mapControl_, SIGNAL(mouseDoubleClickEvent(QMouseEvent*, QPointF)), this, SLOT(mouseDoubleClickEvent_(QMouseEvent*, QPointF)));
}

GeometryInfoMapExtention::~GeometryInfoMapExtention()
{
}

void GeometryInfoMapExtention::start()
{
}

void GeometryInfoMapExtention::stop(MapExtention *sender)
{
}


void GeometryInfoMapExtention::mouseDoubleClickEvent_(QMouseEvent* e, QPointF coordinate)
{
    point_ = coordinate;

    // определяем выбранный объект
    qmapcontrol::Point p(point_.x(), point_.y());
    foreach(qmapcontrol::Geometry *g, geos_->geometries(processorID()))
    {
        if (g->Touches(&p, layer_->mapadapter()))
        {
            QRectF r = g->boundingBox();
            GeometryInformationExtractor gie;
            g->accept(&gie);
            QString info = gie.info();
    
            QMessageBox::information(
                NULL,
                "Object information",
                info,
                QMessageBox::StandardButton::Ok
                );
            break;
        }
    }
}

