#include "createorientedrppmapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"

using namespace qmapcontrol;

CreateOrientedRppMapExtention::CreateOrientedRppMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent)
: GeometryCreatorMapExtention(mapControl, layer, parent), pressed_(false), geometry_(NULL)
{
    color_ = Qt::black;
    azimuth_ = 0;
    filename_ = "";
}

CreateOrientedRppMapExtention::~CreateOrientedRppMapExtention()
{
}

void CreateOrientedRppMapExtention::start()
{
    pressed_ = false;

    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    GeometryCreatorMapExtention::start();
}

void CreateOrientedRppMapExtention::stop(MapExtention *sender)
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

void CreateOrientedRppMapExtention::setColor(QColor color)
{
    color_ = color;
}

QColor CreateOrientedRppMapExtention::getColor()
{
    return color_;
}

void CreateOrientedRppMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (!pressed_) return;

    QPointF from, to;
    from = geometry_->position();
    to = coordinate;
    qreal w, h;
    w = (to.x() - from.x());
    h = (to.y() - from.y());

    qreal radius = sqrt(w * w + h * h);
    qreal angle = -acos(w / radius) * 180.0 / M_PI;
    if (h > 0) angle = 360.0 - angle;
    geometry_->setAzimuth(90.0 - angle);

    e->accept();
    mapControl_->update();
}

void CreateOrientedRppMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
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
        geometry_ = new Rpp(filename_, coordinate, azimuth_, "", QPen(color_));
        layer_->addGeometry(geometry_);

        e->accept();
    }
}

void CreateOrientedRppMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (!pressed_) return;

    emit(objectCreated(this, geometry_));
    geometry_ = NULL;
    pressed_ = false;

    e->accept();
}

QString CreateOrientedRppMapExtention::getFileName()
{
    return filename_;
}

void CreateOrientedRppMapExtention::setFileName(QString filename)
{
    filename_ = filename;
}

qreal CreateOrientedRppMapExtention::getAzimuth()
{
    return azimuth_;
}

void CreateOrientedRppMapExtention::setAzimuth(qreal azimuth)
{
    azimuth_ = azimuth;
}
