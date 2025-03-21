#pragma once

#include <geometries/rpp.h>

namespace qmapcontrol
{

class RppLabeled : public Rpp
{
public:
    RppLabeled(QPixmap &pixmap, QPixmap &hiPixmap, QPointF position, qreal azimuth = 0, QString name = QString(), QPen pen = QPen(Qt::black));
    virtual ~RppLabeled();

    void setLabel(QString label);
    QString label();

    void setSelected(bool value);
    bool selected();

    void setHighlighted(bool value);
    bool highlighted();

    void showLabel(bool show);

    virtual void draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);
    virtual void setPen(QPen pen);

    void    setPixmap(const QPixmap &pixmap);
    void    setPixmaps(const QPixmap &pixmap, const QPixmap &hiPixmap);

private:
    QString    label_;
    bool    labelVisible_;
    bool    isSelected_;
    bool    isHighLighted_;
    QPixmap hiPixmap_;
};
}

