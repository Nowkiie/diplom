#include "coordinatenetmapextention.h"

#include <QStaticText>
#include <QFont>

using namespace qmapcontrol;

CoordinateNetGeometry::CoordinateNetGeometry(QObject *parent)
: StaticGeometry("", parent)
{
}

CoordinateNetGeometry::~CoordinateNetGeometry()
{
}

void CoordinateNetGeometry::draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
{
    QPen origPen = painter->pen();
    QFont origFont = painter->font();
    QBrush origBrush = painter->brush();
    QColor color = Qt::gray;
    color.setAlpha(50);
    QPen pen = QPen(color);

    QRectF vp = viewport;

    QPoint tlo = mapadapter->coordinateToDisplay(vp.topLeft());
    QPoint bro = mapadapter->coordinateToDisplay(vp.bottomRight());

    if (vp.width() > 360)
    {
        vp.setLeft(-180);
        vp.setRight(180 - 1 / delta_.width());
    }

    QPoint tl = mapadapter->coordinateToDisplay(vp.topLeft());
    QPoint br = mapadapter->coordinateToDisplay(vp.bottomRight());

    qreal beg, end;

    QFont fnt("Serif");
    fnt.setPointSize(8);
    QFontMetrics fm(fnt);
    painter->setFont(fnt);

    painter->setBrush(Qt::white);

    // отрисовка вертикальных линий
    beg = int((vp.left() - (-180) + delta_.width() / 2.0) / delta_.width());
    end = int((vp.right() - (-180)) / delta_.width());
    painter->setPen(pen);
    for (qreal i = beg; i <= end; i++)
    {
        QPointF p(i * delta_.width() - 180, 0);
        QString crd = coordinateToString_(p.x());
        p = mapadapter->coordinateToDisplay(p);

        // линия 
        painter->drawLine(QPointF(p.x(), tl.y()), QPointF(p.x(), br.y()));

        // текст
        QSize s = fm.size(Qt::TextSingleLine, crd);
        p = QPointF(p.x() + 3, br.y() + 5);
        QRectF r = QRectF(p, s);
        r.adjust(-1, -1, 1, 1);

        painter->drawRoundedRect(r, 25, 25, Qt::RelativeSize);
        painter->setPen(Qt::black);
        painter->drawText(r, crd, QTextOption(Qt::AlignCenter));
        painter->setPen(pen);
    }

    // отрисовка горизонтальных линий
    beg = (int((vp.top() - (-90)) / delta_.height()) + 1);
    end = int((vp.bottom() - (-90)) / delta_.height());
    painter->setPen(pen);
    for (qreal i = beg; i <= end; i++)
    {
        QPointF p(0, i * delta_.height() - 90);
        QString crd = coordinateToString_(p.y());
        p = mapadapter->coordinateToDisplay(p);

        // линия
        painter->drawLine(QPointF(tl.x(), p.y()), QPointF(br.x(), p.y()));

        // текст
        QSize s = fm.size(Qt::TextSingleLine, crd);
        p = QPointF(tlo.x() + 5, p.y() - 3 - s.height());
        QPointF pp = p;
        pp.rx() -= offset.x();
        if ((pp.rx() > tl.x() && pp.rx() < br.x()) || viewport.width() < 360)
        {
            QRectF r = QRectF(p, s);
            r.adjust(-1, -1, 1, 1);

            painter->drawRoundedRect(r, 25, 25, Qt::RelativeSize);
            painter->setPen(Qt::black);
            painter->drawText(r, crd, QTextOption(Qt::AlignCenter));
            painter->setPen(pen);
        }
    }

    painter->setPen(origPen);
    painter->setFont(origFont);
    painter->setBrush(origBrush);
}

QString CoordinateNetGeometry::coordinateToString_(qreal value)
{
    QString result = "";
    bool neg = value < 0;
    if (neg) value = -value;

    result = QString("%1").arg((int)value)
        + QString::fromUtf8("\302\260")
        + QString("%1").arg(int((value - (int)value) * 60), 2, 'i', 0, QChar('0'))
        + tr("'");
    if (neg) result = "-" + result;

    return result;
}

void CoordinateNetGeometry::setDelta(QSizeF delta)
{
    delta_ = delta;
}

CoordinateNetMapExtention::CoordinateNetMapExtention(MapControl *mapControl, Layer *layer, CoordinateNetGeometry *geometry, QObject *parent)
: CheckableMapExtention(mapControl, parent), layer_(layer)
{
    basicSize_ = QSizeF(60, 30);
    basicSize_ *= 2;
    geometry_ = geometry;
    geometry_->setParent(this);
    geometry_->setDelta(basicSize_);

    connect(mapControl_, SIGNAL(zoomChanged(int)), this, SLOT(zoomChanged_(int)));

    zoomChanged_(mapControl_->currentZoom());
}

CoordinateNetMapExtention::~CoordinateNetMapExtention()
{
}

void CoordinateNetMapExtention::setChecked(bool checked)
{
    if (checked && !isChecked())
    {
        layer_->addGeometry(geometry_);
    }
    else if (!checked && isChecked())
    {
        layer_->removeGeometry(geometry_);
        mapControl_->update();
    }

    CheckableMapExtention::setChecked(checked);
}

void CoordinateNetMapExtention::start()
{
}

void CoordinateNetMapExtention::stop(MapExtention *sender)
{
}

void CoordinateNetMapExtention::zoomChanged_(int zoom)
{
    qreal mult = pow(2, zoom);
    geometry_->setDelta(QSizeF(basicSize_.width() / mult, basicSize_.height() / mult));
}
