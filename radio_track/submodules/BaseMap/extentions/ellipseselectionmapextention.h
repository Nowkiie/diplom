#ifndef ELLIPSESELECTIONMAPEXTENTION_H
#define ELLIPSESELECTIONMAPEXTENTION_H

#include "geometries/staticgeometry.h"
#include "selectionmapextention.h"

namespace qmapcontrol
{
    /*!
    *    Класс по-умолчанию для рисования эллиптического выделения
    *    @author Maxim Poylov
    */
    class EllipseSelectionGeometry : public qmapcontrol::StaticGeometry
    {
        Q_OBJECT
    public:
        EllipseSelectionGeometry(QObject *parent = NULL);
        virtual ~EllipseSelectionGeometry();

        virtual void draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

        void setPoints(QList<QPointF> points);

        QList<QPointF> getPoints();

    protected:
        QList<QPointF> points_;
    };

    class EllipseSelectionMapExtention :
        public SelectionMapExtention
    {
        Q_OBJECT

    public:
        EllipseSelectionMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, EllipseSelectionGeometry *geometry, QObject *parent = NULL);
        virtual ~EllipseSelectionMapExtention();

        public slots:
        virtual void start();
        virtual void stop(MapExtention *);

    public:
        void process(QList<Geometry*> geometries);

    private slots:
        void mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate);
        void mousePressEvent_(QMouseEvent* evnt, QPointF coordinate);
        void mouseReleaseEvent_(QMouseEvent* evnt, QPointF coordinate);

    private:
        bool pressed_;
        qmapcontrol::Layer *layer_;
        EllipseSelectionGeometry *geometry_;
    };

}
#endif
