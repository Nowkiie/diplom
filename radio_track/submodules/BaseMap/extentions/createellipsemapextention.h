#ifndef CREATEELLIPSEMAPEXTENTION_H
#define CREATEELLIPSEMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/ellipse.h"

namespace qmapcontrol
{


/*!
*    Класс расширения для визуального создания эллипса
*    @author Maxim Poylov
*/
class CreateEllipseMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateEllipseMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateEllipseMapExtention();

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
    enum EllipseCreationState_
    {
        ECS_Center,
        ECS_Angle,
        ECS_Size
    };

    QColor color_;
    EllipseCreationState_ state_;
    Ellipse    *geometry_;
};

}

#endif
