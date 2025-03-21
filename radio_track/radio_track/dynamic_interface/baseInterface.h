#pragma once
#include <QWidget>
#include <QVariant>
#include <QMetaType>
#include <optional>
#include "../state.h"
#include "../struct/structEnetringData.h"
#include "../structParamNet.h"
#include "../structForSendParam.h"

class baseInterface : public QWidget
{
    Q_OBJECT
public:
    virtual QWidget* getWidget() = 0;

    virtual std::pair<stateRadiotrack, QVariant> getStateAndData() = 0;

    virtual bool setData(QVariant parametr1) = 0;

    /*
    * \brief проверка данных для установки в виджеты  
    * @param: state - текущее состояние
    *         data - данные от пользователя
    */
    bool checkUncorrectDataInState(stateRadiotrack state, QVariant data)
    {
        switch (state)
        {
            case stateRadiotrack::chooseMethodCalc:
            {
                if (!data.isNull())
                {
                    return true;
                }
                else
                    return false;
            }
            case stateRadiotrack::chooseMethodCalc4Coverage:
            {
                if (!data.isNull())
                {
                    return true;
                }
                return false;
            }
            case stateRadiotrack::choosePointsOnMap:
            {
                return false;
            }
            case stateRadiotrack::choosePointOnMap4Coverage:
            {
                return false;
            }
            case stateRadiotrack::choosePointOnMap4VisCoverage:
            {
                return false;
            }
            default:
            {
                return false;
            }
        }
    };

    /*
    * \brief проверка данных, записанных в виджеты
    * @param: state - текущее состояние
    *         data - данные из всех виджетов
    */
    //todo(PtakhovaA): change type return param. Create map/pair where state and error contain.
    //todo(PtakhovaA): in error write number == info
    stateRadiotrack getNextState(stateRadiotrack state, QVariant data)
    {
        switch (state)
        {
            case stateRadiotrack::chooseMethodCalc:
                break;
            case stateRadiotrack::choosePointsOnMap:
            {
                structures::paramForDrawing data_choose =
                    data.value<structures::paramForDrawing>();

                if (data_choose.coordBeginStr.value().latDegree == ""
                    || data_choose.coordEndStr.value().lonDegree == "")
                {
                    return stateRadiotrack::choosePointsOnMap;
                }
                return stateRadiotrack::drawRt;
            }

            case stateRadiotrack::chooseUnits:
            {
                paramWhenUseUnits dataUnits = data.value<paramWhenUseUnits>();
                if (dataUnits.numberFirstUnit == dataUnits.numberSecondUnit)
                {
                    return stateRadiotrack::chooseUnits;
                }
                return stateRadiotrack::drawRt;
            }
            case stateRadiotrack::drawRt:
                break;
            case stateRadiotrack::drawRtUnits:
                break;
            case stateRadiotrack::chooseMethodCalc4Coverage:
                break;
            case stateRadiotrack::choosePointOnMap4Coverage:
            {
                track::structures::coordInsideLineEdit dataFromEdit =
                    data.value<track::structures::coordInsideLineEdit>();
                if (dataFromEdit.latDegree == ""
                    || dataFromEdit.lonDegree == "")
                {
                    return stateRadiotrack::choosePointOnMap4Coverage;
                }
                return stateRadiotrack::drawCoverage;
            }
            case stateRadiotrack::choosePointOnMap4VisCoverage:
            {
                structures::coordInsideLineEdit dataFromEdit =
                    data.value<structures::coordInsideLineEdit>();
                if (dataFromEdit.latDegree == ""
                    || dataFromEdit.lonDegree == "")
                {
                    return stateRadiotrack::choosePointOnMap4VisCoverage;
                }
                return stateRadiotrack::drawVisCoverage;
            }
            case stateRadiotrack::chooseUnit4Coverage:
                break;
            case stateRadiotrack::drawCoverage:
                break;
            case stateRadiotrack::draw3d:
                break;
            case stateRadiotrack::defau:
                break;
            case stateRadiotrack::settings_ant_system:
            {
                structParamNet::antSystem dataAntSystem =
                    data.value<structParamNet::antSystem>();
                if (dataAntSystem.name == "")
                {
                    return stateRadiotrack::settings_error_ant_system;
                }
                if (dataAntSystem.antGain < 2)
                {
                    return stateRadiotrack::settings_error_ant_system;
                }
                return stateRadiotrack::settings_ant_system;
            }

            case stateRadiotrack::settings_sender:
            {
                structParamNet::sender dataSender =
                    data.value<structParamNet::sender>();
                if (dataSender.name == "")
                {
                    return stateRadiotrack::settings_error_sender;
                }
                return stateRadiotrack::settings_sender;
            }

            case stateRadiotrack::settings_recvier:
            {
                structParamNet::recvier dataRecvier =
                    data.value<structParamNet::recvier>();
                if (dataRecvier.name == "")
                {
                    return stateRadiotrack::settings_error_recvier;
                }
                return stateRadiotrack::settings_recvier;
            }

            default:
                break;
        }
    }

    //virtual void deleteWidget();
    // virtual void createWidget()=0;
};
