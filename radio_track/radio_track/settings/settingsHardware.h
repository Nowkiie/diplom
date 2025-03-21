#pragma once
#include "ui_settingsHardware.h"
#include "../state.h"
#include "../dynamic_interface/factory.h"
#include <QVBoxLayout>
#include <QPushButton>



class settingsHardware : public QWidget
{
    
    Q_OBJECT
public:
    using returnParametr = std::pair<stateRadiotrack, QVariant>;
    settingsHardware();
    void createInterface(stateRadiotrack state);
    void writeData(QVariant data);
signals:
    void applySettings(returnParametr);

private:
    Ui::widgetHardware widgetHardware_;
    std::shared_ptr<factoryInterface> factoryInterface_;
    std::shared_ptr<baseInterface> interface_;
    stateRadiotrack state_;
    QVBoxLayout* vbox;
    QPushButton* btnApply;
    void addWidget(QWidget* wdgt);

    
};