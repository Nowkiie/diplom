#include <fstream>
#include <string>
#include <math.h>
#include <qtoolbutton.h>
#include <QErrorMessage>
#include "radio_track.h"
#include "calculate/ToDegree.h"
#include "PelengCaption.h"
#include "structForSendParam.h"
#include <fstream>

using namespace track;
using json = nlohmann::json;

void radio_track::checkAvailibityData()
{
    if (!ui.mapWidget->checkMapInListLoadedMap("srtm"))
    {
        QErrorMessage* errMessage = new QErrorMessage();
        errMessage->showMessage(QObject::tr("Height maps doesn't load"));
        errMessage->activateWindow();
    }
}

void radio_track::initialData()
{
    ui.mapWidget->addMapButtonOnToolbar(ui.mainToolBar);
    paramNet_->readDataHardwareFromJson();
    tableData_->writeUnits(paramNet_->readDataFromJson());
    settForm_->updateComboAntSystem(paramNet_->getPointerOnVectorAntSystem());
    settForm_->updateComboSender(paramNet_->getPointerOnVectorSender());
    settForm_->updateComboRecvier(paramNet_->getPointerOnVectorRecvier());
}

radio_track::radio_track(PSettingControl appSettings, QWidget* parent)
    : QMainWindow(parent)
    , appSettings_(std::move(appSettings))
{
    ui.setupUi(this);

    using namespace structParamNet;
    paramNet_ = std::make_unique<paramNet>();
    calculatePoint_ = std::make_unique<calculatePoint>();
    calculateVis_ = std::make_unique<visiable_coverage>();
    valueCoordinate_ = std::make_unique<coordinate>();
    tableData_ = std::make_unique<tableModel>();
    settForm_ = std::make_unique<settingsForm>(tableData_.get());
    reliefForm_ = std::make_unique<Form>();
    dynamicInterface_ = std::make_shared<dynamicInterface>();
    dynamicInterface_->setWindowModality(Qt::WindowModality::WindowModal);
    factoryInterface_ = std::make_shared<factoryInterface>();
    calcLosses_ = std::make_unique<calculation::losses::calcLosses>();
    coordinate_ = std::make_unique<coordinate>();

    info = new QLabel();
    info->setText("grfusay");
    ui.statusBar->addWidget(info);

    //calcLosses_->calculateLossesInItmModel();
    initialData();

    actionWithSettingsForm();

    connect(
        dynamicInterface_.get(), &dynamicInterface::nextStep,
        [this](dynamicInterface::returnParametr param)
        {
            switch (param.first)
            {
                case stateRadiotrack::defau:
                {
                    dynamicInterface_->setEnableNextStep(false);
                    break;
                }
                case stateRadiotrack::choosePointsOnMap:
                {
                    ///если некорректные даннные -> переход в это же состояние +
                    ///восстановление данных
                    if (param.second != "")
                    {
                        std::pair<int, QVariant> data4RewritingWidget = {
                            2, param.second};
                        QVariant qvar_pairRewriting =
                            QVariant::fromValue(data4RewritingWidget);

                        dynamicInterface_->sendData(qvar_pairRewriting);
                    }

                    //отправка данных аппаратуры для отображения в combobox
                    paramForInitialDataOnUnitsInterface dataInterface;
                    dataInterface.senders =
                        paramNet_->getPointerOnVectorSender();
                    dataInterface.recviers =
                        paramNet_->getPointerOnVectorRecvier();
                    dataInterface.antSystems =
                        paramNet_->getPointerOnVectorAntSystem();

                    QVariant qvar_dataInterface =
                        QVariant::fromValue(dataInterface);
                    std::pair<int, QVariant> data4PointsInterface = {
                        0, qvar_dataInterface};

                    QVariant qvar_pair =
                        QVariant::fromValue(data4PointsInterface);

                    dynamicInterface_->sendData(qvar_pair);

                    break;
                }
                case stateRadiotrack::drawRt:
                {
                    if (param.second.canConvert<structures::paramForDrawing>())
                    {
                        structures::paramForDrawing paramRt =
                            param.second.value<structures::paramForDrawing>();
                        if (paramRt.coordBegin.has_value())
                        {
                            coordinate_point_begin = paramRt.coordBegin.value();
                        }
                        if (paramRt.coordEnd.has_value())
                        {
                            coordinate_point_end = paramRt.coordEnd.value();
                        }
                    }
                    else
                    {
                        paramWhenUseUnits units =
                            param.second.value<paramWhenUseUnits>();
                        coordinate_point_begin =
                            tableData_->getUnitByNumber(units.numberFirstUnit)
                                .coord;
                        coordinate_point_end =
                            tableData_->getUnitByNumber(units.numberSecondUnit)
                                .coord;
                    }

                    paramHardware hardware{
                        .ant_system = paramNet_->getPointerOnVectorAntSystem(),
                        .recv = paramNet_->getPointerOnVectorRecvier(),
                        .send = paramNet_->getPointerOnVectorSender()};

                    QVariant hardware_converted_qvariant =
                        QVariant::fromValue(hardware);

                    std::pair<stateRadiotrack, QVariant> link_state_hardware =
                        std::make_pair(stateRadiotrack::initParamDrawRt,
                                       hardware_converted_qvariant);

                    QVariant link_converted_qvariant =
                        QVariant::fromValue(link_state_hardware);
                    dynamicInterface_->sendData(link_converted_qvariant);

                    ui.mapWidget->clearPoint();
                    ui.mapWidget->drawPoint(coordinate_point_begin);
                    ui.mapWidget->drawPoint(coordinate_point_end);

                    ui.mapWidget->makeRequestMatrixOfTiles(
                        coordinate_point_begin, coordinate_point_end);
                    dynamicInterface_->setEnableNextStep(false);
                    break;
                }
                case stateRadiotrack::choosePointOnMap4Coverage:
                {
                    paramForInitialDataOnUnitsInterface dataInterface;
                    dataInterface.senders =
                        paramNet_->getPointerOnVectorSender();
                    dataInterface.recviers =
                        paramNet_->getPointerOnVectorRecvier();
                    dataInterface.units = tableData_->getPointerOnVectorUnit();
                    dataInterface.antSystems =
                        paramNet_->getPointerOnVectorAntSystem();

                    QVariant qvar_dataInterface =
                        QVariant::fromValue(dataInterface);
                    //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                    std::pair<int, QVariant> data4PointsInterface = {
                        0, qvar_dataInterface};

                    QVariant qvar_pair =
                        QVariant::fromValue(data4PointsInterface);

                    dynamicInterface_->sendData(qvar_pair);

                    if (param.second != "")
                    {
                        std::pair<int, QVariant> data4RewritingWidget = {
                            3, param.second};
                        QVariant qvar_pairRewriting =
                            QVariant::fromValue(data4RewritingWidget);
                        dynamicInterface_->sendData(qvar_pairRewriting);
                    }
                    break;
                }
                case stateRadiotrack::choosePointOnMap4VisCoverage:
                {
                    if (param.second != "")
                    {
                        std::pair<int, QVariant> data4RewritingWidget = {
                            4, param.second};
                        QVariant qvar_pairRewriting =
                            QVariant::fromValue(data4RewritingWidget);
                        dynamicInterface_->sendData(qvar_pairRewriting);
                    }
                    break;
                }
                case stateRadiotrack::drawCoverage:
                {
                    dynamicInterface_->setEnableNextStep(false);
                    checked_coverage = true;
                    QVariant qvar_param = param.second;

                    if (qvar_param.canConvert<paramForDrawCoverageWithUnit>())
                    {
                        paramForDrawCoverageWithUnit paramForDrawingCoverage;
                        paramForDrawingCoverage =
                            qvar_param.value<paramForDrawCoverageWithUnit>();

                        unit unit;

                        unit = tableData_->getUnitByNumber(
                            paramForDrawingCoverage.numberUnit);

                        getCoordFromCoverageStruct(qvar_param);

                        switch (type_)
                        {
                            case structures::typeCalculation::on_send:
                            {
                                heightAntSend = unit.hardware_.send.heightAnt;
                                power = unit.hardware_.send.power;
                                freq = unit.hardware_.send.sample_rate;

                                heightAntRec =
                                    paramNet_
                                        ->getDataForChangingRecvier(
                                            paramForDrawingCoverage
                                                .numberChoosingHardwareRecvier)
                                        .heightAnt;
                                sens =
                                    paramNet_
                                        ->getDataForChangingRecvier(
                                            paramForDrawingCoverage
                                                .numberChoosingHardwareRecvier)
                                        .sensitivity;

                                break;
                            }
                            case structures::typeCalculation::on_recv:
                            {
                                heightAntSend =
                                    paramNet_
                                        ->getDataForChangingSender(
                                            paramForDrawingCoverage
                                                .numberChoosingHardwareSender)
                                        .heightAnt;
                                power =
                                    paramNet_
                                        ->getDataForChangingSender(
                                            paramForDrawingCoverage
                                                .numberChoosingHardwareSender)
                                        .power;
                                freq =
                                    paramNet_
                                        ->getDataForChangingSender(
                                            paramForDrawingCoverage
                                                .numberChoosingHardwareSender)
                                        .sample_rate;

                                heightAntRec = unit.hardware_.rec.heightAnt;
                                sens = unit.hardware_.rec.sensitivity;

                                break;
                            }
                            default:
                            {
                                //todo(PtakhovaA): add exception
                                break;
                            }
                        }

                        dist = paramForDrawingCoverage.radius;

                        gain = paramNet_
                                   ->getDataForChangingAntSystem(
                                       paramForDrawingCoverage
                                           .numberChoosingHardwareAntSystem)
                                   .antGain;

                        climate = paramForDrawingCoverage.numberChoosingClimate;
                        pol = paramNet_
                                  ->getDataForChangingAntSystem(
                                      paramForDrawingCoverage
                                          .numberChoosingHardwareAntSystem)
                                  .typePolar;
                    }
                    else
                    {
                        structures::paramForDrawing paramForDrawingCoverage;
                        paramForDrawingCoverage =
                            qvar_param.value<structures::paramForDrawing>();

                        getCoordFromCoverageStruct(qvar_param);

                        heightAntSend =
                            paramNet_
                                ->getDataForChangingSender(
                                    paramForDrawingCoverage
                                        .numberChoosingHardwareSender)
                                .heightAnt;
                        heightAntRec =
                            paramNet_
                                ->getDataForChangingRecvier(
                                    paramForDrawingCoverage
                                        .numberChoosingHardwareRecvier)
                                .heightAnt;
                        power = paramNet_
                                    ->getDataForChangingSender(
                                        paramForDrawingCoverage
                                            .numberChoosingHardwareSender)
                                    .power;
                        sens = paramNet_
                                   ->getDataForChangingRecvier(
                                       paramForDrawingCoverage
                                           .numberChoosingHardwareRecvier)
                                   .sensitivity;
                        gain = paramNet_
                                   ->getDataForChangingAntSystem(
                                       paramForDrawingCoverage
                                           .numberChoosingHardwareAntSystem)
                                   .antGain;
                        freq = paramNet_
                                   ->getDataForChangingSender(
                                       paramForDrawingCoverage
                                           .numberChoosingHardwareSender)
                                   .sample_rate;
                        climate = paramForDrawingCoverage.numberChoosingClimate;
                        pol = paramNet_
                                  ->getDataForChangingAntSystem(
                                      paramForDrawingCoverage
                                          .numberChoosingHardwareAntSystem)
                                  .typePolar;
                    }

                    calcRefereancePoints();

                    QPointF coord_leftmost_point =
                        calculatePoint_->getRefPoint(270);
                    QPointF coord_rightmost_point =
                        calculatePoint_->getRefPoint(90);
                    QPointF coord_up_point = calculatePoint_->getRefPoint(0);
                    QPointF coord_down_point =
                        calculatePoint_->getRefPoint(180);

                    ui.mapWidget->makeRequestMatrixOfTiles(
                        coord_rightmost_point, coord_up_point,
                        coord_leftmost_point, coord_down_point);
                    break;
                }
                case stateRadiotrack::drawVisCoverage:
                {
                    dynamicInterface_->setEnableNextStep(false);
                    checked_coverage = true;
                    visual_coverage = true;

                    QVariant qvar_param = param.second;

                    if (qvar_param.canConvert<paramForDrawCoverageWithUnit>())
                    {
                        paramForDrawCoverageWithUnit paramForDarwingCoverage;
                        paramForDarwingCoverage =
                            qvar_param.value<paramForDrawCoverageWithUnit>();

                        unit unit;
                        unit = tableData_->getUnitByNumber(
                            paramForDarwingCoverage.numberUnit);

                        getCoordFromCoverageStruct(qvar_param);

                        heightAntSend = paramForDarwingCoverage.heightAntSend;
                        heightAntRec = paramForDarwingCoverage.heightAntRec;
                    }
                    else
                    {
                        structures::paramForDrawing paramForDrawingCoverage;
                        paramForDrawingCoverage =
                            qvar_param.value<structures::paramForDrawing>();

                        getCoordFromCoverageStruct(qvar_param);

                        heightAntSend = paramForDrawingCoverage.heightAntSend;
                        heightAntRec = paramForDrawingCoverage.heightAntRec;
                    }

                    calcRefereancePoints();

                    QPointF coord_leftmost_point =
                        calculatePoint_->getRefPoint(270);
                    QPointF coord_rightmost_point =
                        calculatePoint_->getRefPoint(90);
                    QPointF coord_up_point = calculatePoint_->getRefPoint(0);
                    QPointF coord_down_point =
                        calculatePoint_->getRefPoint(180);

                    ui.mapWidget->makeRequestMatrixOfTiles(
                        coord_rightmost_point, coord_up_point,
                        coord_leftmost_point, coord_down_point);

                    break;
                }
                case stateRadiotrack::chooseUnits:
                {
                    if (tableData_->getPointerOnVectorUnit().isEmpty())
                    {
                        settForm_->setStatusInitalWindow(true);
                        if (!tableData_->getPointerOnVectorUnit().isEmpty())
                        {
                            settForm_->setVisibleInfoText(false);
                        }
                        else
                        {
                            settForm_->setVisibleInfoText(true);
                        }
                        settForm_->show();
                    }
                    else
                    {
                        if (!tableData_->getPointerOnVectorUnit().isEmpty())
                        {
                            settForm_->setVisibleInfoText(false);
                        }
                        else
                        {
                            settForm_->setVisibleInfoText(true);
                        }
                        paramForInitialDataOnUnitsInterface dataInterface;
                        dataInterface.senders =
                            paramNet_->getPointerOnVectorSender();
                        dataInterface.recviers =
                            paramNet_->getPointerOnVectorRecvier();
                        dataInterface.units =
                            tableData_->getPointerOnVectorUnit();
                        dataInterface.antSystems =
                            paramNet_->getPointerOnVectorAntSystem();
                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        QVariant qvar_data = QVariant::fromValue(dataInterface);
                        dynamicInterface_->sendData(qvar_data);
                    }
                    break;
                }
                case stateRadiotrack::chooseUnit4VisCoverage:
                {
                    if (tableData_->getPointerOnVectorUnit().isEmpty())
                    {
                        // settForm_->setStatusInitalWindow(true);
                        settForm_->setVisibleInfoText(true);
                        settForm_->show();
                    }
                    else
                    {
                        paramForInitialDataOnUnitsInterface dataInterface;
                        dataInterface.senders =
                            paramNet_->getPointerOnVectorSender();
                        dataInterface.recviers =
                            paramNet_->getPointerOnVectorRecvier();
                        dataInterface.units =
                            tableData_->getPointerOnVectorUnit();
                        dataInterface.antSystems =
                            paramNet_->getPointerOnVectorAntSystem();
                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        QVariant qvar_data = QVariant::fromValue(dataInterface);
                        dynamicInterface_->sendData(qvar_data);
                    }
                    break;
                }
                case stateRadiotrack::drawRtUnits:
                {
                    QVariant test = param.second;
                    paramWhenUseUnits units = test.value<paramWhenUseUnits>();
                    unit send =
                        tableData_->getUnitByNumber(units.numberFirstUnit);

                    unit rec =
                        tableData_->getUnitByNumber(units.numberSecondUnit);

                    coordinate_point_begin =
                        QPointF{send.coord.x(), send.coord.y()};
                    coordinate_point_end =
                        QPointF{rec.coord.x(), rec.coord.y()};
                    ui.mapWidget->drawPoint(coordinate_point_begin);
                    ui.mapWidget->drawPoint(coordinate_point_end);
                    ui.mapWidget->makeRequestMatrixOfTiles(
                        coordinate_point_begin, coordinate_point_end);
                    dynamicInterface_->setEnableNextStep(false);
                    break;
                }
                case stateRadiotrack::chooseUnit4Coverage:
                {
                    if (tableData_->getPointerOnVectorUnit().isEmpty())
                    {
                        settForm_->show();
                    }
                    else
                    {
                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        paramForInitialDataOnUnitsInterface dataInterface;
                        dataInterface.senders =
                            paramNet_->getPointerOnVectorSender();
                        dataInterface.recviers =
                            paramNet_->getPointerOnVectorRecvier();
                        dataInterface.units =
                            tableData_->getPointerOnVectorUnit();
                        dataInterface.antSystems =
                            paramNet_->getPointerOnVectorAntSystem();
                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        QVariant qvar_data = QVariant::fromValue(dataInterface);
                        dynamicInterface_->sendData(qvar_data);
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        });

    connect(ui.mapWidget, &MapWidget::MouseMoveEvent,
            [this](const QMouseEvent* evnt, const QPointF coordinate)
            {
                QString geo_coord =
                    coordinate_->convertCoordinateWithPelengCaption(coordinate);

                QString double_coord = QString(" %1 %2")
                                           .arg(coordinate.y(), 0, 'g', 5)
                                           .arg(coordinate.x(), 0, 'g', 5);

                QPointF XY =
                    coordinate_->geoToCK(coordinate.y(), coordinate.x());
                QString xy_coord = QString(" x: %1 y: %2")
                                       .arg(XY.x(), 0, 'g', 12)
                                       .arg(XY.y(), 0, 'g', 12);
                QString coord = geo_coord + double_coord + xy_coord;
                info->setText(coord);
            });

    connect(
        ui.mapWidget, &MapWidget::MouseDoubleClickEvent,
        [this](QMouseEvent* evnt, QPointF coordinate)
        {
            if (!tableData_->returnStatusWorkWithUnit())
            {
                dynamicInterface_->activateWindow();
                if (checked_coverage && count_point > 0)
                {
                    ui.mapWidget->clearPoint();
                    count_point = 0;
                }
                else if (count_point > 1)
                {
                    ui.mapWidget->clearPoint();
                    count_point = 0;
                }

                paramWhenSelectPointsOnMap structSelectPoint{coordinate,
                                                             count_point};
                QVariant qvar_struct = QVariant::fromValue(structSelectPoint);
                std::pair<int, QVariant> data4PointsInterface = {1,
                                                                 qvar_struct};
                QVariant qvar_pair = QVariant::fromValue(data4PointsInterface);
                if (!dynamicInterface_->sendData(qvar_pair))
                {
                    ui.mapWidget->drawPoint(coordinate);
                    count_point == 0 ? coordinate_point_begin = coordinate
                                     : coordinate_point_end = coordinate;
                    count_point++;
                }
            }
            else
            {
                tableData_->writeCoord(coordinate);
            }

            /*else
            {
                count_point--;
            }*/
        });

    createToolButton();

    connect(ui.mapWidget, &MapWidget::loadingFinished,
            [this]()
            {
                // ui.mapWidget->addTextOnEdit("done loading");
                //вычисление дистанции между точками
                if (draw3D)
                {
                    reliefForm_->createComponetes(
                        ui.mapWidget->getPointerOnMatrixTile(),
                        ui.mapWidget->getFileHeights(),
                        ui.mapWidget->getFileTexture(coordinate_point_begin,
                                                     coordinate_point_end));
                    reliefForm_->show();
                    /*paramWhenDraw3D paramFor3D = {
                    };
                QVariant qvar_paramFor3D = QVariant::fromValue(paramFor3D);
                dynamicInterface_->sendData(qvar_paramFor3D);*/
                }
                else if (!checked_coverage)
                {
                    startCalculateRadiotrack();
                }
                else
                {
                    calculateVisiableCoverage();
                }
            });

    // checkAvailibityData();
}

void radio_track::calcRefereancePoints()
{
    for (int i = 0; i < 360; i += 1)
    {
        double arc = valueCoordinate_->deg_rad(i);
        switch (type_)
        {
            case structures::typeCalculation::on_send:
            {
                QPointF test = calculatePoint_->calcReferancePoint(
                    coordinate_point_begin, dist, arc);
                break;
            }
            case structures::typeCalculation::on_recv:
            {
                QPointF test = calculatePoint_->calcReferancePoint(
                    coordinate_point_end, dist, arc);
                break;
            }
            default:
            {
                //todo(PtakhovaA): add exception
                break;
            }
        }
    }
}

//todo(PtakhovaA): draw point on map
void radio_track::getCoordFromCoverageStruct(QVariant coverageStruct)
{
    if (coverageStruct.canConvert<structures::paramForDrawing>())
    {
        structures::paramForDrawing paramForDrawingCoverage;
        paramForDrawingCoverage =
            coverageStruct.value<structures::paramForDrawing>();

        dist = paramForDrawingCoverage.radius;
        type_ = paramForDrawingCoverage.type;
        switch (type_)
        {
            case structures::typeCalculation::on_send:
            {
                coordinate_point_begin =
                    paramForDrawingCoverage.coordBegin.value();
                ui.mapWidget->drawPoint(coordinate_point_begin);
                break;
            }
            case structures::typeCalculation::on_recv:
            {
                coordinate_point_end =
                    paramForDrawingCoverage.coordBegin.value();
                ui.mapWidget->drawPoint(coordinate_point_end);
                break;
            }
            default:
            {
                //todo(PtakhovaA): add exception
                break;
            }
        }
    }
    else
    {
        paramForDrawCoverageWithUnit paramForDrawingCoverage;
        paramForDrawingCoverage =
            coverageStruct.value<paramForDrawCoverageWithUnit>();

        unit unit;
        unit = tableData_->getUnitByNumber(paramForDrawingCoverage.numberUnit);

        dist = paramForDrawingCoverage.radius;
        type_ = paramForDrawingCoverage.type;
        switch (type_)
        {
            case structures::typeCalculation::on_send:
            {
                coordinate_point_begin =
                    QPointF(unit.coord.x(), unit.coord.y());
                ui.mapWidget->drawPoint(coordinate_point_begin);
                break;
            }
            case structures::typeCalculation::on_recv:
            {
                coordinate_point_end = QPointF(unit.coord.x(), unit.coord.y());
                ui.mapWidget->drawPoint(coordinate_point_end);
                break;
            }
            default:
            {
                //todo(PtakhovaA): add exception
                break;
            }
        }
    }
}

void radio_track::actionWithSettingsForm()
{
    connect(paramNet_.get(), &paramNet::updateVectorAntSystem,
            [this](const QVector<antSystem> ant_systems)
            {
                settForm_->updateComboAntSystem(ant_systems);
            });

    connect(paramNet_.get(), &paramNet::updateVectorSender,
            [this](QVector<structParamNet::sender>& send)
            {
                settForm_->updateComboSender(send);
            });

    connect(paramNet_.get(), &paramNet::updateVectorRecvier,
            [this](QVector<recvier> recviers)
            {
                settForm_->updateComboRecvier(recviers);
            });

    connect(settForm_.get(), &settingsForm::changeAntSystem,
            [this](int number)
            {
                settForm_->getDataUpdatingAntSystem(
                    paramNet_->getDataForChangingAntSystem(number));
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::delAntSystem,
            [this](int number)
            {
                paramNet_->del(number, typeSendParam::ant_system);
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::appendRecvier,
            [this](QVariant data, int number)
            {
                if (number == -1)
                {
                    paramNet_->add(data, typeSendParam::recvier);
                    updateInfoAboutHardware();
                }
                else
                {
                    paramNet_->update(data, typeSendParam::recvier, number);
                    updateInfoAboutHardware();
                }
            });

    connect(settForm_.get(), &settingsForm::appendAntSystem,
            [this](QVariant data, int number)
            {
                if (number == -1)
                {
                    paramNet_->add(data, typeSendParam::ant_system);
                    updateInfoAboutHardware();
                }
                else
                {
                    paramNet_->update(data, typeSendParam::ant_system, number);
                    updateInfoAboutHardware();
                }
            });

    connect(settForm_.get(), &settingsForm::changeRecvier,
            [this](int number)
            {
                settForm_->getDataUpdatingRecvier(
                    paramNet_->getDataForChangingRecvier(number));
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::changeSender,
            [this](int number)
            {
                settForm_->getDataUpdatingSender(
                    paramNet_->getDataForChangingSender(number));
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::appendSender,
            [this](QVariant data, int number)
            {
                if (number == -1)
                {
                    paramNet_->add(data, typeSendParam::send);
                    updateInfoAboutHardware();
                }
                else
                {
                    paramNet_->update(data, typeSendParam::send, number);
                    updateInfoAboutHardware();
                }
            });

    connect(settForm_.get(), &settingsForm::delSender,
            [this](int number)
            {
                paramNet_->del(number, typeSendParam::send);
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::delRecvier,
            [this](int number)
            {
                paramNet_->del(number, typeSendParam::recvier);
                updateInfoAboutHardware();
            });

    connect(settForm_.get(), &settingsForm::writeToJson,
            [this]()
            {
                settForm_->close();
                paramNet_->writeDatOnJson(tableData_->getPointerOnVectorUnit());
            });

    connect(settForm_.get(), &settingsForm::appendUnit,
            [this]()
            {
                tableData_->append();
            });

    connect(settForm_.get(), &settingsForm::changeUnit,
            [this](int idx)
            {
                tableData_->change(idx);
            });

    connect(settForm_.get(), &settingsForm::deleteUnit,
            [this](int idx)
            {
                tableData_->remove(idx);
            });

    connect(settForm_.get(), &settingsForm::dataUpload,
            [this](stateRadiotrack state)
            {
                switch (state)
                {
                    case stateRadiotrack::chooseUnits:
                    {
                        settForm_->close();
                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        paramForInitialDataOnUnitsInterface dataInterface;
                        dataInterface.senders =
                            paramNet_->getPointerOnVectorSender();
                        dataInterface.recviers =
                            paramNet_->getPointerOnVectorRecvier();
                        dataInterface.units =
                            tableData_->getPointerOnVectorUnit();

                        //dynamicInterface_->createInterface(stateRadiotrack::chooseUnits);
                        QVariant qvar_data = QVariant::fromValue(dataInterface);
                        dynamicInterface_->sendData(qvar_data);
                    }
                }
            });
}

//todo(PtakhovaA): add clear points on map after clicked btn
void radio_track::createToolButton()
{
    QToolButton* panelCalcRadiotrack = new QToolButton();
    panelCalcRadiotrack->setIcon(QIcon(":/resources/icons/radioTrack.png"));
    panelCalcRadiotrack->setToolTip(tr("radio link"));
    ui.mainToolBar->addWidget(panelCalcRadiotrack);
    connect(panelCalcRadiotrack, &QToolButton::clicked,
            [this](bool checked)
            {
                if (count_point > 0)
                {
                    count_point = 0;
                    ui.mapWidget->clearPoint();
                }
                panelRelief->setEnabled(false);
                dynamicInterface_->setEnableNextStep(true);
                dynamicInterface_->createInterface(
                    stateRadiotrack::chooseMethodCalc);
                dynamicInterface_->show();
                checked_coverage = false;
                draw3D = false;
                begin_operation = true;
                checkAvailibityData();
            });

    QToolButton* panelSettings = new QToolButton();
    panelSettings->setIcon(QIcon(":/resources/icons/settings.png"));
    panelSettings->setToolTip(tr("settings"));
    ui.mainToolBar->addWidget(panelSettings);
    connect(
        panelSettings, &QToolButton::clicked,
        [this](bool clicked)
        {
            settForm_->setStatusInitalWindow(false);
            settForm_->show();
            if (!tableData_->getPointerOnVectorUnit().isEmpty())
            {
                settForm_->setVisibleInfoText(false);
            }
            else
            {
                settForm_->setVisibleInfoText(true);
            }
            settForm_->updateComboAntSystem(
                paramNet_->getPointerOnVectorAntSystem());
            settForm_->updateComboSender(paramNet_->getPointerOnVectorSender());
            settForm_->updateComboRecvier(
                paramNet_->getPointerOnVectorRecvier());
            updateInfoAboutHardware();
            checkAvailibityData();
        });

    panelRelief = new QToolButton();

    QIcon icoRelief = QIcon();
    icoRelief.addFile(":/resources/icons/3d.png", QSize(16, 16),
                      QIcon::Disabled, QIcon::Off);
    panelRelief->setIcon(icoRelief);
    panelRelief->setEnabled(false);
    panelRelief->setToolTip("3D");
    ui.mainToolBar->addWidget(panelRelief);
    connect(panelRelief, &QToolButton::clicked,
            [this](bool clicked)
            {
                panelRelief->setEnabled(false);
                // dynamicInterface_->setEnableNextStep(false);
                draw3D = true;
                //  dynamicInterface_->createInterface(stateRadiotrack::draw3d);
                //  dynamicInterface_->show();
                ui.mapWidget->makeRequestTileFor3D(coordinate_point_begin,
                                                   coordinate_point_end);
                checkAvailibityData();
            });

    connect(reliefForm_.get(), &Form::workWith3DEnd,
            [this]()
            {
                draw3D = false;
            });

    QToolButton* panelPolarCoverage = new QToolButton();
    panelPolarCoverage->setIcon(QIcon(":/resources/icons/polarCoverage.png"));
    panelPolarCoverage->setToolTip(tr("polar radio coverage"));
    ui.mainToolBar->addWidget(panelPolarCoverage);
    connect(panelPolarCoverage, &QToolButton::clicked,
            [this](bool clicked)
            {
                // ui.mapWidget->addTextOnEdit(QString::number(count_point));
                if (count_point > 0)
                {
                    count_point = 0;
                    ui.mapWidget->clearPoint();
                }
                panelRelief->setEnabled(false);
                dynamicInterface_->setEnableNextStep(true);
                checked_coverage = true;
                visual_coverage = false;
                draw3D = false;
                number_ReferencePoint = 0;
                dynamicInterface_->createInterface(
                    stateRadiotrack::chooseMethodCalc4Coverage);
                dynamicInterface_->show();
                checkAvailibityData();
            });

    QToolButton* panelVisibleCoverage = new QToolButton();
    panelVisibleCoverage->setIcon(
        QIcon(":/resources/icons/visualCoverage.png"));
    panelVisibleCoverage->setToolTip(tr("visual coverage"));
    ui.mainToolBar->addWidget(panelVisibleCoverage);
    connect(panelVisibleCoverage, &QToolButton::clicked,
            [this](bool clicked)
            {
                if (count_point > 0)
                {
                    count_point = 0;
                    ui.mapWidget->clearPoint();
                }
                ui.mapWidget->addTextOnEdit(QString::number(count_point));
                panelRelief->setEnabled(false);
                dynamicInterface_->setEnableNextStep(true);
                checked_coverage = true;
                visual_coverage = true;
                draw3D = false;
                number_ReferencePoint = 0;
                dynamicInterface_->createInterface(
                    stateRadiotrack::chooseMethodCalc4VisCoverage);
                dynamicInterface_->show();
                checkAvailibityData();
            });

    QToolButton* clearBtn = new QToolButton();
    clearBtn->setIcon(QIcon(":/resources/icons/clear.png"));
    clearBtn->setToolTip(QObject::tr("clear"));
    ui.mainToolBar->addWidget(clearBtn);
    connect(clearBtn, &QToolButton::clicked,
            [this](bool clicked)
            {
                ui.mapWidget->clearCoverage();
            });
}

void radio_track::updateInfoAboutHardware()
{
    paramHardware listHardwares;
    listHardwares.ant_system = paramNet_->getPointerOnVectorAntSystem();
    listHardwares.recv = paramNet_->getPointerOnVectorRecvier();
    listHardwares.send = paramNet_->getPointerOnVectorSender();
    QVariant qvar_paramHardware = QVariant::fromValue(listHardwares);
    tableData_->initialMenu(qvar_paramHardware);
}

//todo: delete
void radio_track::matchingDistancePointWithHeights(QVector<int>& height)
{
    double k = 0;
    double H = 0;
    int R = 6371 * 2;

    for (int i = 0; i < calculatePoint_->getPointerOnVectorDist().size(); i++)
    {
        //
        k = calculatePoint_->getValueDistByNumber(i) / distance_;
        H = 1000 * ((distance_ * distance_ / R) * k * (1 - k));
        points << QPointF(calculatePoint_->getValueDistByNumber(i),
                          height[i] + H);
    }
}

void radio_track::findMinCoord(QPointF& coord_begin, QPointF& coord_end)
{
    if (coord_begin.x() > coord_end.x())
    {
        double temp = coord_begin.x();
        coord_begin.setX(coord_end.x());
        coord_end.setX(temp);
    }

    if (coord_begin.y() > coord_end.y())
    {
        double temp = coord_begin.y();
        coord_begin.setY(coord_end.y());
        coord_end.setY(temp);
    }
}

void radio_track::calculateVisiableCoverage()
{
    int a = 0;

    QPointF coord_leftmost_point = calculatePoint_->getRefPoint(270);
    QPointF coord_rightmost_point = calculatePoint_->getRefPoint(90);
    QPointF coord_up_point = calculatePoint_->getRefPoint(0);
    QPointF coord_down_point = calculatePoint_->getRefPoint(180);

    findMinCoord(coord_leftmost_point, coord_down_point);
    findMinCoord(coord_rightmost_point, coord_up_point);
    double step = 0.0021;
    int countIter_i = (coord_up_point.x() - coord_leftmost_point.x()) / step;
    int countIter_j = (coord_up_point.y() - coord_leftmost_point.y()) / step;

    int procLimitOpen = 0;
    int procLimitHalfClosed = 75;

    for (int i = 0; i <= countIter_i; i++)
    {
        for (int j = 0; j <= countIter_j; j++)
        {
            double coord_i = coord_leftmost_point.x() + i * step;
            double coord_j = coord_leftmost_point.y() + j * step;

            /*
             * на передачу - coordinate_point_begin - координаты, заданные в окне
             *          - coordinate_point_end - вычисленные координаты
             * на прием - coordinate_point_begin - вычисленные координаты
             *          - coordinate_point_end - координаты, заданные в окне
             */
            switch (type_)
            {
                case structures::typeCalculation::on_send:
                {
                    coordinate_point_end = QPointF{coord_i, coord_j};
                    break;
                }
                case structures::typeCalculation::on_recv:
                {
                    coordinate_point_begin = QPointF{coord_i, coord_j};
                    break;
                }
                default:
                    break;
            }

            distance_ = calculatePoint_->DistanceBTWPoints(
                coordinate_point_begin.y(), coordinate_point_begin.x(),
                coordinate_point_end.y(), coordinate_point_end.x());

            if (distance_ <= dist)
            {
                points.clear();
                lineSignal.clear();
                points_f.clear();
                points_phrenel.clear();

                calculatePoint_->clearVectorsCoordAndDistance();

                QPointF new_coord = {coord_i, coord_j};

                calculatePoint_->calculatePointsTrack(coordinate_point_begin,
                                                      new_coord, 0.000833);

                calculatePoint_->DistanceBTWBegin_PointFromPointsTrack(
                    coordinate_point_begin);

                matchingDistancePointWithHeights(ui.mapWidget->calculateHeights(
                    calculatePoint_->getPointerOnCoordPointsTrack()));

                //высота рельефа в точках, где располагаются антенны
                QPoint heightRelief = ui.mapWidget->getValueHeightAnt();

                //высота приемника/передатчика = высота рельефа + высота антенны
                int height_send = heightRelief.x() + heightAntSend;
                int height_rec = heightRelief.y() + heightAntRec;

                if (visual_coverage)
                {
                    lineSignal = calculatePoint_->calculatePointsTrack(
                        calculatePoint_->getPointerOnVectorDist(), height_send,
                        height_rec);

                    calculateVis_->makeMapWeight(points, lineSignal, new_coord);
                    calculateVis_->clearAll();
                    ui.mapWidget->drawingVisCoverage(
                        calculateVis_->getMapWeight(number_ReferencePoint));
                }
                else
                {
                    std::vector<double> profile;
                    profile.push_back(points.size());
                    profile.push_back(distance_);
                    for (auto el : points)
                    {
                        profile.push_back(el.y());
                    }

                    int polarization{};
                    switch (pol)
                    {
                        case polarization::vertical:
                        {
                            polarization = 1;
                            break;
                        }
                        case polarization::horizontal:
                        {
                            polarization = 0;
                            break;
                        }
                        default:
                        {
                            //todo:add exception
                            break;
                        }
                    }

                    double A_db = calcLosses_->calculateLossesInItmModel(
                        height_send, height_rec, profile, climate, freq,
                        polarization);

                    /*std::ofstream outf{"log.txt", std::ios::app};
                    outf << "coord: " << new_coord.x() << "," << new_coord.y()
                         << " profile size:" << profile.size();
                    outf.close();*/

                    calculateVis_->makeMapWeight(gain, power, sens, A_db,
                                                 new_coord);

                    calculateVis_->clearAll();
                    ui.mapWidget->drawingCoverage(
                        calculateVis_->getMapWeight(number_ReferencePoint));

                    profile.clear();
                }

                number_ReferencePoint++;
            }
        }
    }

    calculateVis_->start();
    calculatePoint_->clearVectorReferencePoints();
    number_ReferencePoint = 0;
    visual_coverage = false;
    checked_coverage = false;
    panelRelief->setEnabled(true);
}

void radio_track::startCalculateRadiotrack()
{
    points.clear();
    lineSignal.clear();
    points_f.clear();
    points_phrenel.clear();
    calculatePoint_->clearVectorsCoordAndDistance();

    calculatePoint_->calculatePointsTrack(coordinate_point_begin,
                                          coordinate_point_end, 0.000833);

    //todo(PtakhovaA): delete distance
    distance_ = calculatePoint_->DistanceBTWPoints(
        coordinate_point_begin.y(), coordinate_point_begin.x(),
        coordinate_point_end.y(), coordinate_point_end.x());

    calculatePoint_->DistanceBTWBegin_PointFromPointsTrack(
        coordinate_point_begin);

    double freq = 2.4;

    paramResultCalculateRt resultCalculateRt{
        ui.mapWidget->calculateHeights(
            calculatePoint_->getPointerOnCoordPointsTrack()),
        calculatePoint_->getPointerOnVectorDist(), freq};
    QVariant result_calculate_converted =
        QVariant::fromValue(resultCalculateRt);
    std::pair<stateRadiotrack, QVariant> linkStateResultCalc = std::make_pair(
        stateRadiotrack::outputResultCalculate, result_calculate_converted);

    QVariant link_state_result_converted =
        QVariant::fromValue(linkStateResultCalc);

    dynamicInterface_->sendData(link_state_result_converted);

    begin_operation = false;
    panelRelief->setEnabled(true);
}

void radio_track::closeEvent(QCloseEvent* event)
{
    event->accept();
}
