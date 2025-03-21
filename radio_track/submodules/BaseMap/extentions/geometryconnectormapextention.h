#ifndef GEOMETRYCONNECTORMAPEXTENTION_H
#define GEOMETRYCONNECTORMAPEXTENTION_H

#include "core/coordinatetranslator.h"
#include "checkablemapextention.h"
#include "geometryprocessormapextention.h"

namespace qmapcontrol
{

/*!
*    Класс-преобразователь координат курсора в соответствующие координаты объекта
*    @author Maxim Poylov
*/
class GeometryConnectorCoordinateTranslator :
    public QObject,
    public GeometryProcessor,
    public CoordinateTranslator
{
    Q_OBJECT

public:
    GeometryConnectorCoordinateTranslator(qreal baseDistance, QObject *parent = NULL);
    virtual ~GeometryConnectorCoordinateTranslator();

    void setDistance(qreal distance);
    qreal getDistance();

    void setBaseDistance(qreal distance);
    qreal getBaseDistance();


public:
    virtual QPointF translate(QPointF coordinate);

    virtual    void    setGeometries(Geometries *geos);
private slots:
    void    geometriesUpdated();

protected:
    qreal distance_;
    qreal baseDistance_;
};

/*!
*    Класс расширения для осуществления привязки координат курсора к координатам объекта на карте
*    @author Maxim Poylov
*/
class GeometryConnectorMapExtention :
    public qmapcontrol::CheckableMapExtention
{
    Q_OBJECT

public:
    GeometryConnectorMapExtention(MapControl *mapControl, GeometryConnectorCoordinateTranslator *translator, QObject *parent = NULL);
    virtual ~GeometryConnectorMapExtention();

    GeometryConnectorCoordinateTranslator *translator();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);
    virtual void setChecked(bool checked);

private slots:
    void zoomChanged_(int zoom);

private:
    GeometryConnectorCoordinateTranslator *translator_;
};
}

#endif
