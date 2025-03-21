#pragma once
#include "baseInterface.h"
#include "../state.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGroupBox>

class interfaceSender : public baseInterface
{
public:
    interfaceSender(stateRadiotrack state)
    {
        state_ = state;
        createWidget(state_);
    }

    QWidget* getWidget() override
    {
        return wnd;
    };

    bool setData(QVariant parametr1) override
    {
        structParamNet::sender paramSender =
            parametr1.value<structParamNet::sender>();
        nameSender->setText(paramSender.name);
        valuePower->setValue(paramSender.power);
        freqValue->setValue(paramSender.sample_rate);
        heightAnt->setValue(paramSender.heightAnt);

        return false;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        structParamNet::sender paramSender;
        paramSender.name = nameSender->text();
        paramSender.sample_rate = freqValue->value();
        paramSender.power = valuePower->value();
        paramSender.heightAnt = heightAnt->value();

        QVariant qvar_paramSender = QVariant::fromValue(paramSender);

        std::pair<stateRadiotrack, QVariant> newStateAndData;

        stateRadiotrack nextState =
            getNextState(stateRadiotrack::settings_sender, qvar_paramSender);
        switch (nextState)
        {
            case stateRadiotrack::settings_sender:
            {
                newStateAndData = {stateRadiotrack::settings_sender,
                                   qvar_paramSender};
                break;
            }
            case stateRadiotrack::settings_error_sender:
            {
                newStateAndData = {stateRadiotrack::settings_error_sender,
                                   qvar_paramSender};
                break;
            }
            default:
            {
                break;
            }
        }

        return newStateAndData;
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();
        grdLayout = new QGridLayout();

        QLabel* nameLabel = new QLabel(wnd);
        nameLabel->setText(QObject::tr("name sender"));
        nameSender = new QLineEdit(wnd);

        QLabel* powerLabel = new QLabel(wnd);
        powerLabel->setText(QObject::tr("power"));
        valuePower = new QDoubleSpinBox(wnd);
        valuePower->setValue(30);
        valuePower->setRange(-140, 90);

        QLabel* nameValuePower = new QLabel(wnd);
        nameValuePower->setText(QObject::tr("dBm"));

        QLabel* label_freq = new QLabel(wnd);
        label_freq->setText(QObject::tr("freq"));
        freqValue = new QDoubleSpinBox(wnd);
        freqValue->setValue(26);
        freqValue->setRange(20, 200);

        QLabel* labelHeight = new QLabel(wnd);
        labelHeight->setText(QObject::tr("height ant"));
        heightAnt = new QSpinBox(wnd);
        heightAnt->setValue(25);

        QLabel* freqNameValue = new QLabel(wnd);
        freqNameValue->setText(QObject::tr("MHz"));

        grdLayout->addWidget(nameLabel, 0, 0);
        grdLayout->addWidget(nameSender, 0, 1, 1, 1);
        grdLayout->addWidget(powerLabel, 1, 0);
        grdLayout->addWidget(valuePower, 1, 1);
        grdLayout->addWidget(nameValuePower, 1, 2);
        grdLayout->addWidget(label_freq, 2, 0, 1, 1);
        grdLayout->addWidget(freqValue, 2, 1, 1, 1);
        grdLayout->addWidget(freqNameValue, 2, 2, 1, 1);
        grdLayout->addWidget(labelHeight, 3, 0);
        grdLayout->addWidget(heightAnt, 3, 1, 1, 2);

        wnd->setLayout(grdLayout);
    }

    ~interfaceSender()
    {
        delete wnd;
    }

private:
    stateRadiotrack state_;

    QWidget* wnd;
    QGridLayout* grdLayout;
    QLineEdit* nameSender;
    QDoubleSpinBox* valuePower;
    QDoubleSpinBox* freqValue;
    QSpinBox* heightAnt;
};