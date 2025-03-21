#ifndef SHOWGEOMETRYMAPEXTENTION_H
#define SHOWGEOMETRYMAPEXTENTION_H

#include "geometryprocessormapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для позиционирования на конкретном объекте
*    @author Maxim Poylov
*/
class ShowGeometryMapExtention :
    public qmapcontrol::MapExtention
    , public qmapcontrol::GeometryProcessor
{
    Q_OBJECT

public:
    ShowGeometryMapExtention(MapControl *mapControl, QObject *parent = NULL);
    virtual ~ShowGeometryMapExtention();

public slots:
    virtual void start();
};

}
#endif