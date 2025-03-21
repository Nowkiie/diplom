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

#include "layer.h"
#include "adapters/localmapadapter.h"
#include <QTime>
#include <QTimer>
#include <QPixmap>
#include <QMessageBox>
#include <QScreen>
#include <QApplication>
#include <unordered_set>
#include <cmath>

namespace qmapcontrol
{

Layer::Layer(QString layername, MapAdapter* mapAdapter, MapLoader* mapLoader,
             enum LayerType layertype, bool takeevents)
    : visible(true)
    , mylayername(layername)
    , mylayertype(layertype)
    , takeevents(takeevents)
    , myoffscreenViewport(QRect(0, 0, 0, 0))
    , _clickEvent(QEvent::Type::None, QPointF(), Qt::MouseButton::NoButton,
                  Qt::MouseButton::NoButton, Qt::KeyboardModifier::NoModifier)
    , mapAdapter(mapAdapter)
    , tilesCount_(tilesCount(mapAdapter->tilesize()))
{
    imageManager = new ImageManager(mapLoader);

    connect(imageManager, &ImageManager::imageReceived, this,
            &Layer::imageReceivedTile);

    connect(imageManager, &ImageManager::loadingFinished, this,
            &Layer::loadingFinished);
}

Layer::~Layer()
{
    delete mapAdapter;
    delete imageManager;
}

void Layer::setSize(QSize size)
{
    this->size = size;
    screenmiddle = QPoint(size.width() / 2, size.height() / 2);
}

QString Layer::layername() const
{
    return mylayername;
}

const MapAdapter* Layer::mapadapter() const
{
    return mapAdapter;
}

void Layer::setVisible(bool visible)
{
    this->visible = visible;
    emit(updateRequest());
}

void Layer::addGeometry(Geometry* geom)
{
    QMutexLocker locker(&geometryListMutex_);

    geometries.append(geom);
    emit(updateRequestRect(geom->boundingBox()));
    //a geometry can request a redraw, e.g. when its position has been changed
    connect(geom, &Geometry::updateRequestRect, this,
            &Layer::updateRequestRect);
}

void Layer::addGeometries(QList<Geometry*> geometies)
{
    QMutexLocker locker(&geometryListMutex_);
    foreach (Geometry* geom, geometies)
    {
        geometries.append(geom);
        //a geometry can request a redraw, e.g. when its position has been changed
        connect(geom, &Geometry::updateRequestRect, this,
                &Layer::updateRequestRect);
    }
    emit(updateRequest());
}

void Layer::removeGeometry(Geometry* geometry)
{
    QMutexLocker locker(&geometryListMutex_);
    for (int i = 0; i < geometries.count(); i++)
    {
        if (geometry == geometries.at(i))
        {
            disconnect(geometry);
            geometries.removeAt(i);

            // убираем из списка объектов над которыми находится мышь
            if (mouseOverGeometries.contains(geometry))
            {
                mouseOverGeometries.removeAll(geometry);
            }
        }
    }
}

void Layer::clearGeometries()
{
    QMutexLocker locker(&geometryListMutex_);
    foreach (Geometry* geometry, geometries)
    {
        disconnect(geometry);
    }
    geometries.clear();
    mouseOverGeometries.clear();
    emit(updateRequest());
}
bool Layer::deleteGeometry(Geometry* geom)
{
    QMutexLocker locker(&geometryListMutex_);
    for (auto geometry = geometries.begin(); geometry != geometries.end();
         geometry++)
    {
        if (geom->name() == (*geometry)->name())
        {
            Point* pt1 = qobject_cast<Point*>(geom);
            Point* pt2 = qobject_cast<Point*>((*geometry));
            if (pt1 && pt2)
            {
                if (pt1->position() == pt2->position())
                {
                    disconnect((*geometry));
                    geometries.erase(geometry);
                    mouseOverGeometries.removeAll(*geometry);
                    return true;
                }
            }
        }
    }

    return false;
}

bool Layer::isVisible() const
{
    return visible;
}
void Layer::zoomIn()
{
    mapAdapter->zoom_in();
}
void Layer::zoomOut()
{
    mapAdapter->zoom_out();
}

void Layer::checkDoubleClick()
{
    // ожидаем, что в счетчике может быть значение, только больше 0
    // поэтому проверяем на совпадение с 1 - если да - одинарное нажатие,
    // иначе - двойное
    bool dbl = false;
    QMouseEvent evt = _clickEvent;
    QPoint mm = _mapmiddle_px;
    if (!_ai_click.testAndSetRelaxed(1, 0))
    {
        dbl = true;
        _ai_click.storeRelease(0);
    }

    if (evt.button() == Qt::LeftButton
        && evt.type() == QEvent::MouseButtonRelease)
    {
        // check for collision
        QPointF c = mapAdapter->displayToCoordinate(
            QPoint(evt.x() - screenmiddle.x() + mm.x(),
                   evt.y() - screenmiddle.y() + mm.y()));

        while (c.x() >= 180) c.rx() -= 360;
        while (c.x() <= -180) c.rx() += 360;
        Point tmppoint(c.x(), c.y());
        for (int i = geometries.count() - 1; i >= 0; i--)
        {
            if (!evt.isAccepted() && geometries.at(i)->isVisible()
                && geometries.at(i)->Touches(&tmppoint, mapAdapter))
            {
                if (dbl)
                    geometries.at(i)->onMouseDoubleClick(&evt);
                else
                    geometries.at(i)->onMouseClick(&evt);
            }
        }
    }
}

void Layer::mouseEvent(QMouseEvent* evnt, const QPoint mapmiddle_px)
{
    if (takesMouseEvents())
    {
        if (geometries.count() == 0)
            return;

        evnt->setAccepted(false);
        // запускам таймер для проверки - было ли двойное нажатие
        if (evnt->type() == QEvent::MouseButtonRelease)
        {
            if (_ai_click.fetchAndAddRelaxed(1) == 0)
            {
                // все предыдущие нажатия обработаны - запускаем новую обработку
                _clickEvent = (*evnt);
                _mapmiddle_px = mapmiddle_px;
                QTimer::singleShot(200, this, SLOT(checkDoubleClick()));
            }
        }
        // иначе предполагаем, что обработка ещё будет...

        /* отслеживание положения мыши относительно объекта */
        if (evnt->button() == Qt::NoButton && evnt->type() == QEvent::MouseMove)
        {
            QList<Geometry*> gl;
            // check for collision
            QPointF c = mapAdapter->displayToCoordinate(
                QPoint(evnt->x() - screenmiddle.x() + mapmiddle_px.x(),
                       evnt->y() - screenmiddle.y() + mapmiddle_px.y()));

            while (c.x() >= 180) c.rx() -= 360;
            while (c.x() <= -180) c.rx() += 360;
            Point tmppoint(c.x(), c.y());
            for (int i = 0; i < geometries.count(); i++)
            {
                if (geometries.at(i)->isVisible()
                    && geometries.at(i)->Touches(&tmppoint, mapAdapter))
                {
                    // заполняем список объектов над которыми находится указатель мыши
                    gl.append(geometries.at(i));
                }
            }

            // сравниваем предыдущий список с новым
            // 1. генерируем событие покидания геометрии для пропаших объектов
            // 2. гененируем событие входа в геометрию для новых объектов
            for (int i = 0; i < mouseOverGeometries.count(); i++)
            {
                auto it =
                    qFind(gl.begin(), gl.end(), mouseOverGeometries.at(i));
                if (it == gl.end())
                {
                    mouseOverGeometries.at(i)->onMouseLeave(evnt);
                }
            }
            for (int i = gl.count() - 1; i >= 0; i--)
            {
                auto it = qFind(mouseOverGeometries.begin(),
                                mouseOverGeometries.end(), gl.at(i));
                if (it == mouseOverGeometries.end())
                {
                    gl.at(i)->onMouseEnter(evnt);
                }
                if (!evnt->isAccepted())
                    gl.at(i)->onMouseOver(evnt);
            }
            gl.swap(mouseOverGeometries);
        }
    }
}

bool Layer::takesMouseEvents() const
{
    return takeevents;
}

void Layer::drawYourImage(QPainter* painter, const QPoint mapmiddle_px)
{
    if (mylayertype == MapLayer)
    {
        _draw(painter, mapmiddle_px);
    }
}

void Layer::drawYourGeometries(QPainter* painter, const QPoint mapmiddle_px,
                               QRectF viewport)
{
    QPoint offset;

    // Poylov-MV: отрисовка с учетом зацикливания карты
    // определяем сколько карт отображается слева и справа от центра экрана
    int tilesize = mapAdapter->tilesize();
    int tileMapSize = tilesize * pow(2, int(mapAdapter->currentZoom()));
    int moffset = screenmiddle.x() - mapmiddle_px.x();
    int leftMaps = 0;
    if (moffset > 0)
        leftMaps = (moffset + (tileMapSize - 1)) / tileMapSize;
    moffset = screenmiddle.x() - (tileMapSize - mapmiddle_px.x());
    int rightMaps = 0;
    if (moffset > 0)
        rightMaps = (moffset + (tileMapSize - 1)) / tileMapSize;

    QMutexLocker locker(&geometryListMutex_);
    QPoint translateOffset;

    for (int i = -leftMaps; i <= rightMaps; i++)
    {
        if (mylayertype == MapLayer && geometries.count() == 0)
            offset = mapmiddle_px;
        else
            offset = mapmiddle_px - screenmiddle;
        offset.rx() += i * tileMapSize;

        translateOffset = (-mapmiddle_px + screenmiddle);
        translateOffset.rx() += i * tileMapSize;
        painter->translate(translateOffset);
        for (int i = 0; i < geometries.count(); i++)
        {
            if (geometries.at(i)->isVisible())
            {
                geometries.at(i)->draw(painter, mapAdapter, viewport, offset);
            }
        }
        painter->translate(-translateOffset);
    }
}
QVector<LayerTilePosition> Layer::tilesToDraw(const QPoint mapmiddle_px,
                                              const QPoint screenmiddle) const
{
    QVector<LayerTilePosition> result;
    int tileSize = mapAdapter->tilesize();
    int z = mapAdapter->currentZoom();
    int k = pow(2, z);

    QPoint topLeftPx = mapmiddle_px - screenmiddle;
    QPoint screenSize = screenmiddle * 2;

    auto limitTile = [k](int index)
    {
        int result = index;
            while (result >= k)
        {
            result -= k;
        }
            while (result < 0)
        {
            result += k;
        }
        return result;
    };

    for (int x = -tileSize; x < screenSize.x() + tileSize; x += tileSize)
    {
        for (int y = -tileSize; y < screenSize.y() + tileSize; y += tileSize)
        {
            QPoint position = QPoint(x, y) + topLeftPx;
            QPoint globalTilePosition = position / tileSize * tileSize;
            QPoint screenTilePosition = globalTilePosition - topLeftPx;

            LayerTilePosition tilePosition{};
            tilePosition.x = limitTile(globalTilePosition.x() / tileSize);
            tilePosition.y = limitTile(globalTilePosition.y() / tileSize);

            tilePosition.z = z;
            tilePosition.sx = screenTilePosition.x();
            tilePosition.sy = screenTilePosition.y();
            result.push_back(tilePosition);
        }
    }

    return result;
}
bool Layer::tileCacheCheck(LayerTilePosition position) const
{
    for (const auto& obj : tileCache_)
    {
        if (obj.first == position)
        {
            return true;
        }
    }
    return false;
}
QPixmap Layer::tileCacheGet(LayerTilePosition position) const
{
    for (const auto& obj : tileCache_)
    {
        if (obj.first == position)
        {
            return obj.second;
        }
    }
    return QPixmap();
}
void Layer::tileCacheInsert(LayerTilePosition position, QPixmap pixmap)
{
    tileCache_.push_back({position, pixmap});
    if (tileCache_.size() > tilesCount_)
    {
        tileCache_.pop_front();
    }
}
int Layer::tilesCount(const int tilesize)
{
    QList<QScreen*> screens;
    screens = QApplication::screens();
    int maxTilesScreen = 0;
    for (auto* screen : screens)
    {
        int currentTilesScreen =
            ceil(static_cast<float>(screen->availableGeometry().height())
                 / tilesize)
            * ceil(static_cast<float>(screen->availableGeometry().width())
                   / tilesize);
        if (maxTilesScreen < currentTilesScreen)
            maxTilesScreen = currentTilesScreen;
    }
    return maxTilesScreen * 1.5;
}
void Layer::_draw(QPainter* painter, const QPoint mapmiddle_px)
{
    auto toDraw = tilesToDraw(mapmiddle_px, screenmiddle);
    for (const auto& tilePosition : toDraw)
    {
        QPixmap pixmap;
        if (tileCacheCheck(tilePosition))
        {
            pixmap = tileCacheGet(tilePosition);
        }
        else
        {
            pixmap = imageManager->getImage(tilePosition.x, tilePosition.y,
                                            tilePosition.z);
            if (pixmap.size().width() == 256)
            {
                tileCacheInsert(tilePosition, pixmap);
            }
        }
        painter->drawPixmap(tilePosition.sx, tilePosition.sy, pixmap);
    }
}

QRect Layer::offscreenViewport() const
{
    return myoffscreenViewport;
}

void Layer::moveWidgets(const QPoint mapmiddle_px) const
{
    for (int i = 0; i < geometries.count(); i++)
    {
        const Geometry* geom = geometries.at(i);
        if (geom->GeometryType == "Point")
        {
            if (((Point*)geom)->widget() != 0)
            {
                QPoint topleft_relative = QPoint(mapmiddle_px - screenmiddle);
                ((Point*)geom)->drawWidget(mapAdapter, topleft_relative);
            }
        }
    }
}
Layer::LayerType Layer::layertype() const
{
    return mylayertype;
}

void Layer::setMapAdapter(MapAdapter* mapadapter)
{
    mapAdapter = mapadapter;
}
void Layer::abortLoading()
{
    imageManager->abortLoading();
}

    void Layer::applyDistanceConverter(IDistanceConverterPtr distanceConverter)
    {
        mapAdapter->applyDistanceConverter(distanceConverter);
    }

}
