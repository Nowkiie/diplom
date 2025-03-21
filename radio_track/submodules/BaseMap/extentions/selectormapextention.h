#ifndef SELECTORMAPEXTENTION_H
#define SELECTORMAPEXTENTION_H

#include <geometries/staticgeometry.h>
#include <extentions/geometryprocessormapextention.h>

namespace qmapcontrol
{


class SelectorVisitor : public GeometryVisitor
{
public:
    SelectorVisitor(QPointF coordinate, qreal radius);

    virtual void visit(Place *object);
    virtual void visit(Image *object);
    virtual void visit(Peleng *object);
    virtual void visit(Ellipse *object);
    virtual void visit(Rpp *object);
    virtual void visit(Region *object);
    virtual void visit(Sector *object);
    virtual void visit(Point *object);
    virtual void visit(Geometry *object);

    bool touches();

private:
    QPointF coord_;
    bool result_;
    qreal radius_;
};

class SelectorMapExtention :
    public MapExtention
    , public GeometryProcessor
{
    Q_OBJECT

public:
    SelectorMapExtention(MapControl *mapControl, Layer *layer, qreal radius, QObject *parent = NULL);
    virtual ~SelectorMapExtention();

public:
    void process(QList<Geometry*> geometries);

private slots:
    void mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* evnt, QPointF coordinate);

private:
    Layer *layer_;
    QPointF coordinate_;
    qreal radius_;
};

}

#endif
