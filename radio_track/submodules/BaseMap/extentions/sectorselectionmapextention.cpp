#include "sectorselectionmapextention.h"
#include "geometries/pelengbase.h"

#define _USE_MATH_DEFINES
#include "math.h"

namespace qmapcontrol
{
    // --------------------------------------------------------------------------------------------------------------------------------
    // class SectorSelectionGeometry
    // --------------------------------------------------------------------------------------------------------------------------------

    SectorSelectionGeometry::SectorSelectionGeometry(QObject *parent)
    {
        points_.clear();
    }

    SectorSelectionGeometry::~SectorSelectionGeometry()
    {
    }

    void SectorSelectionGeometry::draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (points_.count() < 2) return;

        QPen origPen = painter->pen();
        QBrush origBrush = painter->brush();

        QBrush selBrush = QBrush(QColor(0, 100, 255, 100));
        QPen selPen = QPen(QColor(0, 100, 255), 1);
        painter->setBrush(selBrush);
        painter->setPen(selPen);

        QPointF from = points_.at(0);
        QPointF to = points_.at(1);

        qreal sangle, length;
        qreal eangle;
        PelengBase::pelengParamsByPoints(from, to, sangle, length);
        eangle = sangle;
        if (points_.count() > 2)
            PelengBase::pelengParamsByPoints(from, points_.at(2), eangle, length);

        QPolygonF p1, p2;
        PelengBase::calculate(from, sangle, length, p1);
        PelengBase::calculate(from, eangle, length, p2);

        for (int i = 0; i < p1.count(); i++)
            p1[i] = mapadapter->coordinateToDisplay(p1.at(i));
        for (int i = p2.count() - 1; i >= 0; i--)
            p1.append(mapadapter->coordinateToDisplay(p2.at(i)));

        painter->drawPolygon(p1);

        painter->setPen(origPen);
        painter->setBrush(origBrush);
    }

    void SectorSelectionGeometry::setPoints(QList<QPointF> points)
    {
        points_ = points;
    }

    QList<QPointF> SectorSelectionGeometry::getPoints()
    {
        return points_;
    }


    // --------------------------------------------------------------------------------------------------------------------------------
    // class SectorSelectionMapExtention
    // --------------------------------------------------------------------------------------------------------------------------------

    SectorSelectionMapExtention::SectorSelectionMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, SectorSelectionGeometry *geometry, QObject *parent)
        : SelectionMapExtention(mapControl, parent), layer_(layer), geometry_(geometry)
    {
        geometry_->setParent(this);
        pressed_ = false;
    }

    SectorSelectionMapExtention::~SectorSelectionMapExtention()
    {
    }

    void SectorSelectionMapExtention::start()
    {
        pressed_ = false;
        geometry_->setPoints(QList<QPointF>());
        layer_->removeGeometry(geometry_);
        mapControl_->disconnect(this);

        connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));
        connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
        connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));

        SelectionMapExtention::start();
    }

    void SectorSelectionMapExtention::stop(MapExtention *sender)
    {
        pressed_ = false;
        geometry_->setPoints(QList<QPointF>());
        layer_->removeGeometry(geometry_);
        mapControl_->disconnect(this);

        SelectionMapExtention::stop(sender);
    }

    void SectorSelectionMapExtention::process(QList<Geometry*> geometries)
    {
        if (geometries.count() == 0) return;

        // для каждого объекта проверяем пересечение ограничивающего прямоугольника с выделением
        QList<Geometry*> result;

        // преобразуем координаты в размеры и направление эллипса
        QList<QPointF> points = geometry_->getPoints();

        QPointF from, to, fromS, toS;
        from = points.at(0);
        to = points.at(1);

        // проверяем содержатся ли точки дуги сектора внутри геометрии
        qreal sangle, length;
        qreal eangle;
        PelengBase::pelengParamsByPoints(from, to, sangle, length);
        PelengBase::pelengParamsByPoints(from, points.at(2), eangle, length);

        QPolygonF p1, p2;
        PelengBase::calculate(from, sangle, length, p1);
        PelengBase::calculate(from, eangle, length, p2);

        // объединяем в сектор
        QVectorIterator<QPointF> it(p2);
        it.toBack();
        while (it.hasPrevious())
        {
            p1.append(it.previous());
        }

        QRectF br = p1.boundingRect();

        foreach(Geometry *g, geometries)
        {
            bool selected = false;
            QPolygonF points = g->points();
            if (points.count() > 0)
            {
                for (int i = 0; i < points.count(); i++)
                {
                    QPointF c = points.at(i);

                    while (c.x() < br.left()) c.rx() += 360;
                    while (c.x() > br.right()) c.rx() -= 360;

                    if (p1.containsPoint(c, Qt::OddEvenFill))
                    {
                        selected = true;
                        break;
                    }
                }
                if (selected)
                    result.append(g);
            }
        }

        if (result.count() > 0)
        {
            emit(selected(result, getModifiers()));
        }
    }

    void SectorSelectionMapExtention::mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate)
    {
        if (!pressed_) return;

        QList<QPointF> points = geometry_->getPoints();
        int count = points.count();
        if (count > 0)
        {
            points.replace(count - 1, coordinate);
            geometry_->setPoints(points);
        }

        evnt->accept();
    }

    void SectorSelectionMapExtention::mousePressEvent_(QMouseEvent* evnt, QPointF coordinate)
    {
        if (evnt->button() != Qt::MouseButton::LeftButton) return;

        pressed_ = true;
        QList<QPointF> points = geometry_->getPoints();
        if (points.count() == 0)
        {
            layer_->addGeometry(geometry_);
            points.append(coordinate);
        }
        points.append(coordinate);

        if (points.count() > 3)
        {
            if ((evnt->modifiers() & Qt::KeyboardModifier::ShiftModifier) == Qt::KeyboardModifier::ShiftModifier) setModifiers(SM_APPEND);
            else setModifiers(SM_INIT);

            process(geos_->geometries(processorID()));

            pressed_ = false;
            geometry_->setPoints(QList<QPointF>());
            layer_->removeGeometry(geometry_);
        }
        else
            geometry_->setPoints(points);

        evnt->accept();
    }

    void SectorSelectionMapExtention::mouseReleaseEvent_(QMouseEvent* evnt, QPointF coordinate)
    {
        if (evnt->button() != Qt::MouseButton::LeftButton) return;

        if (!pressed_) return;

        QList<QPointF> points = geometry_->getPoints();
        points.append(coordinate);
        geometry_->setPoints(points);

        evnt->accept();
    }

}
