#include "createrppmapextention.h"

using namespace qmapcontrol;

CreateRppMapExtention::CreateRppMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent)
{
    color_ = Qt::black;
    pressed_ = false;
    geometry_ = NULL;
}

CreateRppMapExtention::~CreateRppMapExtention()
{
}

void CreateRppMapExtention::start()
{
    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateRppMapExtention::stop(MapExtention *sender)
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

void CreateRppMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreateRppMapExtention::getColor()
{
    return color_;
}

QString CreateRppMapExtention::getFileName()
{
    return filename_;
}

void CreateRppMapExtention::setFileName(QString filename)
{
    filename_ = filename;
}

void CreateRppMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (pressed_)
    {
        geometry_->setCoordinate(coordinate);
        e->accept();
    }
}

void CreateRppMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    pressed_ = true;

    geometry_ = new Rpp(filename_, coordinate, 0, "", QPen(color_));
    layer_->addGeometry(geometry_);
    e->accept();
}

void CreateRppMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
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
