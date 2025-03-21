#ifndef GEOMETRYINFOMAPEXTENTION_H
#define GEOMETRYINFOMAPEXTENTION_H

#include "geometryprocessormapextention.h"

/*!
*    Класс для выбора информации о конкретном объекте
*    @author Maxim Poylov
*/
class GeometryInformationExtractor : public qmapcontrol::GeometryVisitor
{
public:
    void visit(qmapcontrol::Place *object);
    void visit(qmapcontrol::Image *object);
    void visit(qmapcontrol::Peleng *object);
    void visit(qmapcontrol::Ellipse *object);
    void visit(qmapcontrol::Rpp *object);
    void visit(qmapcontrol::Region *object);
    void visit(qmapcontrol::Sector *object);
    void visit(qmapcontrol::Point *object);
    void visit(qmapcontrol::Geometry *object);

public:
    QString info();

private:
    QString info_;
};

/*!
*    Класс расширения для отображения информации по двойному щелчку на объекте
*    @author Maxim Poylov
*/
class GeometryInfoMapExtention :
    public qmapcontrol::MapExtention
    , public qmapcontrol::GeometryProcessor
{
    Q_OBJECT

public:
    GeometryInfoMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, QObject *parent = NULL);
    virtual ~GeometryInfoMapExtention();

public slots:
    virtual void start();
    virtual void stop(MapExtention *sender);

    //virtual void process(QList<Geometry*> geometries);

private slots:
    void mouseDoubleClickEvent_(QMouseEvent* e, QPointF coordinate);

private:
    QPointF point_;
    qmapcontrol::Layer *layer_;
};

#endif