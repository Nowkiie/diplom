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

#include "layermanager.h"
#include <QCoreApplication>
#include <QTime>
#include "core/distanceconverters.h"

namespace qmapcontrol
{
    LayerManager::LayerManager(MapControl* mapcontrol, QSize size)
        :mapcontrol(mapcontrol)
        , scroll(QPoint(0, 0))
        , size(size)
        , zoomImageScroll(QPoint(0, 0))
        , mapmiddle_px(QPoint(0, 0))
        , _mapBoundingEnabled(true)
        , composedOffscreenImage(size)
        , distanceConverter_(std::make_shared<DistanceKilometersConverter>())
    {

        screenmiddle = QPoint(size.width()/2, size.height()/2);
    }


    LayerManager::~LayerManager()
    {
        for(Layer *layer : mylayers)
        {
            delete layer;
        }

        mylayers.clear();
    }

    QPointF LayerManager::currentCoordinate() const
    {
        return mapmiddle;
    }



    Layer* LayerManager::layer() const
    {
        Q_ASSERT_X(mylayers.size()>0, "LayerManager::getLayer()", "No layers were added!");

        /* Poylov-MV: пытаемся найти первый видимый слой
        * если такого нет, то первый попавшийся
        * *** проблема при наличии нескольких слоев, когда нужно переключаться между ними
        * *** выбирался не активный слой и всегда перерисовывалась картинка (мерцание)
        */
        QListIterator<Layer*> layerit(mylayers);
        while (layerit.hasNext())
        {
            Layer* l = layerit.next();
            if (l->isVisible())
                return l;
        }

        return mylayers.first();
    }

    Layer* LayerManager::layer(const QString& layername) const
    {
        QListIterator<Layer*> layerit(mylayers);
        while (layerit.hasNext())
        {
            Layer* l = layerit.next();
            if (l->layername() == layername)
                return l;
        }
        return 0;
    }

    QList<QString> LayerManager::layers() const
    {
        QList<QString> keys;
        QListIterator<Layer*> layerit(mylayers);
        while (layerit.hasNext())
        {
            keys.append(layerit.next()->layername());
        }
        return keys;
    }


    void LayerManager::scrollView(const QPoint& point)
    {
        int height = layer()->mapadapter()->tilesize()*(pow(2, (double)currentZoom()));

        /* Poylov-MV: ограничение выхода за края карты */
        QPoint offset = point;
        if (mapmiddle_px.y() + offset.y() - screenmiddle.y() < 0)
        {
            offset = QPoint(offset.x(), 0);
        }
        else if (mapmiddle_px.y() + offset.y() + screenmiddle.y() > height)
        {
            offset = QPoint(offset.x(), height - mapmiddle_px.y() - screenmiddle.y());
        }

        scroll += offset;
        zoomImageScroll += offset;
        mapmiddle_px += offset;

        while(mapmiddle_px.x()<0)
            mapmiddle_px.rx()+=height;

        while(mapmiddle_px.x()>height)
            mapmiddle_px.rx()-=height;
            
        mapmiddle = layer()->mapadapter()->displayToCoordinate(mapmiddle_px);
        if (!checkOffscreen())
        {
            newOffscreenImage();
        }
        else
        {
            moveWidgets();
        }
    }

    void LayerManager::moveWidgets()
    {
        QListIterator<Layer*> it(mylayers);
        while (it.hasNext())
        {
            it.next()->moveWidgets(mapmiddle_px);
        }
    }

    void LayerManager::setView(const QPointF& coordinate)
    {
        mapmiddle_px = layer()->mapadapter()->coordinateToDisplay(coordinate);
        updateMapBounding();
        mapmiddle = coordinate;

        //TODO: muss wegen moveTo() raus
        if (!checkOffscreen())
        {
            newOffscreenImage();
        }
        else
        {
            //TODO:
            // verschiebung ausrechnen
            // oder immer neues offscreenimage
            newOffscreenImage();
        }
    }

    void LayerManager::setView(QList<QPointF> coordinates)
    {
        setMiddle(coordinates);
    }

    void LayerManager::setViewAndZoomIn(const QList<QPointF> coordinates)
    {
        QList<QPointF> crd = coordinates;
        // Poylov-MV: переносим все координаты в область -180*180
        for (int i = 0; i < crd.length(); i++)
        {
            QPointF p = crd[i];
            while (p.x() < -180) p.rx() += 360;
            while (p.x() > 180) p.rx() -= 360;
            crd.replace(i, p);
        }

        mapcontrol->setUpdatesEnabled(false);
        setMapBoundingEnabled(false);
        setMiddle(crd);

        int height;
        while (containsAll(crd) && currentZoom() <= layer()->mapAdapter->maxZoom())
        {
            zoomIn();
        }
        while (!containsAll(crd) && currentZoom() > layer()->mapAdapter->minZoom())
        {
            height = layer()->mapadapter()->tilesize()*(pow(2, (double)currentZoom() - 1));
            if (screenmiddle.x() > height / 2) break;
            zoomOut();
        }

        setMapBoundingEnabled(true);
        mapcontrol->setUpdatesEnabled(true);
        setMiddle(crd);

        mapcontrol->update();
    }

    void LayerManager::setMiddle(QList<QPointF> coordinates)
    {
        qreal sum_x = 0;
        qreal sum_y = 0;

        // Poylov-MV: расчет на основе мировых координат
        for (int i = 0; i<coordinates.size(); i++)
        {
            // mitte muss in px umgerechnet werden, da aufgrund der projektion die mittebestimmung aus koordinaten ungenau ist
            QPointF p = coordinates.at(i);
            sum_x += p.x();
            sum_y += p.y();
        }
        QPointF middle = QPoint(sum_x / coordinates.size(), sum_y / coordinates.size());

        setView(middle);
    }

    bool LayerManager::containsAll(QList<QPointF> coordinates) const
    {
        QRectF bb = getViewport();
        bool containsall = true;
        for (int i=0; i<coordinates.size(); i++)
        {
            if (!bb.contains(coordinates.at(i)))
                return false;
        }
        return containsall;
    }
    QPoint LayerManager::getMapmiddle_px() const
    {
        return mapmiddle_px;
    }

    QRectF LayerManager::getViewport() const
    {
        QPoint upperLeft = QPoint(mapmiddle_px.x()-screenmiddle.x(), mapmiddle_px.y()+screenmiddle.y());
        QPoint lowerRight = QPoint(mapmiddle_px.x()+screenmiddle.x(), mapmiddle_px.y()-screenmiddle.y());

        QPointF ulCoord = layer()->mapadapter()->displayToCoordinate(upperLeft);
        QPointF lrCoord = layer()->mapadapter()->displayToCoordinate(lowerRight);

        QRectF coordinateBB = QRectF(ulCoord, QSizeF( (lrCoord-ulCoord).x(), (lrCoord-ulCoord).y()));
        return coordinateBB;
    }

    void LayerManager::addLayer(Layer* layer)
    {
        layer->applyDistanceConverter(distanceConverter_);

        int lastZoom{};
        if (mylayers.size())
        {
            lastZoom = currentZoom();
        }

        mylayers.append(layer);

        layer->setSize(size);

        connect(layer, &Layer::updateRequest,
                this, &LayerManager::updateRequest);
        connect(layer, &Layer::updateRequest,
                this, &LayerManager::updateRequest);

        connect(layer, &Layer::imageReceived,
            this, &LayerManager::updateRequestNew);

        connect(layer, &Layer::imageReceivedTile,
            this, &LayerManager::updateRequestNewTile);

        connect(layer, &Layer::loadingFinished,
            this, &LayerManager::loadingFinished);


        if (mylayers.size()==1)
        {
            setView(QPointF(0,0));
        }
        while (lastZoom--)
        {
            layer->zoomIn();
        }
    }

    void LayerManager::applyDistanceConverter(IDistanceConverterPtr distanceConverter)
    {
        distanceConverter_ = distanceConverter;
        for (auto& layer : mylayers)
        {
            layer->applyDistanceConverter(distanceConverter_);
        }
    }

    void LayerManager::newOffscreenImage(bool clearImage, bool showZoomImage)
    {

        // Poylov-MV: замедляет отрисовку
        mapcontrol->update();
    }

    void LayerManager::updateRequestNewTile(int x, int y, int z)
    {


        // Poylov-MV: замедляет отрисовку
        mapcontrol->update();
    }
    void LayerManager::updateRequestNew()
    {
        /* Poylov-MV сильно затормаживает загрузку, но необходима для постепенной отрисовки загруженных картинок... */
        /* влияет на подтормаживания при загрузке, а также на скакание картинок */
        forceRedraw();
    }
    void LayerManager::zoomIn()
    {
        for (Layer *layer : mylayers)
        {
            layer->abortLoading();
        }


        QListIterator<Layer*> it(mylayers);
        //TODO: remove hack, that mapadapters wont get set zoom multiple times
        QList<const MapAdapter*> doneadapters;
        while (it.hasNext())
        {
            Layer* l = it.next();
            
            if (!doneadapters.contains(l->mapadapter()))
            {
                l->zoomIn();
                doneadapters.append(l->mapadapter());
            }
        }
        mapmiddle_px = layer()->mapadapter()->coordinateToDisplay(mapmiddle);


        newOffscreenImage();
    }

    bool LayerManager::checkOffscreen() const
    {
        // calculate offscreenImage dimension (px)
        QPoint upperLeft = mapmiddle_px - screenmiddle;
        QPoint lowerRight = mapmiddle_px + screenmiddle;
        QRect viewport = QRect(upperLeft, lowerRight);

        QRect testRect = layer()->offscreenViewport();

        if (!testRect.contains(viewport))
        {
            return false;
        }

        return true;
    }
    void LayerManager::zoomOut()
    {
        for (Layer *layer : mylayers)
        {
            layer->abortLoading();
        }

        QListIterator<Layer*> it(mylayers);
        //TODO: remove hack, that mapadapters wont get set zoom multiple times
        QList<const MapAdapter*> doneadapters;
        while (it.hasNext())
        {
            Layer* l = it.next();
            if (!doneadapters.contains(l->mapadapter()))
            {
                l->zoomOut();
                doneadapters.append(l->mapadapter());
            }
        }
        mapmiddle_px = layer()->mapadapter()->coordinateToDisplay(mapmiddle);
        updateMapBounding();

        newOffscreenImage();
    }

    void LayerManager::setZoom(int zoomlevel)
    {
        int current_zoom;
        if (layer()->mapadapter()->minZoom() < layer()->mapadapter()->maxZoom())
        {
            current_zoom = layer()->mapadapter()->currentZoom();
        }
        else
        {
            current_zoom = layer()->mapadapter()->minZoom() - layer()->mapadapter()->currentZoom();
        }


        if (zoomlevel < current_zoom)
        {
            for (int i=current_zoom; i>zoomlevel; i--)
            {
                zoomOut();
            }
        }
        else
        {
            for (int i=current_zoom; i<zoomlevel; i++)
            {
                zoomIn();
            }
        }
    }

    void LayerManager::mouseEvent(QMouseEvent* evnt)
    {
        QListIterator<Layer*> it(mylayers);
        while (it.hasNext())
        {
            Layer* l = it.next();
            if (l->isVisible())
            {
                l->mouseEvent(evnt, mapmiddle_px);
            }
        }
    }

    void LayerManager::updateRequestRect(QRectF rect)
    {
        const QPoint topleft = mapmiddle_px - screenmiddle;

        QPointF c = rect.topLeft();

        if (getViewport().contains(c) || getViewport().contains(rect.bottomRight()))
        {
            mapcontrol->update();
        }
    }
    void LayerManager::updateRequest()
    {
        newOffscreenImage();
    }
    void LayerManager::forceRedraw()
    {
        newOffscreenImage();
    }

    void LayerManager::drawGeoms(QPainter* painter)
    {
        QListIterator<Layer*> it(mylayers);
        while (it.hasNext())
        {
            Layer* l = it.next();
            if (l->layertype() == Layer::GeometryLayer && l->isVisible())
            {
                l->drawYourGeometries(painter, mapmiddle_px, getViewport()); 
            }
        }
    }
    void LayerManager::drawImage(QPainter* painter)
    {
        QPainter imagePainter(&composedOffscreenImage);
        for (int i = 0; i < mylayers.count(); i++)
        {
            Layer* l = mylayers.at(i);
            if (l->isVisible())
            {
                if (l->layertype() == Layer::MapLayer)
                {
                    l->drawYourImage(&imagePainter, mapmiddle_px);
                }
            }
        }
        painter->drawPixmap(0, 0, composedOffscreenImage);
    }

    int LayerManager::currentZoom() const
    {
        return layer()->mapadapter()->currentZoom();
    }

    void LayerManager::resize(QSize newSize)
    {
        int height = layer()->mapadapter()->tilesize()*(pow(2, (double)currentZoom()));

        size = newSize;

        composedOffscreenImage = QPixmap(newSize);
		composedOffscreenImage.fill(Qt::black);

        screenmiddle = QPoint(newSize.width() / 2, newSize.height() / 2);

        /* Poylov-MV: { ограничение выхода за края карты */
        QPoint sm = screenmiddle;
        QPoint mm = mapmiddle_px;
        while (sm.y() * 2 > height)
        {
            zoomIn();

            if (height >= sm.y())
            {
                QPoint offset;
                if (mm.y() < sm.y())
                {
                    offset = QPoint(0, sm.y() - mm.y());
                }
                else if (mm.y() + sm.y() > height)
                {
                    offset = QPoint(0, height - (mm.y() + sm.y()));
                }
                scrollView(offset);
            }

            mm = mapmiddle_px;
            height = layer()->mapadapter()->tilesize()*(pow(2, (double)currentZoom()));
        }

        updateMapBounding();
        /* Poylov-MV: } ограничение выхода за края карты */

        QListIterator<Layer*> it(mylayers);
        while (it.hasNext())
        {
            Layer* l = it.next();
            l->setSize(newSize);
        }

        newOffscreenImage();
    }

    void LayerManager::setMapBoundingEnabled(bool enabled)
    {
        _mapBoundingEnabled = enabled;
        if (enabled) updateMapBounding();
    }

    void LayerManager::updateMapBounding()
    {
        if (!_mapBoundingEnabled) return;

        int height = layer()->mapadapter()->tilesize()*(pow(2, (double)currentZoom()));
        if (mapmiddle_px.y() - screenmiddle.y() < 0)
        {
            mapmiddle_px.ry() = screenmiddle.y();
        }
        else if ((height - mapmiddle_px.y()) - screenmiddle.y() < 0)
        {
            mapmiddle_px.ry() = height - screenmiddle.y();
        }
        mapmiddle = layer()->mapadapter()->displayToCoordinate(mapmiddle_px);
    }



    void LayerManager::loadingFinished()
    {
        forceRedraw();
    }

}
