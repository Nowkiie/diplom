#include "geometrycreatormapextention.h"

namespace qmapcontrol
{

    GeometryCreatorMapExtention::GeometryCreatorMapExtention(MapControl *mapControl, Layer *layer, QObject *parent)
        : CheckableMapExtention(mapControl, parent), layer_(layer), key_(Qt::NoModifier)
    {
    }

    GeometryCreatorMapExtention::~GeometryCreatorMapExtention()
    {
    }

    void GeometryCreatorMapExtention::setKeyboardModifier(Qt::KeyboardModifier key)
    {
        key_ = key;
        if (key_ == Qt::NoModifier)
            setEnableStopOnKeyboard(true);
        else
            setEnableStopOnKeyboard(false);
    };

    Qt::KeyboardModifier GeometryCreatorMapExtention::keyboardModifier()  const
    { 
        return key_; 
    };

    Layer *GeometryCreatorMapExtention::getLayer()
    {
        return layer_;
    }

    void GeometryCreatorMapExtention::start()
    {
        CheckableMapExtention::start();
    }

    void GeometryCreatorMapExtention::stop(MapExtention *sender)
    {
        CheckableMapExtention::stop(sender);
    }

}
