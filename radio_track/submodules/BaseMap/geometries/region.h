#ifndef REGION_H
#define REGION_H

#include "geometry.h"

namespace qmapcontrol
{
    /*!
    *    Класс для рисования прямоугольной области
    *    @author Maxim Poylov
    */
    class Region : public Geometry
    {
    public:
        Region(QRectF rect, Qt::BrushStyle fillStyle = Qt::BrushStyle::NoBrush, QString name = QString(), QPen pen = QPen(Qt::black));
        Region(QRectF rect, QBrush brush, QString name = QString(), QPen pen = QPen(Qt::black));
        virtual ~Region();

        virtual QRectF boundingBox();
        virtual bool Touches(Point* geom, const MapAdapter* mapadapter);
        virtual void draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);
        virtual QPolygonF points();

        void setBaselevel(int zoomlevel);

        void setRect(const QRectF &rect);
        QRectF rect() const;
        void setFillStyle(Qt::BrushStyle style);
        Qt::BrushStyle fillStyle() const;

        void setBrush(const QBrush &brush);
        QBrush brush(void) const;

        void accept(GeometryVisitor *visitor);

    private:
        QRectF    _boundingBox;
        QRectF    _rect;
        QBrush    _brush;

        int        _homelevel;
    };
}
#endif //REGION_H
