#pragma once
#include <iostream>
#include <QString>
#include <QWidget>
#include <QMetaType>

enum class stateRadiotrack
{
    drawRt,
    initParamDrawRt,
    calculateRt,
    outputResultCalculate,
    

    chooseMethodCalc,
    choosePointsOnMap,
    chooseUnits,
    drawRtUnits,
    chooseMethodCalc4Coverage,
    choosePointOnMap4Coverage,
    chooseUnit4Coverage,
    drawCoverage,
    draw3d,
    defau,
    settings_ant_system,
    settings_sender,
    settings_recvier,
    settings_error_ant_system,
    settings_error_sender,
    settings_error_recvier,
    chooseMethodCalc4VisCoverage,
    choosePointOnMap4VisCoverage,
    chooseUnit4VisCoverage,
    drawVisCoverage,
    error
};

Q_DECLARE_METATYPE(stateRadiotrack)

inline int getNumberByState(stateRadiotrack state)
{
    switch (state)
    {
        case stateRadiotrack::chooseMethodCalc:
        {
            return 1;
        }
        case stateRadiotrack::chooseMethodCalc4Coverage:
        {
            return 1;
        }
        case stateRadiotrack::chooseMethodCalc4VisCoverage:
        {
            return 1;
        }
        case stateRadiotrack::choosePointsOnMap:
        {
            return 2;
        }
        case stateRadiotrack::choosePointOnMap4Coverage:
        {
            return 2;
        }
        case stateRadiotrack::choosePointOnMap4VisCoverage:
        {
            return 2;
        }
        case stateRadiotrack::chooseUnit4Coverage:
        {
            return 2;
        }
        case stateRadiotrack::chooseUnits:
        {
            return 2;
        }
        case stateRadiotrack::chooseUnit4VisCoverage:
        {
            return 2;
        }
        case stateRadiotrack::drawCoverage:
        {
            return 3;
        }
        case stateRadiotrack::drawVisCoverage:
        {
            return 3;
        }
        case stateRadiotrack::drawRt:
        {
            return 3;
        }
        case stateRadiotrack::initParamDrawRt:
        {
            return 3;
        }
        case stateRadiotrack::drawRtUnits:
        {
            return 3;
        }
        default:
        {
            return 3;
        }
    }
}

inline QString getWindowNameByState(stateRadiotrack state)
{
    switch (state)
    {
        case stateRadiotrack::chooseMethodCalc:
        {
            return QObject::tr("radiotrack");
        }
        case stateRadiotrack::chooseMethodCalc4Coverage:
        {
            return QObject::tr("coverage");
        }
        case stateRadiotrack::chooseMethodCalc4VisCoverage:
        {
            return QObject::tr("visible coverage");
        }
        case stateRadiotrack::choosePointsOnMap:
        {
            return QObject::tr("radiotrack");
        }
        case stateRadiotrack::choosePointOnMap4Coverage:
        {
            return QObject::tr("coverage");
        }
        case stateRadiotrack::choosePointOnMap4VisCoverage:
        {
            return QObject::tr("visible coverage");
        }
        case stateRadiotrack::chooseUnit4Coverage:
        {
            return QObject::tr("coverage");
        }
        case stateRadiotrack::chooseUnit4VisCoverage:
        {
            return QObject::tr("visible coverage");
        }
        case stateRadiotrack::chooseUnits:
        {
            return QObject::tr("radiotrack");
        }
        case stateRadiotrack::drawCoverage:
        {
            return QObject::tr("coverage");
        }
        case stateRadiotrack::drawVisCoverage:
        {
            return QObject::tr("visible coverage");
        }
        case stateRadiotrack::drawRt:
        {
            return QObject::tr("radiotrack");
        }
        case stateRadiotrack::drawRtUnits:
        {
            return QObject::tr("radiotrack");
        }
        case stateRadiotrack::settings_sender:
        {
            return QObject::tr("settings sender");
        }
        case stateRadiotrack::settings_recvier:
        {
            return QObject::tr("settings recvier");
        }
        case stateRadiotrack::settings_ant_system:
        {
            return QObject::tr("settings ant system");
        }
        case stateRadiotrack::draw3d:
        {
            return QObject::tr("3D");
        }
        default:
        {
            return "";
        }
    }
}
