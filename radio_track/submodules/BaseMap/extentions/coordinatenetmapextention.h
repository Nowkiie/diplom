#ifndef COORDINATENETMAPEXTENTION_H
#define COORDINATENETMAPEXTENTION_H

#include "checkablemapextention.h"
#include "geometries/staticgeometry.h"

namespace qmapcontrol
{

/*!
*    Класс по-умолчанию для рисования координатной сетки
*    @author Maxim Poylov
*/
class CoordinateNetGeometry : public qmapcontrol::StaticGeometry
{
    Q_OBJECT
public:
    CoordinateNetGeometry(QObject *parent = NULL);
    virtual ~CoordinateNetGeometry();

    virtual void draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

    void setDelta(QSizeF delta);

protected:
    QSizeF delta_;

    QString coordinateToString_(qreal value);
};


/*!
*    Класс расширения для включения/выключения отображения координатной сетки
*    @author Maxim Poylov
*/
class CoordinateNetMapExtention :
    public qmapcontrol::CheckableMapExtention
{
    Q_OBJECT

public:
    CoordinateNetMapExtention(MapControl *mapControl, Layer *layer, CoordinateNetGeometry *geometry, QObject *parent = NULL);
    virtual ~CoordinateNetMapExtention();

public slots:
    virtual void setChecked(bool checked);

    virtual void start();
    virtual void stop(MapExtention *sender);

private slots:
    void zoomChanged_(int zoom);

private:
    qmapcontrol::Layer *layer_;
    CoordinateNetGeometry *geometry_;
    QSizeF basicSize_;
};

}
#endif
