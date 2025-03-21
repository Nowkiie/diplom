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

#include "point.h"
namespace qmapcontrol
{
    Point::Point()
    {}
    Point::Point(const Point& point)
        :Geometry(point.name()), X(point.longitude()), Y(point.latitude())
    {
        visible = point.isVisible();
        mywidget = 0;
        mypixmap = 0;
        mypen = point.mypen;
        homelevel = -1;
        minsize = QSize(-1,-1);
        maxsize = QSize(-1,-1);
    }

    Point::Point(qreal x, qreal y, QString name, enum Alignment alignment)
        : Geometry(name), X(x), Y(y), myalignment(alignment)
    {
        GeometryType = "Point";
        mywidget = 0;
        mypixmap = 0;
        visible = true;
        homelevel = -1;
        minsize = QSize(-1,-1);
        maxsize = QSize(-1,-1);
    }

    Point::Point(qreal x, qreal y, QWidget* widget, QString name, enum Alignment alignment)
        : Geometry(name), X(x), Y(y), mywidget(widget), myalignment(alignment)
    {
        GeometryType = "Point";
        mypixmap = 0;
        visible = true;
        size = widget->size();
        homelevel = -1;
        minsize = QSize(-1,-1);
        maxsize = QSize(-1,-1);
        mywidget->show();
    }
    Point::Point(qreal x, qreal y, QPixmap* pixmap, QString name, enum Alignment alignment)
        : Geometry(name), X(x), Y(y), mypixmap(pixmap), myalignment(alignment)
    {
        GeometryType = "Point";
        mywidget = 0;
        visible = true;
        size = pixmap->size();
        homelevel = -1;
        minsize = QSize(-1,-1);
        maxsize = QSize(-1,-1);
    }
    Point::~Point()
    {
        delete mywidget;
        delete mypixmap;
    }

    void Point::setVisible(bool visible)
    {
        this->visible = visible;
        if (mywidget !=0)
        {
            mywidget->setVisible(visible);
        }
    }

    QRectF Point::boundingBox()
    {
        return QRectF(QPointF(X, Y), QSizeF(1, 1) / 10000);
    }

    qreal Point::longitude() const
    {
        return X;
    }
    qreal Point::latitude() const
    {
        return Y;
    }
    QPointF Point::position() const
    {
        return QPointF(X, Y);
    }

    void Point::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (!visible)
            return;

        int diffzoom = 0;
        if (homelevel > 0)
        {

            int currentzoom = mapadapter->maxZoom() < mapadapter->minZoom() ? mapadapter->minZoom() - mapadapter->currentZoom() : mapadapter->currentZoom();

            // int currentzoom = mapadapter->getZoom();
            diffzoom = homelevel-currentzoom;
            int viewheight = size.height();
            int viewwidth = size.width();
            viewheight = int(viewheight / pow(2, diffzoom));
            viewwidth = int(viewwidth / pow(2, diffzoom));

            if (minsize.height() != -1 && viewheight < minsize.height())
                viewheight = minsize.height();
            else if (maxsize.height() != -1 && viewheight > maxsize.height())
                viewheight = maxsize.height();


            if (minsize.width() != -1 && viewwidth < minsize.width())
                viewwidth = minsize.width();
            else if (maxsize.width() != -1 && viewwidth > maxsize.width())
                viewwidth = maxsize.width();


            displaysize = QSize(viewwidth, viewheight);
        }
        else
        {
            displaysize = size;
        }


        if (mypixmap !=0)
        {
            const QPointF c = QPointF(X, Y);
            QPoint point = mapadapter->coordinateToDisplay(c);


            QPoint alignedtopleft = alignedPoint(point);
            painter->drawPixmap(alignedtopleft.x(), alignedtopleft.y(), displaysize.width(), displaysize.height(), *mypixmap);


        }
        else if (mywidget!=0)
        {
            drawWidget(mapadapter, offset);
        }
    }

    void Point::drawWidget(const MapAdapter* mapadapter, const QPoint offset)
    {
        const QPointF c = QPointF(X, Y);
        QPoint point = mapadapter->coordinateToDisplay(c);
        point -= offset;

        QPoint alignedtopleft = alignedPoint(point);
        mywidget->setGeometry(alignedtopleft.x(), alignedtopleft.y(), displaysize.width(), displaysize.height());
    }

    QPoint Point::alignedPoint(const QPoint point) const
    {
        QPoint alignedtopleft;
        if (myalignment == Middle)
        {
            alignedtopleft.setX(point.x()-displaysize.width()/2);
            alignedtopleft.setY(point.y()-displaysize.height()/2);
        }
        else if (myalignment == TopLeft)
        {
            alignedtopleft.setX(point.x());
            alignedtopleft.setY(point.y());
        }
        else if (myalignment == TopRight)
        {
            alignedtopleft.setX(point.x()-displaysize.width());
            alignedtopleft.setY(point.y());
        }
        else if (myalignment == BottomLeft)
        {
            alignedtopleft.setX(point.x());
            alignedtopleft.setY(point.y()-displaysize.height());
        }
        else if (myalignment == BottomRight)
        {
            alignedtopleft.setX(point.x()-displaysize.width());
            alignedtopleft.setY(point.y()-displaysize.height());
        }
        return alignedtopleft;
    }


    bool Point::Touches(Point* p, const MapAdapter* mapadapter)
    {
        if (this->isVisible() == false)
            return false;
        if (mypixmap == 0)
            return false;

        QPointF c = p->position();
        // coordinate to pixel
        QPoint pxOfPoint = mapadapter->coordinateToDisplay(c);
        // size/2 Pixel toleranz aufaddieren
        QPoint p1;
        QPoint p2;

        switch (myalignment)
        {
                        case Middle:
            p1 = pxOfPoint - QPoint(displaysize.width()/2,displaysize.height()/2);
            p2 = pxOfPoint + QPoint(displaysize.width()/2,displaysize.height()/2);
            break;
                        case TopLeft:
            p1 = pxOfPoint - QPoint(displaysize.width(),displaysize.height());
            p2 = pxOfPoint;
            break;
                        case TopRight:
            p1 = pxOfPoint - QPoint(0, displaysize.height());
            p2 = pxOfPoint + QPoint(displaysize.width(),0);
            break;
                        case BottomLeft:
            p1 = pxOfPoint - QPoint(displaysize.width(), 0);
            p2 = pxOfPoint + QPoint(0, displaysize.height());
            break;
                        case BottomRight:
            p1 = pxOfPoint;
            p2 = pxOfPoint + QPoint(displaysize.width(), displaysize.height());
            break;
        }

        // calculate "Bounding Box" in coordinates
        QPointF c1 = mapadapter->displayToCoordinate(p1);
        QPointF c2 = mapadapter->displayToCoordinate(p2);


        if(this->longitude()>=c1.x() && this->longitude()<=c2.x())
        {
            if (this->latitude()<=c1.y() && this->latitude()>=c2.y())
            {
                return true;
            }
        }
        return false;
    }

    void Point::setCoordinate(QPointF point)
    {

        X = point.x();
        Y = point.y();
        emit(updateRequestRect(QRectF(X, Y, size.width(), size.height())));

        emit(positionChanged(this));
    }
    QPolygonF Point::points()
    {
        QPolygonF points;
        points.append(QPointF(X, Y));
        return points;
    }

    QWidget* Point::widget()
    {
        return mywidget;
    }

    QPixmap* Point::pixmap()
    {
        return mypixmap;
    }

    void Point::setBaselevel(int zoomlevel)
    {
        homelevel = zoomlevel;
    }
    void Point::setMinsize(QSize minsize)
    {
        this->minsize = minsize;
    }
    void Point::setMaxsize(QSize maxsize)
    {
        this->maxsize = maxsize;
    }
    Point::Alignment Point::alignment() const
    {
        return myalignment;
    }

    void Point::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

}
