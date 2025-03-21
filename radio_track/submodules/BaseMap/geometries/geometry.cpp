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

#include "geometry.h"
namespace qmapcontrol
{
    Geometry::Geometry(QString name)
        : GeometryType("Geometry"), myparentGeometry(0), mypen(QPen()), visible(true), myname(name), myinfo(QString())
    {
    }

    Geometry::~Geometry()
    {
    }

    QString Geometry::name() const
    {
        return myname;
    }

    QString Geometry::info() const
    {
        return myinfo;
    }

    Geometry* Geometry::parentGeometry() const
    {
        return myparentGeometry;
    }

    void Geometry::setParentGeometry(Geometry* geom)
    {
        myparentGeometry = geom;
    }
    
    bool Geometry::hasPoints() const
    {
        return false;
    }
    
    bool Geometry::hasClickedPoints() const
    {
        return false;
    }
    
    QList<Geometry*> Geometry::clickedPoints()
    {
        QList<Geometry*> tmp;
        return tmp;
    }

    bool Geometry::isVisible() const
    {
        return visible;
    }
    
    void Geometry::setVisible(bool visible)
    {
        this->visible = visible;
        emit(updateRequestRect(boundingBox()));
    }

    void Geometry::setName(QString name)
    {
        myname = name;
    }

    void Geometry::setInfo(QString info)
    {
        myinfo = info;
    }

    void Geometry::setPen(QPen pen)
    {
        mypen = pen;
    }

    QPen Geometry::pen() const
    {
        return mypen;
    }

    void Geometry::setUserData(QVariant data)
    {
        userData_ = data;
    }

    QVariant Geometry::userData() const
    {
        return userData_;
    }
    
    void Geometry::onMouseEnter(QMouseEvent* evnt)
    {
        emit(mouseEnter(this, evnt));
    }

    void Geometry::onMouseOver(QMouseEvent* evnt)
    {
        emit(mouseOver(this, evnt));
    }

    void Geometry::onMouseLeave(QMouseEvent* evnt)
    {
        emit(mouseLeave(this, evnt));
    }
    
    void Geometry::onMouseClick(QMouseEvent* evnt)
    {
        emit(mouseClick(this, evnt));
    }

    void Geometry::onMouseDoubleClick(QMouseEvent* evnt)
    {
        emit(mouseDoubleClick(this, evnt));
    }

}
