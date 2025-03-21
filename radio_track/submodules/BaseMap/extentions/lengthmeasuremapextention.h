#ifndef LENGTHMEASUREMAPEXTENTION_H
#define LENGTHMEASUREMAPEXTENTION_H

#include "checkablemapextention.h"
#include "geometries/staticgeometry.h"

namespace qmapcontrol
{

/*!
*    Класс по-умолчанию для отображения расстояния между двумя точками
*    @author Maxim Poylov
*/
class MeasureGeometry : public qmapcontrol::StaticGeometry
{
    Q_OBJECT
public:
    MeasureGeometry(QObject *parent = NULL);
    virtual ~MeasureGeometry();

    virtual void draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

    void setStart(QPointF point);
    void setEnd(QPointF point);

protected:
    QPointF start_;
    QPointF end_;

    QString CreateInfoText_(QPointF coords);

    qreal lengthByPoints_();

};

/*!
*    Класс расширения для инструмента измерения расстояния и азимута между двумя точками
*    @author Maxim Poylov
*/
class LengthMeasureMapExtention :
    public qmapcontrol::CheckableMapExtention
{
    Q_OBJECT

public:
    LengthMeasureMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, MeasureGeometry *geometry, QObject *parent = NULL);
    virtual ~LengthMeasureMapExtention();


public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

private slots:
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);

private:
    bool pressed_;
    qmapcontrol::Layer *layer_;
    MeasureGeometry *measure_;
};


}
#endif
