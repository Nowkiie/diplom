#ifndef PERSISTENTMAPEXTENTION_H
#define PERSISTENTMAPEXTENTION_H

#include "core/mapcontrol.h"
#include "mapextention.h"

namespace qmapcontrol
{
    /*!
    *    Базовый класс для реализации "расширений", которые не требуют событий
    *        start() и stop(), а работают по-умолчанию с момента создания
    *    @author Maxim Poylov
    */
    class PersistentMapExtention
         : public MapExtention
    {
        Q_OBJECT

    public:
        PersistentMapExtention(MapControl *mapControl, QObject *parent = NULL);
        virtual ~PersistentMapExtention();

    public slots:
        virtual void start();
        virtual void stop(MapExtention *sender);
    };
}

#endif
