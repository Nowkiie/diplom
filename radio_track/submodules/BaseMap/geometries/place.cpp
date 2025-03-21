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

#include "place.h"
#include "qpen.h"

#include <QRadialGradient>

namespace qmapcontrol
{
    Place::Place(QPointF point, int radius, QString name, Alignment alignment, QPen pen)
        : Point(point.x(), point.y(), name, alignment)
    {
        radius_ = radius;
        size = QSize(radius_, radius_);

        setPen(pen);

    }


    Place::~Place()
    {
    }

    void Place::setPen(QPen pen)
    {
        mypen = pen;

        if (mypixmap != NULL) delete mypixmap;

        mypixmap = new QPixmap(radius_ + 1, radius_ + 1);
        mypixmap->fill(Qt::transparent);
        QPainter painter(mypixmap);

        painter.setPen(Qt::NoPen);

        QBrush brush(pen.color(), Qt::SolidPattern);

        painter.setBrush(brush);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawEllipse(0, 0, size.width(), size.height());
    }

    void Place::setRadius(qreal radius)
    {
        radius_ = radius;
    }

    qreal Place::radius()
    {
        return radius_;
    }

    void Place::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

}
