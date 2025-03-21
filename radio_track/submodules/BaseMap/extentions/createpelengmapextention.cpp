#include "createpelengmapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include "geometries/pelengbase.h"

using namespace qmapcontrol;

CreatePelengMapExtention::CreatePelengMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent), pressed_(false), geometry_(NULL)
{
    color_ = Qt::black;
}

CreatePelengMapExtention::~CreatePelengMapExtention()
{
}

void CreatePelengMapExtention::start()
{
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreatePelengMapExtention::stop(MapExtention *sender)
{
    if (geometry_)
    {
        layer_->removeGeometry(geometry_);
        delete geometry_;
        geometry_ = NULL;
    }
    pressed_ = false;
    mapControl_->disconnect(this);

    GeometryCreatorMapExtention::stop(sender);
}

void CreatePelengMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreatePelengMapExtention::getColor()
{
    return color_;
}

void CreatePelengMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (!pressed_) return;

    qreal azimuth, length;
    PelengBase::pelengParamsByPoints(geometry_->position(), coordinate, azimuth, length);

    geometry_->setAzimuth(azimuth);
    geometry_->setLength(length);

    e->accept();
    mapControl_->update();
}

void CreatePelengMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (!pressed_)
    {
        pressed_ = true;

        if (geometry_)
        {
            layer_->removeGeometry(geometry_);
            delete geometry_;
        }
        geometry_ = new Peleng(coordinate, 0, 0, "", QPen(color_));
        layer_->addGeometry(geometry_);

        e->accept();
    }
}

void CreatePelengMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (!pressed_) return;

    emit(objectCreated(this, geometry_));
    geometry_ = NULL;
    pressed_ = false;

    e->accept();
}
