#ifndef PELENG_H
#define PELENG_H

#include "geometry.h"
#include "qpoint.h"
#include "point.h"

namespace qmapcontrol
{
    /*!
    *    Класс для рисования пеленга
    *    @author Maxim Poylov
    */
    class Peleng : public Geometry
    {
        Q_OBJECT

    public:
        Peleng(QPointF position, qreal azimuth, qreal length = 19000, QString name = QString(), QPen pen = QPen(Qt::black));
        virtual ~Peleng();

        virtual QPolygonF    points();
        virtual QRectF boundingBox();
        virtual bool Touches(Point* geom, const MapAdapter* mapadapter);
        virtual void draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

        void setPosition(QPointF position);
        QPointF position();
        void setAzimuth(qreal azimuth);
        qreal azimuth();
        void setLength(qreal length);
        qreal length();

        void accept(GeometryVisitor *visitor);

    private:
        qreal    _length;
        qreal    _azimuth;
        QPointF    _position;
        QRectF    _boundingBox;

        void _calculate();

        QList<QPolygonF*> _polygons;
        QList<QPolygonF*> _cachedPolygons;
        void _clearCachePolygons();

        QPolygonF _peleng;
        enum LOD {
            LOD_0 = 8,
            LOD_1 = 4,
            LOD_2 = 1
        }    levelOfDetails_;
    };
}
#endif //PELENG_H
