#include "createsectormapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include "geometries/pelengbase.h"

using namespace qmapcontrol;

CreateSectorMapExtention::CreateSectorMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent), geometry_(NULL)
{
    color_ = Qt::black;
    fillStyle_ = Qt::BrushStyle::NoBrush;
    state_ = SCS_Center;
}

CreateSectorMapExtention::~CreateSectorMapExtention()
{
}

void CreateSectorMapExtention::start()
{
    state_ = SCS_Center;

    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateSectorMapExtention::stop(MapExtention *sender)
{
    if (geometry_)
    {
        layer_->removeGeometry(geometry_);
        delete geometry_;
        geometry_ = NULL;
    }
    state_ = SCS_Center;
    mapControl_->disconnect(this);

    GeometryCreatorMapExtention::stop(sender);
}

void CreateSectorMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreateSectorMapExtention::getColor()
{
    return color_;
}

void CreateSectorMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (state_ == SCS_Center) return;

    geometry_->updateEnabled(false);

    QPointF from, to;
    from = geometry_->position();
    to = coordinate;

    qreal azimuth, length;
    PelengBase::pelengParamsByPoints(from, to, azimuth, length);

    if (state_ == SCS_Angle)
    {
        geometry_->setStartAzimuth(azimuth);
        geometry_->setEndAzimuth(azimuth);
    }
    else
    {
        geometry_->setEndAzimuth(azimuth);
    }
    geometry_->setLength(length);

    geometry_->updateEnabled(true);

    e->accept();
    mapControl_->update();
}

void CreateSectorMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    switch (state_)
    {
    case CreateSectorMapExtention::SCS_Center:
        {
            if (geometry_)
            {
                layer_->removeGeometry(geometry_);
                delete geometry_;
            }
            geometry_ = new Sector(coordinate, 0, 0, 0, fillStyle_, "", QPen(color_));
            layer_->addGeometry(geometry_);
            state_ = CreateSectorMapExtention::SCS_Angle;
        }
        break;
    case CreateSectorMapExtention::SCS_Angle:
        state_ = CreateSectorMapExtention::SCS_Size;
        break;
    case CreateSectorMapExtention::SCS_Size:
        {
            emit(objectCreated(this, geometry_));
            geometry_ = NULL;
            state_ = CreateSectorMapExtention::SCS_Center;
        }
        break;
    default:
        break;
    }

    e->accept();
}

void CreateSectorMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (state_ == SCS_Center) return;

    state_ = CreateSectorMapExtention::SCS_Size;

    e->accept();
}

void CreateSectorMapExtention::setFillStyle(Qt::BrushStyle fillStyle)
{
    fillStyle_ = fillStyle;
}

Qt::BrushStyle CreateSectorMapExtention::getFillStyle()
{
    return fillStyle_;
}
