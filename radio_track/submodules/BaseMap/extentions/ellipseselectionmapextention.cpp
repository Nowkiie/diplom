#include "ellipseselectionmapextention.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <QPainterPath>

namespace qmapcontrol
{

    // --------------------------------------------------------------------------------------------------------------------------------
    // class EllipseSelectionGeometry
    // --------------------------------------------------------------------------------------------------------------------------------

    EllipseSelectionGeometry::EllipseSelectionGeometry(QObject *parent)
    {
        points_.clear();
    }

    EllipseSelectionGeometry::~EllipseSelectionGeometry()
    {
    }

    void EllipseSelectionGeometry::draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
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
        QPointF fromS = mapadapter->coordinateToDisplay(from);
        QPointF toS = mapadapter->coordinateToDisplay(to);


        qreal w1, h1, w2, h2, ew, eh;
        w1 = (toS.x() - fromS.x());
        h1 = (toS.y() - fromS.y());
        qreal angle = acos(w1 / sqrt(w1 * w1 + h1 * h1)) * 180 / M_PI;
        if (h1 > 0) angle = 360 - angle;

        w1 = (to.x() - from.x());
        h1 = (to.y() - from.y());
        ew = sqrt(w1 * w1 + h1 * h1);

        if (points_.count() != 2)
        {
            to = points_.at(2);
            w2 = (to.x() - from.x());
            h2 = (to.y() - from.y());
            eh = sqrt(w2 * w2 + h2 * h2);
        }
        else
        {
            eh = ew / 2;
        }

        // отрисовка с преобразованием из мировых координат в экранные
        QPainterPath path;
        QPointF prev;
        qreal cosA = cos(angle * M_PI / 180.0);
        qreal sinA = sin(angle * M_PI / 180.0);
        for (int i = 0; i < 360; i++)
        {
            qreal x = cos(i * M_PI / 180.0) * ew;
            qreal y = sin(i * M_PI / 180.0) * eh;
            // поворот
            qreal x1 = x * cosA - y * sinA;
            qreal y1 = x * sinA + y * cosA;
            // перенос в координаты
            x1 += from.x();
            y1 += from.y();

            /* Poylov-MV ограничения для предотвращения выхода за карту */
            if (y1 > 89) y1 = 89;
            else if (y1 < -89) y1 = -89;
            QPoint dsp = mapadapter->coordinateToDisplay(QPointF(x1, y1));

            if (i != 0)
            {
                path.lineTo(dsp);
            }
            else
            {
                path.moveTo(dsp);
            }

            prev = dsp;
        }
        path.closeSubpath();
        painter->drawPath(path);


        painter->setPen(origPen);
        painter->setBrush(origBrush);
    }

    void EllipseSelectionGeometry::setPoints(QList<QPointF> points)
    {
        points_ = points;
    }

    QList<QPointF> EllipseSelectionGeometry::getPoints()
    {
        return points_;
    }


    // --------------------------------------------------------------------------------------------------------------------------------
    // class EllipseSelectionMapExtention
    // --------------------------------------------------------------------------------------------------------------------------------

    EllipseSelectionMapExtention::EllipseSelectionMapExtention(MapControl *mapControl, qmapcontrol::Layer *layer, EllipseSelectionGeometry *geometry, QObject *parent)
        : SelectionMapExtention(mapControl, parent), layer_(layer), geometry_(geometry)
    {
        geometry_->setParent(this);
        pressed_ = false;
    }

    EllipseSelectionMapExtention::~EllipseSelectionMapExtention()
    {
    }

    void EllipseSelectionMapExtention::start()
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

    void EllipseSelectionMapExtention::stop(MapExtention *sender)
    {
        pressed_ = false;
        geometry_->setPoints(QList<QPointF>());
        layer_->removeGeometry(geometry_);
        mapControl_->disconnect(this);

        SelectionMapExtention::stop(sender);
    }

    void EllipseSelectionMapExtention::process(QList<Geometry*> geometries)
    {
        if (geometries.count() == 0) return;

        // для каждого объекта проверяем пересечение ограничивающего прямоугольника с выделением
        QList<Geometry*> result;

        // преобразуем координаты в размеры и направление эллипса
        QList<QPointF> points = geometry_->getPoints();

        QPointF from, to, fromS, toS;
        from = points.at(0);
        to = points.at(1);

        fromS = layer_->mapadapter()->coordinateToDisplay(from);
        toS = layer_->mapadapter()->coordinateToDisplay(to);

        qreal w1, h1, w2, h2, ew, eh;

        w1 = (toS.x() - fromS.x());
        h1 = (toS.y() - fromS.y());
        qreal angle = acos(w1 / sqrt(w1 * w1 + h1 * h1)) * 180 / M_PI;
        if (h1 > 0) angle = 360 - angle;

        w1 = (to.x() - from.x());
        h1 = (to.y() - from.y());
        ew = sqrt(w1 * w1 + h1 * h1);

        to = points.at(2);
        w2 = (to.x() - from.x());
        h2 = (to.y() - from.y());
        eh = sqrt(w2 * w2 + h2 * h2);

        // определяем выделенные
        qreal cosA = cos(angle * M_PI / 180.0);
        qreal sinA = sin(angle * M_PI / 180.0);

        foreach(Geometry *g, geometries)
        {
            QPolygonF points = g->points();
            bool selected = false;
            if (points.count() > 0)
            {
                for (int i = 0; i < points.count(); i++)
                {
                    QPointF c = points.at(i);

                    // проверяем можно ли повернуть точку на 360 градусов, чтобы она стала ближе к центру элипса
                    // это нужно для того, чтобы быть уверенным, что эллипс и точка находятся на одной карте, а не на смежных
                    qreal origdx = qAbs(c.x() - from.x());
                    if (c.x() < from.x() && qAbs(c.x() - from.x() + 360) < origdx) c.rx() += 360;
                    if (c.x() > from.x() && qAbs(c.x() - from.x() - 360) < origdx) c.rx() -= 360;

                    QPointF pnt = c;
                    pnt = QPointF(pnt.x() - from.x(), pnt.y() - from.y());

                    pnt = QPointF(
                        pnt.x() * cosA + pnt.y() * sinA,
                        -pnt.x() * sinA + pnt.y() * cosA);

                    qreal dx = pnt.x() / ew;
                    qreal dy = pnt.y() / eh;

                    if ((dx * dx + dy * dy) <= 1)
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

    void EllipseSelectionMapExtention::mouseMoveEvent_(QMouseEvent* evnt, QPointF coordinate)
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

    void EllipseSelectionMapExtention::mousePressEvent_(QMouseEvent* evnt, QPointF coordinate)
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

        if (points.count() > 3 && pressed_)
        {
            if ((evnt->modifiers() & Qt::KeyboardModifier::ShiftModifier) == Qt::KeyboardModifier::ShiftModifier) setModifiers(SM_APPEND);
            else setModifiers(SM_INIT);

            //emit(needGeometries(this));
            process(geos_->geometries(processorID()));

            geometry_->setPoints(QList<QPointF>());
            layer_->removeGeometry(geometry_);
            pressed_ = false;
        }
        else
            geometry_->setPoints(points);

        evnt->accept();
    }

    void EllipseSelectionMapExtention::mouseReleaseEvent_(QMouseEvent* evnt, QPointF coordinate)
    {
        if (evnt->button() != Qt::MouseButton::LeftButton) return;

        if (!pressed_) return;

        QList<QPointF> points = geometry_->getPoints();
        points.append(coordinate);
        geometry_->setPoints(points);

        evnt->accept();
    }

}
