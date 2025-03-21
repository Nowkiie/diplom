#pragma once

#include <geometries/geometry.h>

namespace qmapcontrol
{
    /*!
    *   Класс для рисования эллипса
    *   @author Maxim Poylov
    */


    class Ellipse : public Geometry
    {
    public:
        Ellipse(QPointF center, QSizeF size, qreal angle = 0,
            QString name = QString(), QPen pen = QPen(Qt::black));
        virtual ~Ellipse();

        virtual QRectF boundingBox();
        virtual bool Touches(Point* geom, const MapAdapter* mapadapter);
        virtual void draw(QPainter* painter, const MapAdapter* mapadapter,
            const QRectF &viewport, const QPoint offset);
        virtual QPolygonF points();

        void setBaselevel(int zoomlevel);

        void setCenter(const QPointF &center);
        QPointF center();
        void setSize(const QSizeF &size);
        QSizeF size();
        void setAngle(const qreal &angle);
        qreal angle();

        void accept(GeometryVisitor *visitor) override;

    private:
        QRectF _boundingBox;
        QPointF _center;
        QSizeF _radius;
        qreal _angle;

        int _homelevel;
        QSizeF _displaySize;

        void _clearPoints();
        void _calculate();
        QPolygonF _points;
    };
}
