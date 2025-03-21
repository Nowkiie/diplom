#ifndef SHOWALLMAPEXTENTION_H
#define SHOWALLMAPEXTENTION_H

#include "geometryprocessormapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для отображения всех объектов на карте
*    @author Maxim Poylov
*/
class ShowAllMapExtention :
    public qmapcontrol::MapExtention
    , public qmapcontrol::GeometryProcessor
{
    Q_OBJECT

public:
    ShowAllMapExtention(MapControl *mapControl, QObject *parent = NULL);
    virtual ~ShowAllMapExtention();

public slots:
    virtual void start();
};

}
#endif