#pragma once

#include "include/utils/factory.hpp"
#include <QWidget>
#include "interfaceRTMethodCalc.h"
#include "interfaceRTChoosePoint.h"
#include "interfaceRTChooseUnits.h"
#include "interfaceDrawRT.h"
#include "interfaceDrawCoverage.h"
#include "intrefaceDraw3D.h"
#include "interfaceSettAntSystem.h"
#include "interfaceRecvier.h"
#include "interfaceSender.h"

class factoryInterface : public QWidget
{
    Q_OBJECT
public:
    using resultType = std::shared_ptr<baseInterface>;

    factoryInterface()
        : factory_()
    {
        factory_.registry(stateRadiotrack::chooseMethodCalc, interf1Create);
        factory_.registry(stateRadiotrack::choosePointsOnMap, interf2Create);
        factory_.registry(stateRadiotrack::chooseUnits, interf3Create);
        factory_.registry(stateRadiotrack::drawRt, interf4Create);
        factory_.registry(stateRadiotrack::chooseMethodCalc4Coverage,
                          interf1Create);
        factory_.registry(stateRadiotrack::choosePointOnMap4Coverage,
                          interf2Create);
        factory_.registry(stateRadiotrack::drawCoverage, interf5Create);
        factory_.registry(stateRadiotrack::draw3d, interf6Create);
        factory_.registry(stateRadiotrack::drawRtUnits, interf4Create);
        factory_.registry(stateRadiotrack::chooseUnit4Coverage, interf3Create);
        factory_.registry(stateRadiotrack::settings_ant_system, interf7Create);
        factory_.registry(stateRadiotrack::settings_recvier, interf8Create);
        factory_.registry(stateRadiotrack::settings_sender, interf9Create);
        factory_.registry(stateRadiotrack::chooseMethodCalc4VisCoverage,
                          interf1Create);
        factory_.registry(stateRadiotrack::choosePointOnMap4VisCoverage,
                          interf2Create);
        factory_.registry(stateRadiotrack::chooseUnit4VisCoverage,
                          interf3Create);
        factory_.registry(stateRadiotrack::drawVisCoverage, interf5Create);
    };

    auto createInterface(stateRadiotrack state) -> resultType
    {
        return factory_.create(state, state);
    }

private:
    static auto interf1Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<intefaceRTChooseMethodCalc>(state);
        return ptr;
    }

    static auto interf2Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<intefaceChoosePointsOnMap>(state);
        return ptr;
    }

    static auto interf3Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceChooseUnits>(state);
        return ptr;
    }

    static auto interf4Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<intefaceDrawRt>(state);
        return ptr;
    }

    static auto interf5Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceDrawCoverage>(state);
        return ptr;
    }

    static auto interf6Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceDraw3d>(state);
        return ptr;
    }

    static auto interf7Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceAntSystem>(state);
        return ptr;
    }

    static auto interf8Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceRecvier>(state);
        return ptr;
    }

    static auto interf9Create(stateRadiotrack state) -> resultType
    {
        auto ptr = std::make_shared<interfaceSender>(state);
        return ptr;
    }

    utils::factory<stateRadiotrack, resultType(stateRadiotrack state)> factory_;
};
