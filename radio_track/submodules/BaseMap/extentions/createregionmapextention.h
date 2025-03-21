#ifndef CREATEREGIONMAPEXTENTION_H
#define CREATEREGIONMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/region.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания региона
*    @author Maxim Poylov
*/
class CreateRegionMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateRegionMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateRegionMapExtention();

    QColor getColor();
    Qt::BrushStyle getFillStyle();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setColor(QColor color);
    void setFillStyle(Qt::BrushStyle fillStyle);

private slots:
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);

private:
    QColor color_;
    Qt::BrushStyle fillStyle_;
    bool pressed_;
    Region    *geometry_;
};

}

#endif
