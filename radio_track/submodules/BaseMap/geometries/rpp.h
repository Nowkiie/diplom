#ifndef RPP_H
#define RPP_H

#include "point.h"

class QDomNode;

namespace qmapcontrol
{
    /*!
    *    Класс для рисования объекта РПП в виде картинки с указанием угла поворота
    *    @author Maxim Poylov
    */
    class Rpp : public Point
    {
    public:
        //!
        /*!
         *
         * @param x longitude
         * @param y latitude
         * @param name name of the circle point
         * @param alignment alignment (Middle or TopLeft)
         * @param pen QPen for drawing
         */
        Rpp(QString &fileName, QPointF position, qreal azimuth = 0, QString name = QString(), QPen pen = QPen(Qt::black));
        Rpp(QPixmap &pixmap, QPointF position, qreal azimuth = 0, QString name = QString(), QPen pen = QPen(Qt::black));

        virtual ~Rpp();

        //! sets the QPen which is used for drawing the circle
        /*!
         * A QPen can be used to modify the look of the drawn circle
         * @param pen the QPen which should be used for drawing
         * @see http://doc.trolltech.com/4.3/qpen.html
         */
        virtual void setPen(QPen pen);

        virtual void draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset);

        void setAzimuth(const qreal &azimuth);
        qreal azimuth();

        void accept(GeometryVisitor *visitor);

        //! reloads current pixmap from fileName (constructor) using current Pen and Azimuth
        void    updatePixmap();

    private:
        QString    _fileName;
        qreal    _azimuth;

        void    replaceColorAttribute_(QDomNode &node, QColor color);

    };
}
#endif //RPP_H
