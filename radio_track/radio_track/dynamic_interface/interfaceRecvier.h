#pragma once
#include "baseInterface.h"
#include "../state.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>

class interfaceRecvier : public baseInterface
{
public:
    interfaceRecvier(stateRadiotrack state)
    {
        state_ = state;
        createWidget(state_);
    }

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();
        grdLayout = new QGridLayout();

        QLabel* nameLabel = new QLabel(wnd);
        nameLabel->setText(QObject::tr("name recvier"));
        nameRecvier = new QLineEdit(wnd);

        QLabel* gain = new QLabel(wnd);
        gain->setText(QObject::tr("sens"));
        valueSens = new QDoubleSpinBox(wnd);
        valueSens->setValue(0);
        valueSens->setRange(-140, 0);

        QLabel* nameValueSens = new QLabel(wnd);
        nameValueSens->setText(QObject::tr("dBm"));

        QLabel* labelHeight = new QLabel(wnd);
        labelHeight->setText(QObject::tr("height ant"));
        heightAnt = new QSpinBox(wnd);
        heightAnt->setValue(25);

        grdLayout->addWidget(nameLabel, 0, 0);
        grdLayout->addWidget(nameRecvier, 0, 1);
        grdLayout->addWidget(gain, 1, 0);
        grdLayout->addWidget(valueSens, 1, 1);
        grdLayout->addWidget(nameValueSens, 1, 2);
        grdLayout->addWidget(labelHeight, 2, 0);
        grdLayout->addWidget(heightAnt, 2, 1, 1, 2);

        wnd->setLayout(grdLayout);
    }

    QWidget* getWidget() override
    {
        return wnd;
    }

    bool setData(QVariant parametr1) override
    {
        recvier recv = parametr1.value<recvier>();
        nameRecvier->setText(recv.name);
        valueSens->setValue(recv.sensitivity);
        heightAnt->setValue(recv.heightAnt);

        return false;
    }

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        recvier recv;
        recv.name = nameRecvier->text();
        recv.sensitivity = valueSens->value();
        recv.heightAnt = heightAnt->value();

        QVariant qvar_recv = QVariant::fromValue(recv);
        std::pair<stateRadiotrack, QVariant> newStateAndData;

        stateRadiotrack nextState =
            getNextState(stateRadiotrack::settings_recvier, qvar_recv);

        switch (nextState)
        {
            case stateRadiotrack::settings_recvier:
            {
                newStateAndData = {stateRadiotrack::settings_recvier,
                                   qvar_recv};
                break;
            }
            case stateRadiotrack::settings_error_recvier:
            {
                newStateAndData = {stateRadiotrack::settings_error_recvier,
                                   qvar_recv};
                break;
            }
            default:
            {
                break;
            }
        }

        return newStateAndData;
    }

    ~interfaceRecvier()
    {
        delete wnd;
    }

private:
    stateRadiotrack state_;

    QWidget* wnd;
    QGridLayout* grdLayout;
    QLineEdit* nameRecvier;
    QDoubleSpinBox* valueSens;
    QSpinBox* heightAnt;
};
