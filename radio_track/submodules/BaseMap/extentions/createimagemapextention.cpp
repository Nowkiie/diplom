#include "createimagemapextention.h"

using namespace qmapcontrol;

CreateImageMapExtention::CreateImageMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent)
{
    filename_ = "";
    pressed_ = false;
    geometry_ = NULL;
}

CreateImageMapExtention::~CreateImageMapExtention()
{
}

void CreateImageMapExtention::start()
{
    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateImageMapExtention::stop(MapExtention *sender)
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

QString CreateImageMapExtention::getFileName()
{
    return filename_;
}

void CreateImageMapExtention::setFileName(QString filename)
{
    filename_ = filename;
}

void CreateImageMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (pressed_)
    {
        geometry_->setCoordinate(coordinate);
        e->accept();
    }
}

void CreateImageMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    pressed_ = true;

    geometry_ = new Image(coordinate.x(), coordinate.y(), filename_, "");
    layer_->addGeometry(geometry_);
    e->accept();
}

void CreateImageMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
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
