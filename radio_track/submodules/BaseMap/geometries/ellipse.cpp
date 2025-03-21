#include "ellipse.h"
#include "qpen.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <geometries/point.h>

#include <geometries/pelengbase.h>

// http://serverznak:3000/GiSeer/GeoMath.git
#include <PC2_Cl_GeoMath.h>


namespace qmapcontrol
{
    Ellipse::Ellipse(QPointF center, QSizeF size, qreal angle,
        QString name, QPen pen)
        : Geometry()
    {
        myname = name;
        _center = center;
        _radius = size;
        _homelevel = -1;
        setPen(pen);

        setAngle(angle);
    }

    Ellipse::~Ellipse()
    {
        _clearPoints();
    }

    void Ellipse::setCenter(const QPointF &center)
    {
        _center = center;
        _calculate();
    }

    QPointF Ellipse::center()
    {
        return _center;
    }

    void Ellipse::setSize(const QSizeF &size)
    {
        _radius = size;
        _calculate();
    }

    QSizeF Ellipse::size()
    {
        return _radius;
    }

    void Ellipse::setAngle(const qreal &angle)
    {
        _angle = -angle;
        _calculate();
    }

    qreal Ellipse::angle()
    {
        return -_angle;
    }

    void Ellipse::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

    QRectF Ellipse::boundingBox()
    {
        return _boundingBox;
    }

    void Ellipse::draw(QPainter* painter, const MapAdapter* mapadapter,
        const QRectF &viewport, const QPoint offset)
    {
        if (!visible) return;

        QPoint center = mapadapter->coordinateToDisplay(_center);

        // если установлен базовый уровень, то вычисляем размеры в зависимости от него
        if (_homelevel > 0)
        {
            int currentzoom = mapadapter->maxZoom() <mapadapter->minZoom() ?
                mapadapter->minZoom() - mapadapter->currentZoom() :
                mapadapter->currentZoom();
            int diffzoom = _homelevel - currentzoom;
            qreal viewheight = _radius.height();
            qreal viewwidth = _radius.width();
            viewheight = viewheight / pow(2, diffzoom);
            viewwidth = viewwidth / pow(2, diffzoom);
            _displaySize = QSizeF(viewwidth, viewheight);
        }
        else
        {
            _displaySize = _radius;
        }

        QPen origPen = painter->pen();
        QTransform origTransform = painter->transform();

        painter->setPen(mypen);

        // отрисовка с преобразованием из мировых координат в экранные
        QPainterPath path;

        for (int i = 0; i < _points.size(); i++)
        {
            QPoint dsp;
            dsp = mapadapter->coordinateToDisplay(_points[i]);

            if (i > 0)
            {
                path.lineTo(dsp);
            }
            else
            {
                path.moveTo(dsp);
            }
        }

        //рисование
        path.closeSubpath();
        painter->drawPath(path);
        painter->setPen(origPen);
    }

    bool Ellipse::Touches(Point* point, const MapAdapter* mapadapter)
    {
        //лежит ли точка point в эллипсе
        QPointF p_F = point->position();

        TGeoPoint p_GP;
        p_GP.d = p_F.rx()*_gtr;
        p_GP.s = p_F.ry()*_gtr;

        TGeoMath GeoMath;
        TEllipse ellipse_v2 = GeoMath.convert_to_ellipse_v2(_center.rx(),
            _center.ry(), _radius.width(), _radius.height(), _angle);

        return GeoMath.Point_In_Ellipse(p_GP, ellipse_v2);
    }

    void Ellipse::_clearPoints()
    {
        _points.clear();
    }

    void Ellipse::_calculate()
    {
        _clearPoints();

        TGeoMath GeoMath;
        TEllipse ellipse_v2 = GeoMath.convert_to_ellipse_v2(_center.rx(),
            _center.ry(), _radius.width(), _radius.height(), _angle);

        std::vector <TGeoPoint> border;
        border.clear();
        border = GeoMath.Ellipse_Border_GP(ellipse_v2);
        border.push_back(border[0]);
        // долгота последней нарисованной точки
        double last_d = 0; 

        for (int i = 0; i < int(border.size()); i++)
        {
            // очередная точка эллипса в мировых координатах типа TGeoPoint
            TGeoPoint p_tmp = border[i];
            // для перевода ее в QPointF
            QPointF p_tmp_F; 

            if ((i > 0) && (abs(last_d - p_tmp.d) > M_PI))
            {
                if (p_tmp.d > 0) p_tmp_F.rx() = (p_tmp.d - 2 * M_PI)*_rtg;
                else p_tmp_F.rx() = (p_tmp.d + 2 * M_PI)*_rtg;
            }
            else
            {
                p_tmp_F.rx() = p_tmp.d*_rtg;
            }

            p_tmp_F.ry() = p_tmp.s*_rtg;
            last_d = p_tmp_F.rx()*_gtr;

            _points << p_tmp_F;
        }

        // вычисление ограждающего прямоугольника
        qreal minlon = 180;
        qreal maxlon = -180;
        qreal minlat = 90;
        qreal maxlat = -90;

        for (int i = 0; i < _points.size(); i++)
        {
            QPointF tmp = _points.at(i);
            if (tmp.x() < minlon) minlon = tmp.x();
            if (tmp.x() > maxlon) maxlon = tmp.x();
            if (tmp.y() < minlat) minlat = tmp.y();
            if (tmp.y() > maxlat) maxlat = tmp.y();
        }
        _boundingBox = QRectF(QPointF(minlon, minlat),
            QPointF(maxlon, maxlat)).normalized();
    }

    QPolygonF Ellipse::points()
    {
        return _points;
    }

    void Ellipse::setBaselevel(int zoomlevel)
    {
        _homelevel = zoomlevel;
    }
}
