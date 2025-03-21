#include "createregionmapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"

using namespace qmapcontrol;

CreateRegionMapExtention::CreateRegionMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent), pressed_(false), geometry_(NULL)
{
    color_ = Qt::black;
    fillStyle_ = Qt::BrushStyle::NoBrush;
}

CreateRegionMapExtention::~CreateRegionMapExtention()
{
}

void CreateRegionMapExtention::start()
{
    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateRegionMapExtention::stop(MapExtention *sender)
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

void CreateRegionMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreateRegionMapExtention::getColor()
{
    return color_;
}

void CreateRegionMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (!pressed_) return;

    QRectF rect = geometry_->rect();
    rect.setBottomRight(coordinate);
    geometry_->setRect(rect);

    e->accept();
    mapControl_->update();
}

void CreateRegionMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
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
        geometry_ = new Region(QRectF(coordinate, coordinate), fillStyle_, "", QPen(color_));
        layer_->addGeometry(geometry_);

        e->accept();
    }
}

void CreateRegionMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (!pressed_) return;

    emit(objectCreated(this, geometry_));
    geometry_ = NULL;
    pressed_ = false;

    e->accept();
}

void CreateRegionMapExtention::setFillStyle(Qt::BrushStyle fillStyle)
{
    fillStyle_ = fillStyle;
}

Qt::BrushStyle CreateRegionMapExtention::getFillStyle()
{
    return fillStyle_;
}
