#ifndef CREATERPPMAPEXTENTION_H
#define CREATERPPMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/rpp.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания РПП
*    @author Maxim Poylov
*/
class CreateRppMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateRppMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateRppMapExtention();

    QColor getColor();
    QString getFileName();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setColor(QColor color);
    void setFileName(QString filename);

private slots:
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);

private:
    bool pressed_;
    QColor color_;
    QString filename_;

    Rpp *geometry_;
};

}

#endif
