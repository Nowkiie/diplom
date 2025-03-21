#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include "baseInterface.h"
#include "../state.h"
#include <qerrormessage.h>

class intefaceRTChooseMethodCalc : public baseInterface
{
public:
    intefaceRTChooseMethodCalc(stateRadiotrack state)
    {
        state_ = state;
        createWidget(state_);
    };

    bool setData(QVariant parametr) override
    {
        bool resultCheck = checkUncorrectDataInState(state_, parametr);
        if (resultCheck)
        {
            QErrorMessage* errMessage = new QErrorMessage;
            errMessage->showMessage(QObject::tr(
                "Uncorrected data. U need choose method by using radiobutton"));
        }

        return resultCheck;
    };

    QWidget* getWidget() override
    {
        return wnd;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        std::pair<stateRadiotrack, QVariant> newStateAndData;
        switch (state_)
        {
            case stateRadiotrack::chooseMethodCalc:
            {
                if (choosePointOnMap->isChecked())
                {
                    newStateAndData = {stateRadiotrack::choosePointsOnMap, ""};
                }
                if (chooseUnit->isChecked())
                {
                    newStateAndData = {stateRadiotrack::chooseUnits, ""};
                }
                break;
            }
            case stateRadiotrack::chooseMethodCalc4Coverage:
            {
                if (choosePointOnMap->isChecked())
                {
                    newStateAndData = {
                        stateRadiotrack::choosePointOnMap4Coverage, ""};
                }
                if (chooseUnit->isChecked())
                {
                    newStateAndData = {stateRadiotrack::chooseUnit4Coverage,
                                       ""};
                }
                break;
            }
            case stateRadiotrack::chooseMethodCalc4VisCoverage:
            {
                if (choosePointOnMap->isChecked())
                {
                    newStateAndData = {
                        stateRadiotrack::choosePointOnMap4VisCoverage, ""};
                }
                if (chooseUnit->isChecked())
                {
                    newStateAndData = {stateRadiotrack::chooseUnit4VisCoverage,
                                       ""};
                }
                break;
            }
            default:
            {
                //todo: add exception
                break;
            }
        }

        return newStateAndData;
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();
        choosePointOnMap = new QRadioButton(wnd);
        chooseUnit = new QRadioButton(wnd);
        infoText = new QLabel(wnd);
        vbox = new QVBoxLayout(wnd);

        switch (state)
        {
            case stateRadiotrack::chooseMethodCalc:
            {
                QString text4ChoosePoints = QObject::tr("choose points on map");
                choosePointOnMap->setText(text4ChoosePoints);
                chooseUnit->setText(QObject::tr("choose units"));

                infoText->setText(QObject::tr(
                    "Select the method you want to use to calculate the "
                    "radiotrack:"));
                break;
            }
            case stateRadiotrack::chooseMethodCalc4Coverage:
            {
                choosePointOnMap->setText(QObject::tr(
                    "choose point on map and enter radius coverage"));
                chooseUnit->setText(
                    QObject::tr("choose unit and enter radius coverage"));

                infoText->setText(QObject::tr(
                    "Select the method you want to use to calculate the "
                    "radiotrack coverage:"));
                break;
            }
            case stateRadiotrack::chooseMethodCalc4VisCoverage:
            {
                choosePointOnMap->setText(QObject::tr(
                    "choose point on map and enter radius coverage"));
                chooseUnit->setText(
                    QObject::tr("choose unit and enter radius coverage"));

                infoText->setText(QObject::tr(
                    "Select the method you want to use to calculate the "
                    "visual coverage:"));
                break;
            }
            default:
            {
                //todo: add exception
                break;
            }
        }

        choosePointOnMap->setChecked(true);
        vbox->addWidget(infoText);
        vbox->addWidget(choosePointOnMap);
        vbox->addWidget(chooseUnit);
        wnd->setLayout(vbox);
    };

    ~intefaceRTChooseMethodCalc()
    {
        delete wnd;
    };

private:
    QWidget* wnd;
    QRadioButton* choosePointOnMap;
    QRadioButton* chooseUnit;
    QLabel* infoText;
    QVBoxLayout* vbox;

    stateRadiotrack state_;
};
