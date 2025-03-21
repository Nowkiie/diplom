#include "geometryconnectormapextention.h"

using namespace qmapcontrol;

GeometryConnectorCoordinateTranslator::GeometryConnectorCoordinateTranslator(qreal baseDistance, QObject *parent)
: QObject(parent)
{
    baseDistance_ = baseDistance;
    distance_ = baseDistance_;
}

GeometryConnectorCoordinateTranslator::~GeometryConnectorCoordinateTranslator()
{
}

void GeometryConnectorCoordinateTranslator::setDistance(qreal distance)
{
    distance_ = qAbs(distance);
}

qreal GeometryConnectorCoordinateTranslator::getDistance()
{
    return distance_;
}

void GeometryConnectorCoordinateTranslator::setBaseDistance(qreal distance)
{
    baseDistance_ = qAbs(distance);
}

qreal GeometryConnectorCoordinateTranslator::getBaseDistance()
{
    return baseDistance_;
}


QPointF GeometryConnectorCoordinateTranslator::translate(QPointF coordinate)
{
    QPolygonF points;

    if (geos_)
    {
        points = geos_->cache(processorID()).value<QPolygonF>();
    }


    qreal distance = distance_;
    qreal dx, dy;
    distance = distance * distance;
    QPointF pr = coordinate;

    foreach(QPointF p, points)
    {
        dx = coordinate.x() - p.x();
        dy = coordinate.y() - p.y();
        while (dx > 180) dx -= 360.0;
        while (dx < -180) dx += 360.0;
        dx = dx * dx;
        dy = dy * dy;
        dx += dy;
        if (distance > dx)
        {
            distance = dx;
            pr = p;
        }
    }

    return pr;
}

void    GeometryConnectorCoordinateTranslator::setGeometries(Geometries *geos)
{
    if (geos_) disconnect(geos_, 0, this, 0);
    GeometryProcessor::setGeometries(geos);
    if (geos_) connect(geos_, SIGNAL(updated()), this, SLOT(geometriesUpdated()));
}

void    GeometryConnectorCoordinateTranslator::geometriesUpdated()
{
    QPolygonF points;
    if (geos_)
    {
        foreach(Geometry *g, geos_->geometries(processorID()))
        {
            points << g->points();
        }
        geos_->setCache(processorID(), QVariant::fromValue(points));
    }
}

GeometryConnectorMapExtention::GeometryConnectorMapExtention(MapControl *mapControl, GeometryConnectorCoordinateTranslator *translator, QObject *parent)
: CheckableMapExtention(mapControl, parent)
{
    translator_ = translator;

    connect(mapControl_, SIGNAL(zoomChanged(int)), this, SLOT(zoomChanged_(int)));

    zoomChanged_(mapControl_->currentZoom());
}

GeometryConnectorMapExtention::~GeometryConnectorMapExtention()
{
}

GeometryConnectorCoordinateTranslator *GeometryConnectorMapExtention::translator()
{
    return translator_;
}

void GeometryConnectorMapExtention::start()
{
}

void GeometryConnectorMapExtention::stop(MapExtention *sender)
{
}

void GeometryConnectorMapExtention::setChecked(bool checked)
{
    if (checked && !isChecked())
    {
        mapControl_->setCoordinateTranslator(translator_);
    }
    else if (!checked && isChecked())
    {
        mapControl_->setCoordinateTranslator(NULL);
    }

    CheckableMapExtention::setChecked(checked);
}

void GeometryConnectorMapExtention::zoomChanged_(int zoom)
{
    qreal mult = pow(2, zoom);
    translator_->setDistance(translator_->getBaseDistance() / mult);
}
