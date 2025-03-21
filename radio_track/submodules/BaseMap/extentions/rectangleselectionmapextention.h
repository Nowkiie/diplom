#ifndef RECTANGLESELECTIONMAPEXTENTION_H
#define RECTANGLESELECTIONMAPEXTENTION_H

#include "geometries/staticgeometry.h"
#include "selectionmapextention.h"

namespace qmapcontrol
{
/*!
    *    Класс по-умолчанию для рисования прямоугольного выделения
    *    @author Maxim Poylov
    */
class RectangleSelectionGeometry : public qmapcontrol::StaticGeometry
{
    Q_OBJECT
public:
    RectangleSelectionGeometry(QObject* parent = NULL);
    virtual ~RectangleSelectionGeometry();

    virtual void draw(QPainter* painter,
                      const qmapcontrol::MapAdapter* mapadapter,
                      const QRectF& viewport, const QPoint offset);

    void setStart(QPointF point);
    void setEnd(QPointF point);

    QPointF start();
    QPointF end();

protected:
    QPointF start_;
    QPointF end_;
};

class RectangleSelectionMapExtention : public SelectionMapExtention
{
    Q_OBJECT

public:
    RectangleSelectionMapExtention(MapControl* mapControl,
                                   qmapcontrol::Layer* layer,
                                   RectangleSelectionGeometry* geometry,
                                   QObject* parent = NULL);

    RectangleSelectionMapExtention(
        MapControl* mapControl, qmapcontrol::Layer* layer,
        RectangleSelectionGeometry* geometry,
        Qt::MouseButton actionButton, QObject* parent = NULL);

    RectangleSelectionMapExtention(
        MapControl* mapControl, qmapcontrol::Layer* layer,
        RectangleSelectionGeometry* geometry,
        Qt::MouseButton actionButton,
        Qt::KeyboardModifier actionAdditionalKey_,
        Qt::KeyboardModifier selectionAddModifer_,
        QObject* parent = NULL);

    virtual ~RectangleSelectionMapExtention();

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
    qmapcontrol::Layer* layer_;
    RectangleSelectionGeometry* geometry_;
    Qt::MouseButton actionButton_;
    Qt::KeyboardModifier actionAdditionalKey_;
    Qt::KeyboardModifier selectionAddModifer_;
};

}  // namespace qmapcontrol
#endif
