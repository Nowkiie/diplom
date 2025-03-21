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

#include "mapcontrol.h"
#include <math.h>

#include <QTimer>

#include <QTime>

#include "geometries/pelengbase.h"
#include "core/zoomleveldistances.h"
#include "core/distanceconverters.h"


#define DRAGGING_OR_PAINNING_START_DELTA 5

namespace qmapcontrol
{

    MapControl::MapControl(QSize size, QWidget *parent, MouseMode mousemode)
        : size_(size), mymousemode(mousemode), scaleVisible(false)
        , _clickEvent(QEvent::Type::None, QPointF(), Qt::MouseButton::NoButton,
            Qt::MouseButton::NoButton, Qt::KeyboardModifier::NoModifier)
        , cTranslator(NULL)
        , QWidget(parent)
        , distanceConverter_(std::make_shared<DistanceKilometersConverter>())
    {
        setAttribute(Qt::WA_OpaquePaintEvent);

        setFocusPolicy(Qt::StrongFocus);

        setSizePolicy(
            QSizePolicy(
                QSizePolicy::Policy::MinimumExpanding, 
                QSizePolicy::Policy::MinimumExpanding)
                );


        layermanager = new LayerManager(this, size);
        screen_middle = QPoint(size.width()/2, size.height()/2);

        mousepressed = false;

        this->showScale(true);
        this->setMouseTracking(true);
    }

    MapControl::~MapControl()
    {
        delete layermanager;
    }

    void MapControl::applyDistanceConverter(IDistanceConverterPtr converter) {
        distanceConverter_ = converter;
        layermanager->applyDistanceConverter(converter);
    }

    QPointF MapControl::currentCoordinate() const
    {
        return layermanager->currentCoordinate();
    }

    Layer* MapControl::layer(const QString& layername) const
    {
        return layermanager->layer(layername);
    }

    QList<QString> MapControl::layers() const
    {
        return layermanager->layers();
    }

    int MapControl::numberOfLayers() const
    {
        return layermanager->layers().size();
    }

    void MapControl::followGeometry(const Geometry* geom) const
    {
        connect(geom, &Geometry::positionChanged,
                this, &MapControl::positionChanged);
    }

    void MapControl::positionChanged(Geometry* geom)
    {
        QPoint start = layermanager->layer()->mapadapter()->coordinateToDisplay(currentCoordinate());
        QPoint dest = layermanager->layer()->mapadapter()->coordinateToDisplay(((Point*)geom)->position());

        QPoint step = (dest-start);

        layermanager->scrollView(step);

        update();
    }

    void MapControl::moveTo(QPointF coordinate)
    {
        target = coordinate;
        steps = 25;
        if (moveMutex.tryLock())
        {
            QTimer::singleShot(40, this, SLOT(tick()));
        }
    }
    void MapControl::tick()
    {
        QPoint start = layermanager->layer()->mapadapter()->coordinateToDisplay(currentCoordinate());
        QPoint dest = layermanager->layer()->mapadapter()->coordinateToDisplay(target);

        QPoint step = (dest-start)/steps;
        QPointF next = currentCoordinate()- step;

        layermanager->scrollView(step);

        update();
        steps--;
        if (steps>0)
        {
            QTimer::singleShot(40, this, SLOT(tick()));
        }
        else
        {
            moveMutex.unlock();
        }
    }

    void MapControl::paintEvent(QPaintEvent* evnt)
    {
        QWidget::paintEvent(evnt);
        QPainter painter(this);


        layermanager->drawImage(&painter);
        layermanager->drawGeoms(&painter);

        // added by wolf
        // draw scale
        if (scaleVisible)
        {
            const auto zoomLevel = currentZoom();

            ZoomLevelDistances zoomLevelDistances;
            if (zoomLevelDistances.hasDistance(zoomLevel))
            {
                const auto thousandthUnitDistance = zoomLevelDistances.distanceFor(zoomLevel);
                const auto unitDistance = static_cast<double>(thousandthUnitDistance) / 1000.0;
                const auto pixelDistance = computeScalePixelDistance(unitDistance);
                const auto unitDistanceAsText = distanceConverter_->toText(unitDistance);
                // рисование масштаба в левом нижнем углу карты
                drawMapScaleRuler(painter, pixelDistance, unitDistanceAsText);
            };
        }

        painter.drawLine(screen_middle.x(), screen_middle.y()-10,
                         screen_middle.x(), screen_middle.y()+10); // |
        painter.drawLine(screen_middle.x()-10, screen_middle.y(),
                         screen_middle.x()+10, screen_middle.y()); // -

        painter.drawRect(0,0, size_.width(), size_.height());
    

        
        
    
        emit viewChanged(currentCoordinate(), currentZoom());
    }

    void MapControl::checkDoubleClick()
    {
        // ожидаем, что в счетчике может быть значение, только больше 0
        // поэтому проверяем на совпадение с 2 (press + release) - если да - одинарное нажатие,
        // иначе - двойное
        QMouseEvent evt = _clickEvent;
        int val = _ai_click.fetchAndStoreRelaxed(0);
        if (val < 2) return;

        _ai_click.storeRelease(0);


        if (val > 2) emit(mouseDoubleClickEvent(&evt, translateCoordinate(clickToWorldCoordinate(evt.pos()))));
        else emit(mouseClickEvent(&evt, translateCoordinate(clickToWorldCoordinate(evt.pos()))));

    }

    // mouse events
    void MapControl::mousePressEvent(QMouseEvent* evnt)
    {
        evnt->setAccepted(false);
        emit(mousePressEvent(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        if (evnt->isAccepted()) return;

        /* Poylov-MV */
        mymousemode = MouseMode::None;

        if (layermanager->layers().size()>0)
        {
          //  if (evnt->button() == Qt::MouseButton::MiddleButton)
            //if (evnt->button() == Qt::MouseButton::RightButton)
            if (evnt->button() == Qt::MouseButton::LeftButton)
            {
                mousepressed = true;
                pre_click_px = QPoint(evnt->x(), evnt->y());
            }
        }


        // новая реализация
        int timeStamp = -QTime::currentTime().msecsTo(QTime(0, 0));
        _dblClickDelta = (timeStamp - _dblClickTimeStamp) < 300;
        _dblClickTimeStamp = timeStamp;

        // emit(mouseEvent(evnt));
        emit(mouseEventCoordinate(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        evnt->accept();
    }

    void MapControl::mouseReleaseEvent(QMouseEvent* evnt)
    {
        evnt->setAccepted(false);
        emit(mouseReleaseEvent(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        if (evnt->isAccepted()) return;

        mousepressed = false;

        if (mymousemode == MouseMode::None && (
            abs(pre_click_px.x() - evnt->x()) < DRAGGING_OR_PAINNING_START_DELTA
            && abs(pre_click_px.y() - evnt->y()) < DRAGGING_OR_PAINNING_START_DELTA
            ))
        {
            layermanager->mouseEvent(evnt);
        }


        // новая реализация
        if (_dblClickDelta) emit(mouseDoubleClickEvent(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        else emit(mouseClickEvent(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));


        emit(mouseEventCoordinate(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
    }

    void MapControl::mouseMoveEvent(QMouseEvent* evnt)
    {
        evnt->setAccepted(false);
        emit(mouseMoveEvent(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        if (!evnt->isAccepted())
        {

            if (evnt->buttons() != Qt::MouseButton::LeftButton) mousepressed = false;

            if (mymousemode == MouseMode::None && (
                abs(pre_click_px.x() - evnt->x()) > DRAGGING_OR_PAINNING_START_DELTA
                || abs(pre_click_px.y() - evnt->y()) > DRAGGING_OR_PAINNING_START_DELTA
                ))
            {
                mymousemode = Panning;
            }

            // реализация события при наведении/снятия наведния мыши на объект
            layermanager->mouseEvent(evnt);

            if (mousepressed && mymousemode == Panning)
            {
                QPoint offset = pre_click_px - QPoint(evnt->x(), evnt->y());

                layermanager->scrollView(offset);
                pre_click_px = QPoint(evnt->x(), evnt->y());
            }

            emit(mouseEventCoordinate(evnt, translateCoordinate(clickToWorldCoordinate(evnt->pos()))));
        }

        update();
    }

    void MapControl::keyPressEvent(QKeyEvent * event)
    {
        QWidget::keyPressEvent(event);

        emit(keyboardEvent(event));
    }

    void MapControl::keyReleaseEvent(QKeyEvent * event)
    {
        QWidget::keyReleaseEvent(event);

        emit(keyboardEvent(event));
    }

    void MapControl::wheelEvent ( QWheelEvent * event )
    {        
        QWidget::wheelEvent(event);

        emit(mouseWheelEvent(event));
    }
    QPointF MapControl::clickToWorldCoordinate(QPoint click)
    {
        QPointF out = clickToWorldCoordinateAbsolute(click);
        while (out.x() > 180)
            out.setX(out.x() - 360);
        while (out.x() < -180)
            out.setX(out.x() + 360);
        while (out.y() > 90)
            out.setY(out.y() - 180);
        while (out.y() < -90)
            out.setY(out.y() + 180);
        return out;
    }

    QPointF MapControl::mapToWorld(QPoint cursor)
    {
        return translateCoordinate(clickToWorldCoordinate(cursor));
    }

    QPointF MapControl::clickToWorldCoordinateAbsolute(QPoint click)
    {
        // click coordinate to image coordinate
        QPoint displayToImage = QPoint(click.x() - screen_middle.x() + layermanager->getMapmiddle_px().x(),
                                       click.y() - screen_middle.y() + layermanager->getMapmiddle_px().y());
        // image coordinate to world coordinate
        QPointF out = layermanager->layer()->mapadapter()->displayToCoordinate(displayToImage);

        return out;
    }

    void MapControl::updateRequest(QRect rect)
    {
        update(rect);
    }
    // slots
    void MapControl::zoomIn()
    {
        if (currentZoom() >= layermanager->layer()->mapadapter()->maxZoom()) 
            return;
        layermanager->zoomIn();
        update();

        emit(zoomChanged(currentZoom()));
    }

    void MapControl::zoomOut()
    {
        if (currentZoom() <= layermanager->layer()->mapadapter()->minZoom()) return;

        if (!isZoomOutAvailable()) return;

        layermanager->zoomOut();
        update();

        emit(zoomChanged(currentZoom()));
    }

    void MapControl::zoomIn(QPoint point)
    {
        QPointF pt = clickToWorldCoordinateAbsolute(point) + currentCoordinate();
        pt.rx() /= 2;
        pt.ry() /= 2;
        setUpdatesEnabled(false);
        setView(pt);
        zoomIn();
        setUpdatesEnabled(true);
    }

    void MapControl::zoomOut(QPoint point)
    {
        if (!isZoomOutAvailable()) return;

        QPointF pt = currentCoordinate() * 2 - clickToWorldCoordinateAbsolute(point);
        setUpdatesEnabled(false);
        setView(pt);
        zoomOut();
        setUpdatesEnabled(true);
    }


    bool MapControl::isZoomOutAvailable()
    {

        QPoint sm = screen_middle;
        int height = layermanager->layer()->mapadapter()->tilesize()*(pow(2, (double)(layermanager->currentZoom())));
        // если высота экрана будет больше предполагаемого размера карты, то не выполняем действие
        if ((height / 2) < (sm.y() * 2)) return false;

        return true;
    }

    void MapControl::setZoom(int zoomlevel)
    {
        if(zoomlevel==0) return;
        layermanager->setZoom(zoomlevel);
        update();

        emit(zoomChanged(currentZoom()));
    }
    int MapControl::currentZoom() const
    {
        return layermanager->currentZoom();
    }
    void MapControl::scrollLeft(int pixel)
    {
        layermanager->scrollView(QPoint(-pixel,0));
        update();
    }
    void MapControl::scrollRight(int pixel)
    {
        layermanager->scrollView(QPoint(pixel,0));
        update();
    }
    void MapControl::scrollUp(int pixel)
    {
        layermanager->scrollView(QPoint(0,-pixel));
        update();
    }
    void MapControl::scrollDown(int pixel)
    {
        layermanager->scrollView(QPoint(0,pixel));
        update();
    }
    void MapControl::scroll(const QPoint scroll)
    {
        layermanager->scrollView(scroll);
        update();
    }

    void MapControl::setView(const QPointF& coordinate) const
    {
        layermanager->setView(coordinate);
    }

    void MapControl::setView(const QList<QPointF> coordinates) const
    {
        layermanager->setView(coordinates);
    }

    void MapControl::setViewAndZoomIn(const QList<QPointF> coordinates)
    {
        layermanager->setViewAndZoomIn(coordinates);

        emit(zoomChanged(currentZoom()));
    }

    void MapControl::setView(const Point* point) const
    {
        layermanager->setView(point->position());
    }

    void MapControl::addLayer(Layer* layer)
    {
        layermanager->addLayer(layer);
    }

    void MapControl::setMouseMode(MouseMode mousemode)
    {
        mymousemode = mousemode;
        /* Poylov-MV */
        mousepressed = false;
    }
    MapControl::MouseMode MapControl::mouseMode()
    {
        return mymousemode;
    }

    void MapControl::stopFollowing(Geometry* geom)
    {
        disconnect(geom, &Geometry::positionChanged, this, 
            &MapControl::positionChanged);
    }

    void MapControl::showScale(bool show)
    {
        scaleVisible = show;
    }

    void MapControl::resize(const QSize newSize)
    {
        this->size_ = newSize;
        screen_middle = QPoint(newSize.width()/2, newSize.height()/2);

        int cz = currentZoom();
        layermanager->resize(newSize);

        if (cz != currentZoom())
        {
            emit(zoomChanged(currentZoom()));
        }
    }

    void MapControl::resizeEvent(QResizeEvent * event)
    {
        resize(event->size());
    }

    void MapControl::setCoordinateTranslator(CoordinateTranslator *translator)
    {
        cTranslator = translator;
    }

    QPointF MapControl::translateCoordinate(QPointF point)
    {
        if (cTranslator)
            return cTranslator->translate(point);
        
        return point;
    }

    QSize  MapControl::sizeHint() const
    {
        return QSize(50, 50);
    }

    int MapControl::computeScalePixelDistance(double scaleUnitDistance) const
    {
        // тестовая длина в пикселах для расчета коэффициента отношения пикселов к метрам
        const int testPixelDistance = 20;
        const double testKilometerDistance = pixelDistanceToKilometers(testPixelDistance);
        const double testUnitDistance = distanceConverter_->fromKilometers(testKilometerDistance);

        // коэффициет отношения пикселов к физическому расстоянию
        const double coefficient = static_cast<double>(testPixelDistance) / testUnitDistance;
        return static_cast<int>(coefficient * scaleUnitDistance);
    }

    double MapControl::pixelDistanceToKilometers(int pixelDistance) const
    {
        const auto mapAdapter = layermanager->layer()->mapadapter();
        const QPoint testDisplayPoint = mapAdapter->coordinateToDisplay(currentCoordinate());
        const QPoint testDeltaPoint = QPoint(pixelDistance / 2, 0);
        const QPoint leftTestDisplayPoint = testDisplayPoint - testDeltaPoint;
        const QPoint rightTestDisplayPoint = testDisplayPoint + testDeltaPoint;
        const QPointF leftTestQPoint = mapAdapter->displayToCoordinate(leftTestDisplayPoint);
        const QPointF rightTestQPoint = mapAdapter->displayToCoordinate(rightTestDisplayPoint);
        return PelengBase::lengthByPoints(leftTestQPoint, rightTestQPoint);
    }

    void MapControl::drawMapScaleRuler(QPainter& painter, int pixelDistance, const QString& meterDistanceText)
    {
        painter.setPen(Qt::black);

        QPoint leftBottomCorner(0, size_.height());
        QPoint cornerOffset(10, -20);

        QPoint lineStart = leftBottomCorner + cornerOffset;
        QPoint lineEnd = lineStart + QPoint(pixelDistance, 0);
        
        // отрисовка линий шкалы
        drawMapScaleRulerLines(painter, lineStart, lineEnd);
        // отрисовка текстовой метки

        // отрисовка текста шкалы
        drawMapScaleRulerLabel(painter, meterDistanceText, lineEnd);
    }

    void MapControl::drawMapScaleRulerLines(QPainter& painter, const QPoint& leftPoint, const QPoint& rightPoint)
    {
        const int dashHeight = 10;
        QPoint dashOffset(0, dashHeight / 2);

        painter.drawLine(leftPoint, rightPoint);                            // горизонтальная линия
        painter.drawLine(leftPoint  - dashOffset, leftPoint  + dashOffset); // левая вертикальная линия
        painter.drawLine(rightPoint - dashOffset, rightPoint + dashOffset); // правая вертикальная линия
   }

    void MapControl::drawMapScaleRulerLabel(QPainter& painter, const QString& distance, const QPoint& horizontalLineRightPoint)
    {
        const int offset = 5; // отступ текстовой метки от гориз. линии в пикселах (вниз и вправо)
        const QPoint textPoint = horizontalLineRightPoint + QPoint(offset, offset);

        // отрисовка
        painter.drawText(textPoint, distance);
    }

}
