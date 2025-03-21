#include "createellipsemapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include "geometries/pelengbase.h"

using namespace qmapcontrol;

CreateEllipseMapExtention::CreateEllipseMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent), geometry_(NULL)
{
    color_ = Qt::black;
    state_ = ECS_Center;
}

CreateEllipseMapExtention::~CreateEllipseMapExtention()
{
}

void CreateEllipseMapExtention::start()
{
    state_ = ECS_Center;

    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateEllipseMapExtention::stop(MapExtention *sender)
{
    if (geometry_)
    {
        layer_->removeGeometry(geometry_);
        delete geometry_;
        geometry_ = NULL;
    }
    state_ = ECS_Center;
    mapControl_->disconnect(this);

    GeometryCreatorMapExtention::stop(sender);
}

void CreateEllipseMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreateEllipseMapExtention::getColor()
{
    return color_;
}

void CreateEllipseMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (state_ == ECS_Center) return;

    QPointF from, to;
    from = geometry_->center();
    to = coordinate;

    qreal azimuth, length;
    PelengBase::pelengParamsByPoints(from, to, azimuth, length);

    length *= 360.0 / EARTH_EQUATOR_LENGTH;

    if (state_ == ECS_Angle)
    {
        qreal angle = azimuth;
        geometry_->setAngle(angle);
    }
    QSizeF s = QSizeF(length, length / 2.0);
    if (state_ == ECS_Size)
    {
        s = geometry_->size();
        s.setHeight(length);
    }


    geometry_->setSize(s);

    e->accept();
    mapControl_->update();
}

void CreateEllipseMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    switch (state_)
    {
    case CreateEllipseMapExtention::ECS_Center:
        {
            if (geometry_)
            {
                layer_->removeGeometry(geometry_);
                delete geometry_;
            }
            geometry_ = new Ellipse(coordinate, QSizeF(0, 0), 0, "", QPen(color_));
            layer_->addGeometry(geometry_);
            state_ = CreateEllipseMapExtention::ECS_Angle;
        }
        break;
    case CreateEllipseMapExtention::ECS_Angle:
        state_ = CreateEllipseMapExtention::ECS_Size;
        break;
    case CreateEllipseMapExtention::ECS_Size:
        {
            emit(objectCreated(this, geometry_));
            geometry_ = NULL;
            state_ = CreateEllipseMapExtention::ECS_Center;
        }
        break;
    default:
        break;
    }

    e->accept();
}

void CreateEllipseMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (state_ == ECS_Center) return;

    state_ = CreateEllipseMapExtention::ECS_Size;

    e->accept();
}
