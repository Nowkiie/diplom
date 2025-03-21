#include "rpplabeled.h"

#include <QPixmap>

using namespace qmapcontrol;

RppLabeled::RppLabeled(QPixmap &pixmap, QPixmap &hiPixmap, QPointF position, qreal azimuth, QString n, QPen pen)
: Rpp(pixmap, position, azimuth, n, pen)
, label_(QString())
, labelVisible_(false)
, isSelected_(false)
, isHighLighted_(false)
, hiPixmap_(hiPixmap)
{

}

RppLabeled::~RppLabeled()
{
}

void    RppLabeled::setPixmap(const QPixmap &pixmap)
{
    if (mypixmap)
    {
        *mypixmap = pixmap;
        size = pixmap.size();
        displaysize = size;
    }
}

void    RppLabeled::setPixmaps(const QPixmap &pixmap, const QPixmap &hiPixmap)
{
    setPixmap(pixmap);
    hiPixmap_ = hiPixmap;
}

void RppLabeled::setLabel(QString label)
{
    label_ = label;
}

QString RppLabeled::label()
{
    return label_;
}

void RppLabeled::setSelected(bool value)
{
    isSelected_ = value;
}

bool RppLabeled::selected()
{
    return isSelected_;
}

void RppLabeled::setHighlighted(bool value)
{
    isHighLighted_ = value;
}

bool RppLabeled::highlighted()
{
    return isHighLighted_;
}

void RppLabeled::showLabel(bool show)
{
    labelVisible_ = show;
}

void RppLabeled::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
{
    if (!visible) return;

    QPointF p = QPointF(X, Y);
    p = mapadapter->coordinateToDisplay(p);
    QPointF alp = alignedPoint(p.toPoint());

    painter->save();

    if (isHighLighted_)
    {
        QSize size = mypixmap->size();
        QSize newSize = hiPixmap_.size();
        QSize diffSize = (newSize - size) / 2;

        painter->drawPixmap(alp - QPoint(diffSize.width(), diffSize.height()), hiPixmap_);
    }
    else
    {
        painter->drawPixmap(alp, *mypixmap);
    }

    if (isSelected_)
    {
        QPen pen(Qt::red);
        pen.setStyle(Qt::PenStyle::DashLine);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRect(alp.toPoint(), mypixmap->size()));
    }

    if (!(!visible || !labelVisible_ || label_.isEmpty()))
    {
        // отображение справа
        QFontMetrics fm = painter->fontMetrics();
        int height = fm.height();
        int width = fm.width(label_);
        QPoint lp = p.toPoint() + QPoint(mypixmap->width() / 2, 0);

        QColor backColor(Qt::white);
        backColor.setAlpha(150);
        painter->setPen(Qt::NoPen);
        painter->setBrush(backColor);
        QRect r(lp - QPoint(0, height / 2), QSize(width, height));
        painter->drawRect(r);

        painter->setPen(mypen);
        painter->drawText(r, label_, QTextOption(Qt::AlignCenter));
    }

    painter->restore();
}

void RppLabeled::setPen(QPen pen)
{
    Rpp::setPen(pen);

    if (!mypixmap || mypixmap->isNull())
    {
        // файл с изображением объекта не найден - рисуем просто прямоугольник со штриховкой
        QRect rect(0, 0, 32, 32);
        size = rect.size();
        delete mypixmap;
        mypixmap = new QPixmap(rect.width() + 1, rect.height() + 1);
        mypixmap->fill(Qt::transparent);
        QPainter painter(mypixmap);
        rect.adjust(2, 2, -2, -2);
        painter.setBrush(Qt::BrushStyle::DiagCrossPattern);
        QPen pen(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(rect);
    }
}
