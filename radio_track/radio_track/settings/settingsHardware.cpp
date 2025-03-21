#include "settingsHardware.h"

settingsHardware::settingsHardware()
{
    widgetHardware_.setupUi(this);
    factoryInterface_ = std::make_shared<factoryInterface>();
    vbox = new QVBoxLayout();
    btnApply = new QPushButton();
    btnApply->setText(QObject::tr("Apply"));
    vbox->insertWidget(1, btnApply);

    connect(btnApply, &QPushButton::clicked,
            [this](bool clicked)
            {
                returnParametr param = interface_->getStateAndData();
                stateRadiotrack state = param.first;
                switch (state)
                {
                    case stateRadiotrack::settings_error_ant_system:
                    {
                        createInterface(stateRadiotrack::settings_ant_system);
                        writeData(param.second);
                        QErrorMessage* errMessage = new QErrorMessage();
                        errMessage->showMessage(
                            QObject::tr("uncorrect eneterd data"));
                        break;
                    }
                    case stateRadiotrack::settings_error_sender:
                    {
                        createInterface(stateRadiotrack::settings_sender);
                        writeData(param.second);
                        QErrorMessage* errMessage = new QErrorMessage();
                        errMessage->showMessage(
                            QObject::tr("uncorrect eneterd data"));
                        break;
                    }
                    case stateRadiotrack::settings_error_recvier:
                    {
                        createInterface(stateRadiotrack::settings_recvier);
                        writeData(param.second);
                        QErrorMessage* errMessage = new QErrorMessage();
                        errMessage->showMessage(
                            QObject::tr("uncorrect eneterd data"));
                        break;
                    }
                    default:
                    {
                        emit applySettings(param);
                        break;
                    }
                }
            });
}

void settingsHardware::createInterface(stateRadiotrack state)
{
    state_ = state;
    interface_ = factoryInterface_->createInterface(state_);
    addWidget(interface_->getWidget());
    this->setWindowTitle(getWindowNameByState(state_));
}

void settingsHardware::addWidget(QWidget* wdgt)
{
    vbox->insertWidget(0, wdgt);
    widgetHardware_.canvas->setLayout(vbox);
}

void settingsHardware::writeData(QVariant data)
{
    interface_->setData(data);
}
