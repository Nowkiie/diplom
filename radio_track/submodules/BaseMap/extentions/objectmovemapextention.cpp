#include "objectmovemapextention.h"

#include "selectormapextention.h"

#include <geometries/rpp.h>

using namespace qmapcontrol;

// --------------------------------------------------------------------------------------------------------------------------------
// class MoveGeometryVisitor
// --------------------------------------------------------------------------------------------------------------------------------
MoveGeometryVisitor::MoveGeometryVisitor(QPointF delta)
    : delta_(delta)
{
}

void MoveGeometryVisitor::visit(Place* object) {}

void MoveGeometryVisitor::visit(Image* object) {}

void MoveGeometryVisitor::visit(Peleng* object) {}

void MoveGeometryVisitor::visit(Ellipse* object) {}

void MoveGeometryVisitor::visit(Rpp* object)
{
    QPointF pos = object->position();
    object->setCoordinate(pos + delta_);
}

void MoveGeometryVisitor::visit(Region* object) {}

void MoveGeometryVisitor::visit(Sector* object) {}

void MoveGeometryVisitor::visit(Point* object) {}

void MoveGeometryVisitor::visit(Geometry* object) {}

// --------------------------------------------------------------------------------------------------------------------------------
// class ObjectMoveMapExtention
// --------------------------------------------------------------------------------------------------------------------------------

ObjectMoveMapExtention::ObjectMoveMapExtention(MapControl* mapControl,
                                               qreal radius,
                                               Qt::MouseButton actionButton,
                                               QObject* parent)
    : CheckableMapExtention(mapControl, parent)
    , radius_(radius)
    , pressed_(false)
    , actionButton_(actionButton)
    , geometry_(NULL)
{
}

ObjectMoveMapExtention::ObjectMoveMapExtention(MapControl* mapControl,
                                               qreal radius, QObject* parent)
    : ObjectMoveMapExtention(mapControl, radius, Qt::RightButton, parent)
{
}

ObjectMoveMapExtention::~ObjectMoveMapExtention() {}

void ObjectMoveMapExtention::start()
{
    setEnableStopOnKeyboard(true);

    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this,
            SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)), Qt::DirectConnection);
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this,
            SLOT(mousePressEvent_(QMouseEvent*, QPointF)),
            Qt::DirectConnection);
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this,
            SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)),
            Qt::DirectConnection);

    CheckableMapExtention::start();
}

void ObjectMoveMapExtention::stop(MapExtention* sender)
{
    pressed_ = false;
    mapControl_->disconnect(this);

    mapControl_->update();

    CheckableMapExtention::stop(sender);
}

void ObjectMoveMapExtention::process(QList<Geometry*> geometries)
{
    if (geometries.count() == 0)
        return;

    // для каждого объекта проверяем пересечение ограничивающего прямоугольника с выделением
    geometry_ = NULL;
    SelectorVisitor v(initPosition_,
                      radius_ / (qreal)pow(2, mapControl_->currentZoom()));
    foreach (Geometry* g, geometries)
    {
        // сдвигаем ограничивающий прямоугольник в сторону выделения (коррекция для смежных карт)
        g->accept(&v);
        if (v.touches())
        {
            geometry_ = g;

            break;
        }
    }
    if (!geometry_)
        pressed_ = false;
}

void ObjectMoveMapExtention::mouseMoveEvent_(QMouseEvent* evnt,
                                             QPointF coordinate)
{
    if (pressed_)
    {
        if (geometry_)
        {
            MoveGeometryVisitor v(coordinate - initPosition_);
            geometry_->accept(&v);
            initPosition_ = coordinate;
            evnt->accept();
        }

        if (evnt->buttons() != actionButton_)
        {
            stop(this);
            return;
        }
    }
}

void ObjectMoveMapExtention::mousePressEvent_(QMouseEvent* evnt,
                                              QPointF coordinate)
{
    if (evnt->button() != actionButton_)
        return;

    pressed_ = true;
    initPosition_ = coordinate;
    process(geos_->geometries(processorID()));
    if (geometry_ != NULL)
        emit objectSelected(geometry_);
}

void ObjectMoveMapExtention::mouseReleaseEvent_(QMouseEvent* evnt,
                                                QPointF coordinate)
{
    if (evnt->button() != actionButton_)
        return;

    pressed_ = false;

    if (geometry_)
    {
        // оповещаем об изменении положения объекта
        emit(objectMoved(geometry_));

        geometry_ = NULL;
    }
}
