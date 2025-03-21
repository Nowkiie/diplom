#include "staticgeometry.h"

namespace qmapcontrol
{

    StaticGeometry::StaticGeometry(QString name, QObject *parent)
        : Geometry(name)
    {
        setParent(parent);
    }

    StaticGeometry::~StaticGeometry()
    {
    }

    QRectF StaticGeometry::boundingBox()
    {
        return QRect();
    }

    bool StaticGeometry::Touches(qmapcontrol::Point* geom, const qmapcontrol::MapAdapter* mapadapter)
    {
        return false;
    }

    QPolygonF StaticGeometry::points()
    {
        return QPolygonF();
    }

    void StaticGeometry::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

}
