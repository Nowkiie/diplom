#ifndef CREATESECTORMAPEXTENTION_H
#define CREATESECTORMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/sector.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания сектора
*    @author Maxim Poylov
*/
class CreateSectorMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateSectorMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateSectorMapExtention();

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
    enum SectorCreationState_
    {
        SCS_Center,
        SCS_Angle,
        SCS_Size
    };

    QColor color_;
    Qt::BrushStyle fillStyle_;
    SectorCreationState_ state_;
    Sector    *geometry_;
};

}
#endif
