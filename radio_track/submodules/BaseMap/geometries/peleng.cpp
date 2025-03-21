/*
*
* This file is part of QMapControl,
* an open-source cross-platform map widget
*
* Copyright (C) 2007 - 2008 Kai Winter
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with QMapControl. If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: kaiwinter@gmx.de
* Program URL   : http://qmapcontrol.sourceforge.net/
*
*/

#include "peleng.h"
#include "pelengbase.h"

#include <QTime>

#define _USE_MATH_DEFINES
#include "math.h"

namespace qmapcontrol
{
    Peleng::Peleng(QPointF position, qreal azimuth, qreal length, QString name, QPen pen)
        :Geometry(name), _azimuth(azimuth), _position(position), _length(length), levelOfDetails_(LOD_0)
    {
        setPen(pen);
        GeometryType = "Peleng";

        _calculate();
    }

    Peleng::~Peleng()
    {
        _peleng.clear();
        for (int i = 0; i < _polygons.count(); i++)
        {
            delete _polygons.at(i);
        }
        _polygons.clear();

        _clearCachePolygons();
    }

    void Peleng::_calculate()
    {
        _clearCachePolygons();

        for (int i = 0; i < _polygons.count(); i++)
        {
            delete _polygons.at(i);
        }
        _polygons.clear();

        _peleng.clear();
        PelengBase::calculate(_position, _azimuth, _length, levelOfDetails_, _peleng);
        PelengBase::splitByMapBorders(_peleng, _polygons);

        // вычисление ограждающего прямоугольника
        qreal minlon = 180;
        qreal maxlon = -180;
        qreal minlat = 90;
        qreal maxlat = -90;

        for (int i = 0; i<_peleng.size(); i++)
        {
            QPointF tmp = _peleng.at(i);
            if (tmp.x() < minlon) minlon = tmp.x();
            if (tmp.x() > maxlon) maxlon = tmp.x();
            if (tmp.y() < minlat) minlat = tmp.y();
            if (tmp.y() > maxlat) maxlat = tmp.y();
        }
        _boundingBox = QRectF(QPointF(minlon, minlat), QPointF(maxlon, maxlat)).normalized();
    }

    void Peleng::setPosition(QPointF position)
    {
        _position = position;
        _calculate();
    }

    QPointF Peleng::position()
    {
        return _position;
    }

    void Peleng::setAzimuth(qreal azimuth)
    {
        _azimuth = azimuth;
        _calculate();
    }

    qreal Peleng::azimuth()
    {
        return _azimuth;
    }

    void Peleng::setLength(qreal length)
    {
        _length = length;
        _calculate();
    }

    qreal Peleng::length()
    {
        return _length;
    }

    QPolygonF Peleng::points()
    {
        return _peleng;
    }

    void Peleng::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

    void Peleng::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (!visible)
            return;


        QPen origPen = painter->pen();
        painter->setPen(mypen);


        auto rhint=painter->renderHints();
        painter->setRenderHint(QPainter::Antialiasing);

        //QTime t;
        //t.start();

        bool needRecalc = true;

        // проверка уровня детализации
        LOD lod = levelOfDetails_;
        if (mapadapter->currentZoom() < 5 && levelOfDetails_ != LOD_1 && levelOfDetails_ != LOD_2) lod = LOD_1;
        else if (mapadapter->currentZoom() < 8 && levelOfDetails_ != LOD_2) lod = LOD_1;
        else if (mapadapter->currentZoom() > 7) lod = LOD_2;
        if (lod != levelOfDetails_)
        {
            levelOfDetails_ = lod;
            _calculate();
        }
        if (_cachedPolygons.count() > 0)
        {
            if (_cachedPolygons.at(0)->count() > 1)
            {
                // проверяем первую и последнюю точку, а также общее количество
                int sz = _cachedPolygons.at(0)->size();
                int nsz = _polygons.at(0)->size();
                needRecalc =
                    (mapadapter->coordinateToDisplay(_polygons.at(0)->at(0)) != _cachedPolygons.at(0)->at(0))
                    || (mapadapter->coordinateToDisplay(_polygons.at(0)->at(nsz - 1)) != _cachedPolygons.at(0)->at(sz - 1));

            }
        }
        if (needRecalc)
        {
            _clearCachePolygons();

            int delta = 1; 
            if (delta == 0) delta = 1;
            for (int i = 0; i < _polygons.count(); i+= delta)
            {
                QPolygonF *pg = new QPolygonF(); 
                _cachedPolygons.append(pg);

                QPolygonF *p = _polygons.at(i);
                for (int j = 0; j < p->count(); j++)
                {
                    pg->append(mapadapter->coordinateToDisplay(p->at(j)));
                }
                PelengBase::optimizePolygon(*pg);
            }
        }


        for (int i = 0; i < _cachedPolygons.count(); i++)
        {
            painter->drawPolyline(*_cachedPolygons.at(i));
        }

        painter->setRenderHints(QPainter::Antialiasing, rhint.testFlag(QPainter::Antialiasing));
    
        painter->setPen(origPen);

    }

    void Peleng::_clearCachePolygons()
    {
        for (int i = 0; i < _cachedPolygons.count(); i++)
        {
            delete _cachedPolygons.at(i);
        }
        _cachedPolygons.clear();
    }

    bool Peleng::Touches(Point* point, const MapAdapter* mapadapter)
    {
        QPointF c = point->position();

        // смещаем точку в сторону ограждающего прямоугольника (если нужно)
        while (c.x() < _boundingBox.left()) c.setX(c.x() + 360);
        while (c.x() > _boundingBox.right()) c.setX(c.x() - 360);
        if (!_boundingBox.contains(c)) return false;
        qreal delta = 20 / pow(2, mapadapter->currentZoom()); // 5 градусов при минимальном удалении

        // третий способ
        // вычисляем угол между указателем и началом пеленга и сравниваем его с углом пеленга
        qreal length, angle;
        PelengBase::pelengParamsByPoints(_position, c, angle, length);
        if ((angle * _azimuth) < 0) // если разных знаков, то выравниваем
        {
            if (angle > _azimuth) angle -= 360;
            else if (angle < _azimuth) angle += 360;
        }
        bool result = qAbs(angle - _azimuth) < delta;

        return result;
    }

    QRectF Peleng::boundingBox()
    {
        return _boundingBox;
    }
}
