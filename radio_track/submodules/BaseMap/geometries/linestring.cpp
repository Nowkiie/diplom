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

#include "linestring.h"
namespace qmapcontrol
{
    LineString::LineString()
        : Curve()
    {
        GeometryType = "LineString";
    }

    LineString::LineString(QList<Point*> const points, QString name)
        :Curve(name)
    {
        setPoints(points);
    }

    LineString::~LineString()
    {
        
    }

    void LineString::addPoint(Point* point)
    {
        vertices.append(point);
    }

    QPolygonF LineString::points()
    {
        QPolygonF points;
        for (int i = 0; i < vertices.count(); i++)
        {
            points.append(vertices.at(i)->position());
        }

        return points;
    }

    void LineString::setPoints(QList<Point*> points)
    {
        for (int i=0; i<points.size(); i++)
        {
            points.at(i)->setParentGeometry(this);
        }
        vertices = points;
    }

    void LineString::draw(QPainter* painter, const MapAdapter* mapadapter, const QRect &screensize, const QPoint offset)
    {
        if (!visible)
            return;

        QPolygon p = QPolygon();

        QPointF c;
        for (int i=0; i<vertices.size(); i++)
        {
            c = vertices[i]->position();
            p.append(mapadapter->coordinateToDisplay(c));
        }

        QPen origPen = painter->pen();
        painter->setPen(mypen);

        auto rhint=painter->renderHints();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawPolyline(p);
        painter->setRenderHints(rhint);

        painter->setPen(origPen);

        for (int i=0; i<vertices.size(); i++)
        {
            vertices[i]->draw(painter, mapadapter, screensize, offset);
        }
    }

    int LineString::numberOfPoints() const
    {
        return vertices.count();
    }
    bool LineString::Touches(Point* geom, const MapAdapter* mapadapter)
    {
        touchedPoints.clear();
        bool touches = false;
        for (int i=0; i<vertices.count(); i++)
        {
            // use implementation from Point
            if (vertices.at(i)->Touches(geom, mapadapter))
            {
                touchedPoints.append(vertices.at(i));

                touches = true;
            }
        }
        return touches;
    }
    bool LineString::Touches(Geometry* /*geom*/, const MapAdapter* /*mapadapter*/)
    {
        touchedPoints.clear();

        return false;
    }

    QList<Geometry*> LineString::clickedPoints()
    {
        return touchedPoints;
    }
    bool LineString::hasPoints() const
    {
        return vertices.size() > 0 ? true : false;
    }
    bool LineString::hasClickedPoints() const
    {
        return touchedPoints.size() > 0 ? true : false;
    }

    QRectF LineString::boundingBox()
    {
        qreal minlon=180;
        qreal maxlon=-180;
        qreal minlat=90;
        qreal maxlat=-90;
        for (int i=0; i<vertices.size(); i++)
        {
            Point* tmp = vertices.at(i);
            if (tmp->longitude() < minlon) minlon = tmp->longitude();
            if (tmp->longitude() > maxlon) maxlon = tmp->longitude();
            if (tmp->latitude() < minlat) minlat = tmp->latitude();
            if (tmp->latitude() > maxlat) maxlat = tmp->latitude();
        }
        QPointF min = QPointF(minlon, minlat);
        QPointF max = QPointF(maxlon, maxlat);
        QPointF dist = max - min;
        QSizeF si = QSizeF(dist.x(), dist.y());

        return QRectF(min, si);

    }
}
