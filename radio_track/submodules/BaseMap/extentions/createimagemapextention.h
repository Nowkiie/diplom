#ifndef CREATEIMAGEMAPEXTENTION_H
#define CREATEIMAGEMAPEXTENTION_H

#include "geometrycreatormapextention.h"

#include "geometries/image.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для визуального создания произвольного объекта
*    @author Maxim Poylov
*/
class CreateImageMapExtention :
    public qmapcontrol::GeometryCreatorMapExtention
{
    Q_OBJECT

public:
    CreateImageMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~CreateImageMapExtention();

    QString getFileName();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    void setFileName(QString filename);

private slots:
    void mousePressEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate);
    void mouseMoveEvent_(QMouseEvent* e, QPointF coordinate);

private:
    QString filename_;

    bool pressed_;
    Image *geometry_;
};
}

#endif
