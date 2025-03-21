#ifndef SCROLLZOOMMAPEXTENTION_H
#define SCROLLZOOMMAPEXTENTION_H

#include "persistentmapextention.h"

namespace qmapcontrol
{

/*!
*    Класс расширения для реализации приближения/удаления карты с помощью колесика мыши
*    @author Maxim Poylov
*/
class ScrollZoomMapExtention :
    public qmapcontrol::PersistentMapExtention
{
    Q_OBJECT

public:
    ScrollZoomMapExtention(MapControl *mapControl, QObject *parent = NULL);
    virtual ~ScrollZoomMapExtention();

private slots:
    void mouseWheelEvent_(QWheelEvent *e);
};
}

#endif