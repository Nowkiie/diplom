#include "checkablemapextention.h"

namespace qmapcontrol
{

    CheckableMapExtention::CheckableMapExtention(MapControl *mapControl, QObject *parent)
        : MapExtention(mapControl, parent), isChecked_(false)
    {
        isEnabledStopOnKeyboard_ = false;
    }

    CheckableMapExtention::~CheckableMapExtention()
    {
    }

    void CheckableMapExtention::start()
    {
        if (isEnabledStopOnKeyboard_)
        {
            stopOnKeyboard_ = connect(mapControl_, SIGNAL(keyboardEvent(const QKeyEvent*)), this, SLOT(keyboardEvent_(const QKeyEvent*)));
        }
        MapExtention::start();
    }

    void CheckableMapExtention::stop(MapExtention *sender)
    {
        if (stopOnKeyboard_)
            mapControl_->disconnect(stopOnKeyboard_);

        if (isChecked()) setChecked(false);
        MapExtention::stop(sender);
    }

    void CheckableMapExtention::setChecked(bool checked)
    {
        if (checked == isChecked()) return;
        isChecked_ = checked;

        if (checked)
        {
            start();
        }
        else if (!checked)
        {
            stop(this);
        }

        emit(checkedChanged(isChecked_));
    }

    bool CheckableMapExtention::isChecked()
    {
        return isChecked_;
    }

    void CheckableMapExtention::setEnableStopOnKeyboard(bool enable)
    {
        // только отключение, т.к.подключение возможно только по запуску start()
        if (!enable)
        {
            disconnect(stopOnKeyboard_);
        }
        isEnabledStopOnKeyboard_ = enable;
    }

    void CheckableMapExtention::keyboardEvent_(const QKeyEvent *event)
    {
        setChecked(false);
    }

}
