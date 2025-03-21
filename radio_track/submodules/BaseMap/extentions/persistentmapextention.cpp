#include "persistentmapextention.h"

namespace qmapcontrol
{
    PersistentMapExtention::PersistentMapExtention(MapControl *mapControl, QObject *parent)
        : MapExtention(mapControl, parent)
    {
    }

    PersistentMapExtention::~PersistentMapExtention()
    {
    }

    void PersistentMapExtention::start()
    {
        // события не рассылаются
    }

    void PersistentMapExtention::stop(MapExtention *sender)
    {
        // события не рассылаются
    }
}
