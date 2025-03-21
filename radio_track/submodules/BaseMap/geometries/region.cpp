#include "region.h"
#include <QPen>

#include "point.h"

namespace qmapcontrol
{
    Region::Region(QRectF rect, Qt::BrushStyle fillStyle, QString name, QPen pen)
        : Geometry()
    {
        myname = name;
        _rect = rect;
        _homelevel = -1;
        QColor col = pen.color();
        _brush = QBrush(QColor(col.red(), col.green(), col.blue(), 100), fillStyle);
        setPen(pen);

        setRect(_rect);
    }

    Region::Region(QRectF rect, QBrush brush, QString name, QPen pen)
    {
        myname = name;
        _rect = rect;
        _homelevel = -1;
        _brush = brush;
        setPen(pen);

        setRect(_rect);
    }

    Region::~Region()
    {
    }

    QRectF Region::boundingBox()
    {
        return _boundingBox;
    }

    void Region::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (!visible) return;

        QPen origPen = painter->pen();
        QBrush origBrush = painter->brush();
        painter->setBrush(_brush);
        painter->setPen(mypen);

        QPoint tl = mapadapter->coordinateToDisplay(_rect.topLeft());
        QPoint rb = mapadapter->coordinateToDisplay(_rect.bottomRight());
        painter->drawRect(QRectF(tl, rb));

        painter->setPen(origPen);
        painter->setBrush(origBrush);
    }

    bool Region::Touches(Point* geom, const MapAdapter* mapadapter)
    {
        return _rect.contains(geom->position());
    }

    QPolygonF Region::points()
    {
        QPolygonF points;

        points.append(_rect.topLeft());
        points.append(_rect.topRight());
        points.append(_rect.bottomRight());
        points.append(_rect.bottomLeft());

        return points;
    }

    void Region::setBaselevel(int zoomlevel)
    {
        _homelevel = zoomlevel;
    }

    void Region::setRect(const QRectF &rect)
    {
        _rect = rect;
        _boundingBox = rect;
    }

    QRectF Region::rect() const
    {
        return _rect;
    }

    void Region::setFillStyle(Qt::BrushStyle style)
    {
        QColor col = _brush.color();
        _brush = QBrush(col, style);
    }

    Qt::BrushStyle Region::fillStyle() const
    {
        return _brush.style();
    }

    void Region::setBrush(const QBrush &brush)
    {
        _brush = brush;
    }

    QBrush Region::brush(void) const
    {
        return _brush;
    }

    void Region::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

}
