#ifndef CREATEPELENGMAPEXTENTION_H
#define CREATEPELENGMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/peleng.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания пеленга
*    @author Maxim Poylov
*/
class CreatePelengMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreatePelengMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreatePelengMapExtention();

    QColor getColor();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setColor(QColor color);

private slots:
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);

private:
    QColor color_;
    bool pressed_;
    Peleng    *geometry_;
};
}

#endif
