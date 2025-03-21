#ifndef CREATEORIENTEDRPPMAPEXTENTION_H
#define CREATEORIENTEDRPPMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/rpp.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания Корабельного (ориентированного) РПП
*    @author Maxim Poylov
*/
class CreateOrientedRppMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateOrientedRppMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateOrientedRppMapExtention();

    QColor getColor();
    QString getFileName();
    qreal getAzimuth();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setColor(QColor color);
    void setFileName(QString filename);
    void setAzimuth(qreal azimuth);

private slots:
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);

private:
    QColor color_;
    QString filename_;
    qreal azimuth_;
    bool pressed_;

    Rpp    *geometry_;
};

}
#endif
