#ifndef ZOOMOUTMAPEXTENTION_H
#define ZOOMOUTMAPEXTENTION_H

#include "persistentmapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для отдаления карты
*    @author Maxim Poylov
*/
class ZoomOutMapExtention :
    public PersistentMapExtention
{
    Q_OBJECT

public:
    ZoomOutMapExtention(MapControl *mapControl, QObject *parent = NULL);
    virtual ~ZoomOutMapExtention();

public slots:
    virtual void start();
};

}
#endif