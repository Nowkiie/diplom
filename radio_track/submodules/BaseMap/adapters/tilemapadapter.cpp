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

#include "tilemapadapter.h"
#include "core/urlconverter.h"



namespace qmapcontrol
{
    TileMapAdapter::TileMapAdapter(const QString& host, int tilesize, int minZoom, int maxZoom)
        :MapAdapter(host, "", tilesize, minZoom, maxZoom)
    {
        PI = acos(-1.0);

        int zoom = max_zoom < min_zoom ? min_zoom - current_zoom : current_zoom;
        numberOfTiles = tilesonzoomlevel(zoom);
    }

    TileMapAdapter::~TileMapAdapter()
    {
    }
    //TODO: pull out
    void TileMapAdapter::zoom_in()
    {
        if (min_zoom > max_zoom)
        {
            //current_zoom = current_zoom-1;
            current_zoom = current_zoom > max_zoom ? current_zoom-1 : max_zoom;
        }
        else if (min_zoom < max_zoom)
        {
            //current_zoom = current_zoom+1;
            current_zoom = current_zoom < max_zoom ? current_zoom+1 : max_zoom;
        }

        int zoom = max_zoom < min_zoom ? min_zoom - current_zoom : current_zoom;
        numberOfTiles = tilesonzoomlevel(zoom);

    }
    void TileMapAdapter::zoom_out()
    {
        if (min_zoom > max_zoom)
        {
            //current_zoom = current_zoom+1;
            current_zoom = current_zoom < min_zoom ? current_zoom+1 : min_zoom;
        }
        else if (min_zoom < max_zoom)
        {
            //current_zoom = current_zoom-1;
            current_zoom = current_zoom > min_zoom ? current_zoom-1 : min_zoom;
        }

        int zoom = max_zoom < min_zoom ? min_zoom - current_zoom : current_zoom;
        numberOfTiles = tilesonzoomlevel(zoom);
    }

    qreal TileMapAdapter::deg_rad(qreal x) const
    {
        return x * (PI/180.0);
    }
    qreal TileMapAdapter::rad_deg(qreal x) const
    {
        return x * (180/PI);
    }

    QString TileMapAdapter::query(int x, int y, int z) const
    {
        x = xoffset(x);
        y = yoffset(y);
        return tilesToUrl(x, y, z, this);
    }
    void TileMapAdapter::fromQuery(QString query, int &x, int &y, int &z) const
    {
        urlToTiles(query, x, y, z);
    }
    QPoint TileMapAdapter::coordinateToDisplay(const QPointF& coordinate) const
    {
        // ограничение координат до допустимого уровня
        qreal y = coordinate.y();
        qreal x = (coordinate.x() + 180) * (numberOfTiles*mytilesize) / 360.; // coord to pixel!
        y = (1-(log(tan(PI/4+deg_rad(y)/2)) /PI)) /2  * (numberOfTiles*mytilesize);

        return QPoint(int(x), int(y));
    }

    QPointF TileMapAdapter::displayToCoordinate(const QPoint& point) const
    {
        qreal longitude = (point.x()*(360/(numberOfTiles*mytilesize)))-180;
        qreal latitude = rad_deg(atan(sinh((1-point.y()*(2/(numberOfTiles*mytilesize)))*PI)));

        return QPointF(longitude, latitude);
    }

    bool TileMapAdapter::isValid(int x, int y, int z) const
    {
        if (max_zoom < min_zoom)
        {
            z= min_zoom - z;
        }

        if (x<0 || x>pow(2,z)-1 ||
            y<0 || y>pow(2,z)-1)
        {
            return false;
        }
        return true;

    }
    int TileMapAdapter::tilesonzoomlevel(int zoomlevel) const
    {
        return int(pow(2, zoomlevel));
    }
    int TileMapAdapter::xoffset(int x) const
    {
        return x;
    }
    int TileMapAdapter::yoffset(int y) const
    {
        return y;
    }
}
