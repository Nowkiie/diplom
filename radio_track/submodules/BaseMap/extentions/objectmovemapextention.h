#ifndef OBJECTMOVEMAPEXTENTION_H
#define OBJECTMOVEMAPEXTENTION_H

#include <geometries/staticgeometry.h>
#include <extentions/selectionmapextention.h>

namespace qmapcontrol
{
class MoveGeometryVisitor : public GeometryVisitor
{
public:
    MoveGeometryVisitor(QPointF delta);

    virtual void visit(Place* object);
    virtual void visit(Image* object);
    virtual void visit(Peleng* object);
    virtual void visit(Ellipse* object);
    virtual void visit(Rpp* object);
    virtual void visit(Region* object);
    virtual void visit(Sector* object);
    virtual void visit(Point* object);
    virtual void visit(Geometry* object);

private:
    QPointF delta_;
};

class ObjectMoveMapExtention
    : public CheckableMapExtention
    , public GeometryProcessor
{
    Q_OBJECT

public:
    ObjectMoveMapExtention(MapControl* mapControl, qreal radius,
                           Qt::MouseButton actionButton,
                           QObject* parent = NULL);
    ObjectMoveMapExtention(MapControl* mapControl, qreal radius,
                           QObject* parent = NULL);
    virtual ~ObjectMoveMapExtention();

public slots:
    virtual void start();
    virtual void stop(MapExtention*);

public:
    void process(QList<Geometry*> geometries);

private slots:
    void mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate);
    void mousePressEvent_(QMouseEvent* evnt, QPointF coordinate);
    void mouseReleaseEvent_(QMouseEvent* evnt, QPointF coordinate);

private:
    bool pressed_;
    QPointF initPosition_;
    Qt::MouseButton actionButton_;
    Geometry* geometry_;
    qreal radius_;

signals:
    //void needGeometries(GeometryProcessor *sender);
    void objectMoved(Geometry* object);
    void objectSelected(Geometry* object);
};
}  // namespace qmapcontrol

#endif
