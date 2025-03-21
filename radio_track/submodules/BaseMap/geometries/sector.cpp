#include "sector.h"
#include "pelengbase.h"

#include <QTime>

#define _USE_MATH_DEFINES
#include "math.h"

//#include <QDebug>

namespace qmapcontrol
{
    Sector::Sector(QPointF position, qreal startAzimuth, qreal endAzimuth, qreal length, Qt::BrushStyle fillStyle, QString name, QPen pen)
        :Geometry(name), _fillStyle(fillStyle), _position(position), _startAzimuth(startAzimuth), _endAzimuth(endAzimuth), _length(length)
        , levelOfDetails_(LOD_0)
    {
        GeometryType = "Sector";
        setPen(pen);

        updateEnabled(true);

    }

    Sector::~Sector()
    {
    }

    void Sector::_calculate()
    {
        if (!_updateEnabled) return;

        _sector.clear();

        // формируем пеленги
        QPolygonF peleng1, peleng2;
        PelengBase::calculate(_position, _startAzimuth, _length, levelOfDetails_, peleng1);
        PelengBase::calculate(_position, _endAzimuth, _length, levelOfDetails_, peleng2);

        // формируем пеленг между конечными точками
        qreal tmpAzimuth, tmpLength;
        QPolygonF peleng3;
        if (peleng1.size() > 0
            && peleng2.size() > 0)
        {
            PelengBase::pelengParamsByPoints(peleng1.last(), peleng2.last(), tmpAzimuth, tmpLength);
            PelengBase::calculate(peleng1.last(), tmpAzimuth, tmpLength, levelOfDetails_, peleng3);
        }


        _sector.swap(peleng1);

        if (peleng3.size() > 1)
        {
            peleng3.removeFirst();
            peleng3.removeLast();
            _sector << peleng3;
        }

        peleng2.removeFirst();
        QVectorIterator<QPointF> it(peleng2);
        it.toBack();
        while (it.hasPrevious())
        {
            _sector.append(it.previous());
        }

        // вычисление ограждающего прямоугольника
        qreal minlon = 180;
        qreal maxlon = -180;
        qreal minlat = 90;
        qreal maxlat = -90;

        for (int i = 0; i<_sector.size(); i++)
        {
            QPointF tmp = _sector.at(i);
            if (tmp.x() < minlon) minlon = tmp.x();
            if (tmp.x() > maxlon) maxlon = tmp.x();
            if (tmp.y() < minlat) minlat = tmp.y();
            if (tmp.y() > maxlat) maxlat = tmp.y();
        }
        _boundingBox = QRectF(QPointF(minlon, minlat), QPointF(maxlon, maxlat)).normalized();
    }

    void Sector::setPosition(QPointF position)
    {
        _position = position;
        _calculate();
    }

    QPointF Sector::position()
    {
        return _position;
    }

    void Sector::setStartAzimuth(qreal azimuth)
    {
        _startAzimuth = azimuth;
        _calculate();
    }

    qreal Sector::startAzimuth()
    {
        return _startAzimuth;
    }

    void Sector::setEndAzimuth(qreal azimuth)
    {
        _endAzimuth = azimuth;
        _calculate();
    }

    qreal Sector::endAzimuth()
    {
        return _endAzimuth;
    }

    void Sector::setLength(qreal length)
    {
        _length = length;
        _calculate();
    }

    qreal Sector::length()
    {
        return _length;
    }

    void Sector::setFillStyle(Qt::BrushStyle style)
    {
        _fillStyle = style;
    }

    Qt::BrushStyle Sector::fillStyle()
    {
        return _fillStyle;
    }

    QPolygonF Sector::points()
    {
        return _sector;
    }

    void Sector::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (!visible)
            return;

        QPen origPen = painter->pen();
        QBrush origBrush = painter->brush();
        QBrush selBrush;
        QPen selPen;
        selBrush = QBrush(QColor(mypen.color().red(), mypen.color().green(), mypen.color().blue(), 100), _fillStyle);
        selPen = mypen;
        painter->setBrush(selBrush);
        painter->setPen(selPen);

        auto rhint=painter->renderHints();
        painter->setRenderHint(QPainter::Antialiasing);

        bool needRecalc = true;

        // проверка уровня детализации
        LOD lod = levelOfDetails_;
        if (mapadapter->currentZoom() < 5 && levelOfDetails_ != LOD_1 && levelOfDetails_ != LOD_2) lod = LOD_0;
        else if (mapadapter->currentZoom() < 8 && levelOfDetails_ != LOD_2) lod = LOD_1;
        else if (mapadapter->currentZoom() > 7) lod = LOD_2;
        if (lod != levelOfDetails_)
        {
            levelOfDetails_ = lod;
            _calculate();
        }


        if (needRecalc)
        {
            _cachedPath = QPainterPath();
            QPoint p;
            for (int j = 0; j < _sector.count(); j++)
            {
                p = mapadapter->coordinateToDisplay(_sector.at(j));
                if (j == 0)
                {
                    _cachedPath.moveTo(p);
                    _cachedFirstPoint = p;
                }
                else
                    _cachedPath.lineTo(p);
            }
            _cachedPath.closeSubpath();
        }


        painter->drawPath(_cachedPath);

        painter->setRenderHints(QPainter::Antialiasing, rhint.testFlag(QPainter::Antialiasing));

        painter->setPen(origPen);
        painter->setBrush(origBrush);
    }

    bool Sector::Touches(Point* point, const MapAdapter* mapadapter)
    {
        QPointF c = point->position();

        // смещаем точку в сторону ограждающего прямоугольника (если нужно)
        while (c.x() < _boundingBox.left()) c.setX(c.x() + 360);
        while (c.x() > _boundingBox.right()) c.setX(c.x() - 360);
        if (!_boundingBox.contains(c)) return false;


        qreal length, angle;
        PelengBase::pelengParamsByPoints(_position, c, angle, length);
        while (angle > _endAzimuth) angle -= 360;
        while (angle < _startAzimuth) angle += 360;

        bool result = _startAzimuth <= angle && _endAzimuth >= angle;


        return result;
    }

    QRectF Sector::boundingBox()
    {
        return _boundingBox;
    }

    void Sector::updateEnabled(bool enabled)
    {
        _updateEnabled = enabled;
        if (_updateEnabled) _calculate();
    }

    void Sector::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

}
