#ifndef ZOOMINMAPEXTENTION_H
#define ZOOMINMAPEXTENTION_H

#include "persistentmapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для приближения карты
*    @author Maxim Poylov
*/
class ZoomInMapExtention : public PersistentMapExtention
{
    Q_OBJECT

public:
    ZoomInMapExtention(MapControl *mapControl, QObject *parent = NULL);
    ~ZoomInMapExtention();

public slots:
    virtual void start();
};

}
#endif