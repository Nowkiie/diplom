#include "localmapadapter.h"

#include <qstringlist.h>
#include <qfile.h>

namespace qmapcontrol
{
    LocalMapAdapter::LocalMapAdapter()
    : TileMapAdapter("local", 256, 0, 17)// Poylov-MV: zoom level borders
    {
    
    }

    LocalMapAdapter::~LocalMapAdapter()
    {
    }

}