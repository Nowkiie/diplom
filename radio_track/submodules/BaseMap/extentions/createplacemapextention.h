#ifndef CREATEPLACEMAPEXTENTION_H
#define CREATEPLACEMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/place.h"
namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания места
*    @author Maxim Poylov
*/
class CreatePlaceMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreatePlaceMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreatePlaceMapExtention();

    QColor getColor();
    int getRadius();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setColor(QColor color);
    void setRadius(int radius);

private slots:
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);

private:
    bool pressed_;
    QColor color_;
    int radius_;

    Place *geometry_;
};

}
#endif
