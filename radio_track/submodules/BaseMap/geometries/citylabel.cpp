#include "citylabel.h"

#include <QStaticText>
#include <QFont>
#include <QFileInfo>

//------------------------------------------------------------------------------
// CityLabelGeometry
//------------------------------------------------------------------------------

using namespace qmapcontrol;


QFont *CityLabelGeometry::font_ = NULL;

CityLabelGeometry::CityLabelGeometry(QObject *parent)
: StaticGeometry("", parent)
{
    if (!font_)
    {
        font_ = new QFont("Serif");
        font_->setPointSize(8);
    }
}

CityLabelGeometry::~CityLabelGeometry()
{
    if (font_)
    {
        delete font_;
        font_ = NULL;
    }
}

void CityLabelGeometry::draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
{
    if (!pixmap_.isNull() && visible)
        painter->drawPixmap(mapadapter->coordinateToDisplay(pos_), pixmap_);
}

void CityLabelGeometry::setLabel(QString label)
{
    label_ = label;

    recalcLabel_();
}

void CityLabelGeometry::setPosition(QPointF pos)
{
    pos_ = pos;
}

void CityLabelGeometry::recalcLabel_()
{
    QFontMetrics fm(*font_);

    QSize s = fm.size(Qt::TextSingleLine, label_);

    s += QSize(2, 2);

    pixmap_ = QPixmap(s.width() + 1, s.height() + 1);
    pixmap_.fill(Qt::transparent);
    QPainter painter(&pixmap_);

    painter.setFont(*font_);
    painter.setBrush(Qt::white);

    QRectF r(QPointF(), s);
    painter.drawRoundedRect(r, 25, 25, Qt::RelativeSize);
    painter.drawText(r, label_, QTextOption(Qt::AlignCenter));
}
