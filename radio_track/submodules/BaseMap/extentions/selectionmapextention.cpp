#include "selectionmapextention.h"

namespace qmapcontrol
{

    SelectionMapExtention::SelectionMapExtention(MapControl *mapControl, QObject *parent)
        : CheckableMapExtention(mapControl, parent), modifier_(SM_INIT)
    {
    }

    SelectionMapExtention::~SelectionMapExtention()
    {
    }

    void SelectionMapExtention::start()
    {
        setEnableStopOnKeyboard(true);

        CheckableMapExtention::start();
    }

    void SelectionMapExtention::stop(MapExtention *sender)
    {
        mapControl_->update();

        CheckableMapExtention::stop(sender);
    }

    void SelectionMapExtention::setModifiers(SelectionModifiers modifiers)
    {
        modifier_ = modifiers;
    }

    SelectionMapExtention::SelectionModifiers SelectionMapExtention::getModifiers()
    {
        return modifier_;
    }

}
