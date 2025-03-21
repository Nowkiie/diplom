#ifndef CITYLABELS_H
#define CITYLABELS_H

#include "geometries/staticgeometry.h"

namespace qmapcontrol
{
/*!
*    Класс по-умолчанию для рисования текста на карте
*    @author Maxim Poylov
*/
class CityLabelGeometry : public qmapcontrol::StaticGeometry
{
    Q_OBJECT
public:
    CityLabelGeometry(QObject *parent = NULL);
    virtual ~CityLabelGeometry();

    virtual void draw(QPainter* painter, const qmapcontrol::MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

    void setLabel(QString label);
    void setPosition(QPointF pos);

protected:
    QString label_;
    QPointF pos_;
    QPixmap pixmap_;

    static QFont *font_;

    void recalcLabel_();
};
}
#endif