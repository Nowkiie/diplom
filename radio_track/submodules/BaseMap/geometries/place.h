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

#ifndef SIMPLEPOINT_H
#define SIMPLEPOINT_H

#include "point.h"

namespace qmapcontrol
{
    /*!
    *    Класс для рисования объекта Место в виде закрашенной точки
    *    @author Maxim Poylov
    */
    class Place : public Point
    {
    public:
        //!
        /*!
         *
         * @param x longitude
         * @param y latitude
         * @param name name of the circle point
         * @param alignment alignment (Middle or TopLeft)
         * @param pen QPen for drawing
         */
        //Place(QPointF point, QString name = QString(), Alignment alignment = Middle, QPen pen = QPen());

        //!
        /*!
         *
         * @param x longitude
         * @param y latitude
         * @param radius the radius of the circle
         * @param name name of the circle point
         * @param alignment alignment (Middle or TopLeft)
         * @param pen QPen for drawing
         */
        Place(QPointF point, int radius = 10, QString name = QString(), Alignment alignment = Middle, QPen pen = QPen());
        virtual ~Place();

        //! sets the QPen which is used for drawing the circle
        /*!
         * A QPen can be used to modify the look of the drawn circle
         * @param pen the QPen which should be used for drawing
         * @see http://doc.trolltech.com/4.3/qpen.html
         */
        virtual void setPen(QPen pen);

        void accept(GeometryVisitor *visitor);

        void setRadius(qreal radius);
        qreal radius();
    private:
        qreal radius_;
    };
}
#endif //SIMPLEPOINT_H
