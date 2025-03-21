#include "lengthmeasuremapextention.h"

#include <QStaticText>

#define _USE_MATH_DEFINES
#include "math.h"

#include "geometries/pelengbase.h"

using namespace qmapcontrol;

MeasureGeometry::MeasureGeometry(QObject *parent)
: StaticGeometry("", parent)
{
    start_ = end_ = QPointF(0, 0);
}

MeasureGeometry::~MeasureGeometry()
{
}

void MeasureGeometry::draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
{
    QPen origPen = painter->pen();
    QBrush origBrush = painter->brush();

    QString text;
    QRectF rect;

    QPen backPen(Qt::white, 4);
    QPen frontPen(Qt::black, 2);
    QColor bc = Qt::white;
    bc.setAlpha(180);
    QBrush backBrush(bc);

    QPointF sp = mapadapter->coordinateToDisplay(start_);
    QPointF ep = mapadapter->coordinateToDisplay(end_);
    QPointF mp = (sp + ep) / 2;


    // отрисовка линейки в виде пеленга
    qreal azimuth, length;
    qmapcontrol::PelengBase::pelengParamsByPoints(start_, end_, azimuth, length);

    QPolygonF pel;
    qmapcontrol::PelengBase::calculate(start_, azimuth, length, pel);

    for (int i = 0; i < pel.count(); i++)
        pel[i] = mapadapter->coordinateToDisplay(pel.at(i));

    // две линии разной толшины для придания контрастности
    painter->setPen(backPen);
    painter->drawPolyline(pel);
    painter->setPen(frontPen);
    painter->drawPolyline(pel);

    painter->setPen(origPen);
    painter->setBrush(origBrush);

    // отрисовка текста с координатами начала и конца
    QStaticText st;
    st.setTextOption(QTextOption(Qt::AlignLeft | Qt::AlignBottom));

    st.setText("<table>" + CreateInfoText_(start_) + "</table>");
    rect = QRectF(sp, st.size());

    painter->setBrush(backBrush);
    painter->setPen(Qt::PenStyle::NoPen);
    painter->drawRoundedRect(rect, 5, 5);
    painter->setPen(frontPen);
    painter->drawStaticText(sp, st);

    st.setText("<table>" + CreateInfoText_(end_) +
        "<tr><td>" + QString("ДИСТ:</td><td><b>") + QString("%1").arg(mapadapter->distanceToText(length)) +
        QString("</b></td></tr><tr><td>АЗИМ:</td><td><b>") + 
        QString("%1").arg(azimuth < 0.0 ? (360 + azimuth) : azimuth) + "</b></td></tr></table>");
    rect = QRectF(ep, st.size());

    painter->setBrush(backBrush);
    painter->setPen(Qt::PenStyle::NoPen);
    painter->drawRoundedRect(rect, 5, 5);
    painter->setPen(frontPen);
    painter->drawStaticText(ep, st);

    painter->setPen(origPen);
    painter->setBrush(origBrush);
}

qreal MeasureGeometry::lengthByPoints_()
{
    return qmapcontrol::PelengBase::lengthByPoints(start_, end_);
}

QString MeasureGeometry::CreateInfoText_(QPointF coords)
{
    bool neg;
    QString lon, lat;

    neg = coords.x()<0;
    if (neg) coords.setX(-coords.x());

    lon = QString("%1").arg((int)coords.x(), 3, 'i', 0, QChar('0'))
        + QString::fromUtf8("\302\260")
        + QString("%1").arg(int((coords.x() - (int)coords.x()) * 60), 2, 'i', 0, QChar('0'))
        + tr("'");
    if (neg) lon += QString("з.д");
    else lon += QString("в.д");
    lon = "<tr><td>" + QString("ДОЛ: ") + "</td><td><b>" + lon + "</b></td></tr>";
    
    neg = coords.y()<0;
    if (neg) coords.setY(-coords.y());

    lat = QString("%1").arg((int)coords.y(), 3, 'i', 0, QChar('0'))
        + QString::fromUtf8("\302\260")
        + QString("%1").arg(int((coords.y() - (int)coords.y()) * 60), 2, 'i', 0, QChar('0'))
        + tr("'");
    if (neg) lat += QString("ю.ш.");
    else lat += QString("с.ш.");
    lat = "<tr><td>" + QString("ШИР: ") + "</td><td><b>" + lat + "</b></td></tr>";

    return lat + lon;
}

void MeasureGeometry::setStart(QPointF point)
{
    start_ = point;
    while (start_.x() >= 180) start_.rx() -= 360;
    while (start_.x() <= -180) start_.rx() += 360;
}

void MeasureGeometry::setEnd(QPointF point)
{
    end_ = point;   
}

LengthMeasureMapExtention::LengthMeasureMapExtention(qmapcontrol::MapControl *mapControl, qmapcontrol::Layer *layer, MeasureGeometry *geometry, QObject *parent)
: CheckableMapExtention(mapControl, parent), layer_(layer), measure_(geometry), pressed_(false)
{
    measure_->setParent(this);
}

LengthMeasureMapExtention::~LengthMeasureMapExtention()
{
    if (pressed_)
    {
        layer_->removeGeometry(measure_);
    }
}

void LengthMeasureMapExtention::start()
{
    connect(mapControl_, SIGNAL(mousePressEvent(QMouseEvent*, QPointF)), this, SLOT(mousePressEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseReleaseEvent(QMouseEvent*, QPointF)), this, SLOT(mouseReleaseEvent_(QMouseEvent*, QPointF)));
    connect(mapControl_, SIGNAL(mouseMoveEvent(QMouseEvent*, QPointF)), this, SLOT(mouseMoveEvent_(QMouseEvent*, QPointF)));

    setEnableStopOnKeyboard(true);

    CheckableMapExtention::start();
}

void LengthMeasureMapExtention::stop(MapExtention *sender)
{
    if (pressed_)
    {
        layer_->removeGeometry(measure_);
        pressed_ = false;
    }

    mapControl_->disconnect(this);
    
    CheckableMapExtention::stop(sender);
}

void LengthMeasureMapExtention::mouseMoveEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (pressed_)
    {
        measure_->setEnd(coordinate);
        e->accept();
    }
}

void LengthMeasureMapExtention::mousePressEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (!pressed_)
    {
        pressed_ = true;
        measure_->setStart(coordinate);
        measure_->setEnd(coordinate);

        layer_->addGeometry(measure_);
        e->accept();
    }
}

void LengthMeasureMapExtention::mouseReleaseEvent_(QMouseEvent* e, QPointF coordinate)
{
    if (e->button() != Qt::MouseButton::LeftButton) return;

    if (pressed_)
    {
        measure_->setEnd(coordinate);
        layer_->removeGeometry(measure_);
        pressed_ = false;
        e->accept();
    }
}
