#include "selectormapextention.h"

#include <geometries/rpp.h>

using namespace qmapcontrol;

// --------------------------------------------------------------------------------------------------------------------------------
// class SelectorVisitor
// --------------------------------------------------------------------------------------------------------------------------------
SelectorVisitor::SelectorVisitor(QPointF coordinate, qreal radius)
: coord_(coordinate)
{
    result_ = false;
    radius_ = radius * radius;
}

void SelectorVisitor::visit(Place *object)
{
}

void SelectorVisitor::visit(Image *object)
{
}

void SelectorVisitor::visit(Peleng *object)
{
}

void SelectorVisitor::visit(Ellipse *object)
{
}

void SelectorVisitor::visit(Rpp *object)
{
    QPointF p = (object->position() - coord_);
    result_ = (p.x() * p.x() + p.y() * p.y()) <= radius_;
}

void SelectorVisitor::visit(Region *object)
{
}

void SelectorVisitor::visit(Sector *object)
{
}

void SelectorVisitor::visit(Point *object)
{
}

void SelectorVisitor::visit(Geometry *object)
{
}

bool SelectorVisitor::touches()
{
    return result_;
}




// --------------------------------------------------------------------------------------------------------------------------------
// class SelectorMapExtention
// --------------------------------------------------------------------------------------------------------------------------------

SelectorMapExtention::SelectorMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, qreal radius, QObject *parent)
    : MapExtention(mapControl, parent), layer_(layer), radius_(radius)
{

}

SelectorMapExtention::~SelectorMapExtention()
{
}

void SelectorMapExtention::process(QList<Geometry*> geometries)
{
    if (geometries.empty()) return;

    SelectorVisitor v(coordinate_, radius_ / (qreal)pow(2, mapControl_->currentZoom()));
    for(Geometry *g: geometries)
    {
        // сдвигаем ограничивающий прямоугольник в сторону выделения (коррекция для смежных карт)

        g->accept(&v);
    }
}

void SelectorMapExtention::mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate)
{
    coordinate_ = coordinate;
}

void SelectorMapExtention::mousePressEvent_(QMouseEvent* evnt, QPointF coordinate)
{
    coordinate_ = coordinate;
    if (evnt->button() == Qt::MouseButton::LeftButton)
    {
        process(geos_->geometries(processorID()));
    }

    if (evnt->button() == Qt::MouseButton::RightButton)
    {
        process(geos_->geometries(processorID()));
    }
}
