#ifndef SECTOR_H
#define SECTOR_H

#include <QPainterPath>
#include "geometry.h"
#include "qpoint.h"
#include "point.h"
#include <QPainterPath>


namespace qmapcontrol
{
    /*!
    *    Класс для рисования сектора
    *    @author Maxim Poylov
    */
    class Sector : public Geometry
    {
        Q_OBJECT

    public:
     
        //! constructor
        /*!
         * The constructor of a LineString takes a list of Points to form a line.
         * @param points a list of points
         * @param name the name of the LineString
         * @param pen a QPen can be used to modify the look of the line.
         * @see http://doc.trolltech.com/4.3/qpen.html
         */
        Sector(QPointF position, qreal startAzimuth, qreal endAzimuth, qreal length = 19000, Qt::BrushStyle fillStyle = Qt::BrushStyle::NoBrush, QString name = QString(), QPen pen = QPen(Qt::black));
        virtual ~Sector();

        virtual QPolygonF    points();
        virtual QRectF boundingBox();
        virtual bool Touches(Point* geom, const MapAdapter* mapadapter);
        virtual void draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

        void setPosition(QPointF position);
        QPointF position();
        void setStartAzimuth(qreal azimuth);
        qreal startAzimuth();
        void setEndAzimuth(qreal azimuth);
        qreal endAzimuth();
        void setLength(qreal length);
        qreal length();
        void setFillStyle(Qt::BrushStyle style);
        Qt::BrushStyle fillStyle();

        void updateEnabled(bool enabled = true);

        void accept(GeometryVisitor *visitor);

    private:
        QPointF _position;
        qreal _startAzimuth;
        qreal _endAzimuth;
        qreal _length;
        Qt::BrushStyle _fillStyle;

        QPolygonF _sector;

        bool _updateEnabled;
        void _calculate();

        QRectF    _boundingBox;

        QPainterPath _cachedPath;
        QPointF _cachedFirstPoint;
        enum LOD {
            LOD_0 = 16,
            LOD_1 = 8,
            LOD_2 = 1
        }    levelOfDetails_;
    };
}
#endif //SECTOR_H
