#ifndef SECTORSELECTIONMAPEXTENTION_H
#define SECTORSELECTIONMAPEXTENTION_H

#include "geometries/staticgeometry.h"
#include "selectionmapextention.h"

namespace qmapcontrol
{

    /*!
    *    Класс по-умолчанию для рисования выделения в виде сектора
    *    @author Maxim Poylov
    */
    class SectorSelectionGeometry : public qmapcontrol::StaticGeometry
    {
        Q_OBJECT
    public:
        SectorSelectionGeometry(QObject *parent = NULL);
        virtual ~SectorSelectionGeometry();

        virtual void draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

        void setPoints(QList<QPointF> points);

        QList<QPointF> getPoints();

    protected:
        QList<QPointF> points_;
    };

    class SectorSelectionMapExtention :
        public SelectionMapExtention
    {
        Q_OBJECT

    public:
        SectorSelectionMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, SectorSelectionGeometry *geometry, QObject *parent = NULL);
        virtual ~SectorSelectionMapExtention();

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
        SectorSelectionGeometry *geometry_;
    };

}
#endif
