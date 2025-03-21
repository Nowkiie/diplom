#ifndef STATICGEOMETRY_H
#define STATICGEOMETRY_H

#include "geometry.h"

namespace qmapcontrol
{
    /*!
    *    Базовый класс для рисования неизменяющихся/статичных/не отвечающих на события объектов
    *    @author Maxim Poylov
    */
    class StaticGeometry :
        public Geometry
    {
        Q_OBJECT

    public:
        StaticGeometry(QString name = QString(), QObject *parent = NULL);
        virtual ~StaticGeometry();

        virtual QRectF boundingBox();
        virtual bool Touches(qmapcontrol::Point* geom, const qmapcontrol::MapAdapter* mapadapter);
        virtual QPolygonF points();

        void accept(GeometryVisitor *visitor);
    };

}
#endif