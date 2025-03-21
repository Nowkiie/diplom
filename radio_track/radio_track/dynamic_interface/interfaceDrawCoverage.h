#pragma once
#include "baseInterface.h"
#include <QWidget>

class interfaceDrawCoverage : public baseInterface
{
public:
    interfaceDrawCoverage(stateRadiotrack state)
    {
        state_ = state;
        createWindow(state_);
    };

    bool setData(QVariant parametr) override
    {
        return true;
    };

    QWidget* getWidget() override
    {
        return wnd;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        std::pair<stateRadiotrack, QVariant> test = {stateRadiotrack::defau,
                                                     ""};
        return test;
    };

    void createWindow(stateRadiotrack state)
    {
        wnd = new QWidget();
    };

private:
    stateRadiotrack state_;
    QWidget* wnd;
};