#ifndef LOCALMAPADAPTER_H
#define LOCALMAPADAPTER_H

#include "tilemapadapter.h"

namespace qmapcontrol
{

    /*!
    *    Класс загрузчик изображений карт с диска
    *    @author Maxim Poylov
    */
    class LocalMapAdapter : public TileMapAdapter
    {
        Q_OBJECT
                public:
        //! constructor
        /*!
         * This construct a Local Adapter
         */
        LocalMapAdapter();
        virtual ~LocalMapAdapter();

    };
    
}
#endif