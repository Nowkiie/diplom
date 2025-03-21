#include "rectangleselectionmapextention.h"

namespace qmapcontrol
{
// --------------------------------------------------------------------------------------------------------------------------------
// class RectangleSelectionGeometry
// --------------------------------------------------------------------------------------------------------------------------------

RectangleSelectionGeometry::RectangleSelectionGeometry(QObject* parent)
{
    start_ = end_ = QPointF(0, 0);
}

RectangleSelectionGeometry::~RectangleSelectionGeometry() {}

void RectangleSelectionGeometry::draw(QPainter* painter,
                                      const qmapcontrol::MapAdapter* mapadapter,
                                      const QRectF& viewport,
                                      const QPoint offset)
{
    QPen origPen = painter->pen();
    QBrush origBrush = painter->brush();

    QBrush selBrush = QBrush(QColor(0, 100, 255, 100));
    QPen selPen = QPen(QColor(0, 100, 255), 1);
    painter->setBrush(selBrush);
    painter->setPen(selPen);

    QPointF fromS = mapadapter->coordinateToDisplay(start_);
    QPointF toS = mapadapter->coordinateToDisplay(end_);

    painter->drawRect(QRectF(fromS, toS));

    painter->setPen(origPen);
    painter->setBrush(origBrush);
}

void RectangleSelectionGeometry::setStart(QPointF point)
{
    start_ = point;
}

void RectangleSelectionGeometry::setEnd(QPointF point)
{
    end_ = point;
}

QPointF RectangleSelectionGeometry::start()
{
    return start_;
}

QPointF RectangleSelectionGeometry::end()
{
    return end_;
}

// --------------------------------------------------------------------------------------------------------------------------------
// class RectangleSelectionMapExtention
// --------------------------------------------------------------------------------------------------------------------------------

RectangleSelectionMapExtention::RectangleSelectionMapExtention(
    MapControl* mapControl, qmapcontrol::Layer* layer,
    RectangleSelectionGeometry* geometry, QObject* parent)
    : RectangleSelectionMapExtention(mapControl, layer, geometry,
                                     Qt::LeftButton, parent)
{
    geometry_->setParent(this);
}

RectangleSelectionMapExtention::RectangleSelectionMapExtention(
    MapControl* mapControl, qmapcontrol::Layer* layer,
    RectangleSelectionGeometry* geometry, Qt::MouseButton actionButton,
    QObject* parent)
    : RectangleSelectionMapExtention(mapControl, layer, geometry, actionButton,
                                     Qt::NoModifier, Qt::ShiftModifier, parent)
{
    geometry_->setParent(this);
}

RectangleSelectionMapExtention::RectangleSelectionMapExtention(
    MapControl* mapControl, qmapcontrol::Layer* layer,
    RectangleSelectionGeometry* geometry, Qt::MouseButton actionButton,
    Qt::KeyboardModifier actionAdditionalKey,
    Qt::KeyboardModifier selectionAddModifer, QObject* parent)
    : SelectionMapExtention(mapControl, parent)
    , layer_(layer)
    , geometry_(geometry)
    , pressed_(false)
    , actionButton_(actionButton)
    , actionAdditionalKey_(actionAdditionalKey)
    , selectionAddModifer_(selectionAddModifer)
{
    geometry_->setParent(this);
}

RectangleSelectionMapExtention::~RectangleSelectionMapExtention() {}

void RectangleSelectionMapExtention::start()
{
    pressed_ = false;
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this,
            SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)), Qt::DirectConnection);
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this,
            SLOT(mousePressEvent_(QMouseEvent*, QPointF)),
            Qt::DirectConnection);
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this,
            SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)),
            Qt::DirectConnection);

    SelectionMapExtention::start();
}

void RectangleSelectionMapExtention::stop(MapExtention* sender)
{
    pressed_ = false;
    layer_->removeGeometry(geometry_);
    mapControl_->disconnect(this);

    SelectionMapExtention::stop(sender);
}

void RectangleSelectionMapExtention::process(QList<Geometry*> geometries)
{
    if (geometries.count() == 0)
        return;

    // для каждого объекта проверяем пересечение ограничивающего прямоугольника с выделением
    QRectF selection(geometry_->start(), geometry_->end());
    selection = selection.normalized();
    QList<Geometry*> result;
    foreach (Geometry* g, geometries)
    {
        // сдвигаем ограничивающий прямоугольник в сторону выделения (коррекция для смежных карт)
        QRectF bb = g->boundingBox();
        while (bb.left() > selection.right()) bb.moveLeft(bb.left() - 360.0);
        while (bb.right() < selection.left()) bb.moveLeft(bb.left() + 360.0);

        if (selection.intersects(bb))
        {
            result.append(g);
        }
    }

    if (result.count() > 0)
    {
        emit(selected(result, getModifiers()));
    }
}

void RectangleSelectionMapExtention::mouseMoveEvent_(QMouseEvent* evnt,
                                                     QPointF coordinate)
{
    if (pressed_)
    {
        geometry_->setEnd(coordinate);

        if ((evnt->buttons() != actionButton_)
            || ((evnt->modifiers() & actionAdditionalKey_)
                != actionAdditionalKey_))
        {
            stop(this);
            return;
        }
        evnt->accept();
    }
}

void RectangleSelectionMapExtention::mousePressEvent_(QMouseEvent* evnt,
                                                      QPointF coordinate)
{
    auto mod = evnt->modifiers();
    if ((evnt->button() != actionButton_)
        || ((evnt->modifiers() & actionAdditionalKey_) != actionAdditionalKey_))
            return;

    geometry_->setStart(coordinate);
    geometry_->setEnd(coordinate);

    if (!pressed_)
    {
        layer_->addGeometry(geometry_);
    }
    pressed_ = true;

    evnt->accept();
}

void RectangleSelectionMapExtention::mouseReleaseEvent_(QMouseEvent* evnt,
                                                        QPointF coordinate)
{
    if ((evnt->button() != actionButton_)
        || ((evnt->modifiers() & actionAdditionalKey_) != actionAdditionalKey_))
        return;

    geometry_->setEnd(coordinate);

    if ((evnt->modifiers() & selectionAddModifer_) == selectionAddModifer_)
        setModifiers(SM_APPEND);
    else
        setModifiers(SM_INIT);

    process(geos_->geometries(processorID()));
    layer_->removeGeometry(geometry_);
    pressed_ = false;

    evnt->accept();
}

}  // namespace qmapcontrol
