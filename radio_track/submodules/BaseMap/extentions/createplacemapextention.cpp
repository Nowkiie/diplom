#include "createplacemapextention.h"

using namespace qmapcontrol;

CreatePlaceMapExtention::CreatePlaceMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent)
{
    color_ = Qt::black;
    radius_ = 5;
    pressed_ = false;
    geometry_ = NULL;
}

CreatePlaceMapExtention::~CreatePlaceMapExtention()
{
}

void CreatePlaceMapExtention::start()
{
    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreatePlaceMapExtention::stop(MapExtention *sender)
{
    pressed_ = false;
    if (geometry_)
    {
        layer_->removeGeometry(geometry_);
        delete geometry_;
        geometry_ = NULL;
    }
    mapControl_->disconnect(this);

    GeometryCreatorMapExtention::stop(sender);
}

void CreatePlaceMapExtention::setColor(QColor color)
{
    color_ = color;
}

void CreatePlaceMapExtention::setRadius(int radius)
{
    radius_ = radius;
}

QColor CreatePlaceMapExtention::getColor()
{
    return color_;
}

int CreatePlaceMapExtention::getRadius()
{
    return radius_;
}

void CreatePlaceMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (pressed_)
    {
        geometry_->setCoordinate(coordinate);
        e->accept();
    }
}

void CreatePlaceMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    pressed_ = true;

    geometry_ = new Place(coordinate, radius_, "", Point::Middle, QPen(color_));
    layer_->addGeometry(geometry_);
    e->accept();
}

void CreatePlaceMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (pressed_)
    {
        emit(objectCreated(this, geometry_));
        geometry_ = NULL;
    }
    pressed_ = false;
    e->accept();
}
