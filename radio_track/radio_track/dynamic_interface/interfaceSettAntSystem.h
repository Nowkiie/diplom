#pragma once
#include "baseInterface.h"
#include "../state.h"
#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include "../structParamNet.h"
#include <QString>

using namespace structParamNet;

class interfaceAntSystem : public baseInterface
{
public:
    interfaceAntSystem(stateRadiotrack state)
    {
        state_ = state;
        createWidget(state_);

        connect(sectorSendValueFrom,
                static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [=](int i)
                {
                    int value_before = sectorSendValueBefore->value();
                    if (i > value_before)
                    {
                        sectorSendValueFrom->setValue(value_before - 1);
                    }
                });

        connect(sectorAngleValueFrom,
                static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [=](int i)
                {
                    int value_before = sectorAngleValueBefore->value();
                    if (i > value_before)
                    {
                        sectorAngleValueFrom->setValue(value_before - 1);
                    }
                });
    };

    QWidget* getWidget() override
    {
        return wnd;
    };

    bool setData(QVariant parametr1) override
    {
        antSystem paramAntSystem = parametr1.value<antSystem>();
        nameAntSystem->setText(paramAntSystem.name);
        sectorSendValueFrom->setValue(paramAntSystem.sectorSendRec.first);
        sectorSendValueBefore->setValue(paramAntSystem.sectorSendRec.second);
        sectorAngleValueFrom->setValue(paramAntSystem.sectorAngle.first);
        sectorAngleValueBefore->setValue(paramAntSystem.sectorAngle.second);
        gainAnt->setValue(paramAntSystem.antGain);
        switch (paramAntSystem.typePolar)
        {
            case polarization::vertical:
            {
                vertical->setChecked(true);
                break;
            }
            case polarization::horizontal:
            {
                horizontal->setChecked(true);
                break;
            }
        }
        return false;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        antSystem paramAntSystem;
        paramAntSystem.name = nameAntSystem->text();
        paramAntSystem.sectorSendRec = std::pair<double, double>{
            sectorSendValueFrom->value(), sectorSendValueBefore->value()};
        paramAntSystem.sectorAngle = std::pair<double, double>{
            sectorAngleValueFrom->value(), sectorAngleValueBefore->value()};
        paramAntSystem.antGain = gainAnt->value();
        paramAntSystem.typePolar = getTypePolarization();

        QVariant qvar_paramAntSystem = QVariant::fromValue(paramAntSystem);

        stateRadiotrack nextState = getNextState(
            stateRadiotrack::settings_ant_system, qvar_paramAntSystem);
        std::pair<stateRadiotrack, QVariant> newStateAndData;

        switch (nextState)
        {
            case stateRadiotrack::settings_error_ant_system:
            {
                newStateAndData = {stateRadiotrack::settings_error_ant_system,
                                   qvar_paramAntSystem};
                break;
            }
            case stateRadiotrack::settings_ant_system:
            {
                newStateAndData = {stateRadiotrack::settings_ant_system,
                                   qvar_paramAntSystem};
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
        labelName = new QLabel(wnd);
        labelName->setText(QObject::tr("name ant system"));
        nameAntSystem = new QLineEdit(wnd);

        grdLayout = new QGridLayout();
        grdLayout->addWidget(labelName, 0, 0, 1, 1);
        grdLayout->addWidget(nameAntSystem, 0, 1, 1, 1);

        QLabel* label_gainAnt = new QLabel(wnd);
        label_gainAnt->setText(QObject::tr("Gain"));
        gainAnt = new QDoubleSpinBox(wnd);
        gainAnt->setMinimum(2.0);
        gainAnt->setMaximum(30.);
        gainAnt->setValue(2);
        QLabel* nameValueGain = new QLabel(wnd);
        nameValueGain->setText(QObject::tr("dB"));

        grdLayout->addWidget(label_gainAnt, 1, 0, 1, 1);
        grdLayout->addWidget(gainAnt, 1, 1, 1, 1);
        grdLayout->addWidget(nameValueGain, 1, 2, 1, 1);

        QLabel* fromSend = new QLabel(wnd);
        fromSend->setText(QObject::tr("from"));
        //  sectorSendValueFrom = new QSpinBox(wnd);
        sectorSendValueFrom->setValue(0);
        sectorSendValueFrom->setMinimum(0);
        sectorSendValueFrom->setMaximum(360);

        QLabel* beforeSend = new QLabel(wnd);
        beforeSend->setText(QObject::tr("before"));
        sectorSendValueBefore = new QSpinBox(wnd);
        sectorSendValueBefore->setValue(360);
        sectorSendValueBefore->setMinimum(0);
        sectorSendValueBefore->setMaximum(360);

        layout4GroupBoxSectorSend = new QGridLayout();
        layout4GroupBoxSectorSend->addWidget(fromSend, 0, 0);
        layout4GroupBoxSectorSend->addWidget(sectorSendValueFrom, 0, 1);
        layout4GroupBoxSectorSend->addWidget(beforeSend, 0, 2);
        layout4GroupBoxSectorSend->addWidget(sectorSendValueBefore, 0, 3);

        sectorSend_Rec = new QGroupBox(wnd);
        sectorSend_Rec->setTitle(QObject::tr("sector send/rec"));
        sectorSend_Rec->setLayout(layout4GroupBoxSectorSend);

        grdLayout->addWidget(sectorSend_Rec, 2, 0, 1, 2);

        QLabel* fromAngle = new QLabel(wnd);
        fromAngle->setText(QObject::tr("from"));
        sectorAngleValueFrom = new QSpinBox(wnd);
        sectorAngleValueFrom->setValue(0);
        sectorAngleValueFrom->setMinimum(0);
        sectorAngleValueFrom->setMaximum(90);

        QLabel* beforeAngle = new QLabel(wnd);
        beforeAngle->setText(QObject::tr("before"));
        sectorAngleValueBefore = new QSpinBox(wnd);
        sectorAngleValueBefore->setValue(90);
        sectorAngleValueBefore->setMinimum(0);
        sectorAngleValueBefore->setMaximum(360);
        sectorAngle = new QGroupBox(wnd);
        sectorAngle->setTitle(QObject::tr("sector angle"));
        layout4GroupBoxSectorAngle = new QGridLayout();
        layout4GroupBoxSectorAngle->addWidget(fromAngle, 0, 0);
        layout4GroupBoxSectorAngle->addWidget(sectorAngleValueFrom, 0, 1);
        layout4GroupBoxSectorAngle->addWidget(beforeAngle, 0, 2);
        layout4GroupBoxSectorAngle->addWidget(sectorAngleValueBefore, 0, 3);

        sectorAngle->setLayout(layout4GroupBoxSectorAngle);
        grdLayout->addWidget(sectorAngle, 3, 0, 1, 2);

        vertical = new QRadioButton(wnd);
        vertical->setText(QObject::tr("vertical"));
        vertical->setChecked(true);
        horizontal = new QRadioButton(wnd);
        horizontal->setText(QObject::tr("horizontal"));
        layout4GroupBoxPolar = new QGridLayout();
        layout4GroupBoxPolar->addWidget(vertical, 0, 0);
        layout4GroupBoxPolar->addWidget(horizontal, 0, 1);

        polarizationGroup = new QGroupBox(wnd);
        polarizationGroup->setTitle(QObject::tr("polarization"));
        polarizationGroup->setLayout(layout4GroupBoxPolar);

        grdLayout->addWidget(polarizationGroup, 4, 0, 1, 2);

        wnd->setLayout(grdLayout);
    };

    ~interfaceAntSystem()
    {
        delete wnd;
    };

private:
    stateRadiotrack state_;
    QWidget* wnd;

    QLabel* labelName;
    QLineEdit* nameAntSystem;
    QGroupBox* sectorSend_Rec;
    QSpinBox* sectorSendValueFrom = new QSpinBox();
    QSpinBox* sectorSendValueBefore;
    QGridLayout* layout4GroupBoxSectorSend;
    QGroupBox* sectorAngle;
    QDoubleSpinBox* gainAnt;
    QSpinBox* sectorAngleValueFrom;
    QSpinBox* sectorAngleValueBefore;
    QGridLayout* layout4GroupBoxSectorAngle;
    QGroupBox* polarizationGroup;
    QRadioButton* vertical;
    QRadioButton* horizontal;
    QGridLayout* layout4GroupBoxPolar;

    QGridLayout* grdLayout;

    polarization getTypePolarization()
    {
        if (vertical->isChecked())
        {
            return polarization::vertical;
        }
        if (horizontal->isChecked())
        {
            return polarization::horizontal;
        }
    };
};
