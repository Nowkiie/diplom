#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "QLabel"
#include <QSpinBox>
#include <QErrorMessage>

#include "baseInterface.h"
#include "../structForSendParam.h"
#include "../struct/structEnetringData.h"
#include "../widgets/widgetCoordinate.h"
#include "../dynamic_interface/paramsList.h"

class intefaceChoosePointsOnMap : public baseInterface
{
public:
    intefaceChoosePointsOnMap(stateRadiotrack state)
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
        bool resultCheck = checkUncorrectDataInState(state_, parametr1);

        std::pair<int, QVariant> data4InterfacePoint =
            parametr1.value<std::pair<int, QVariant>>();

        if (!resultCheck)
        {
            int select = data4InterfacePoint.first;
            switch (select)
            {
                //todo(PtakhovaA): try to change type select from int to enum
                case 0:
                {
                    paramInterface =
                        data4InterfacePoint.second
                            .value<paramForInitialDataOnUnitsInterface>();
                    for (auto el : paramInterface.senders)
                    {
                        senderHardware->addItem(el.name);
                    }
                    for (auto el : paramInterface.recviers)
                    {
                        recvierHardware->addItem(el.name);
                    }
                    for (auto el : paramInterface.antSystems)
                    {
                        antSystemHardware->addItem(el.name);
                    }

                    climat->addItems(climateParams::getClimateList());
                    climat->setCurrentIndex(
                        climateParams::climateList::continental_temperate);

                    if (state_ != stateRadiotrack::choosePointsOnMap)
                    {
                        int heightAnt_send =
                            paramInterface
                                .senders[senderHardware->currentIndex()]
                                .heightAnt;
                        int heightAnt_rec =
                            paramInterface
                                .recviers[recvierHardware->currentIndex()]
                                .heightAnt;
                        radius->setValue(
                            calcValueRadius(heightAnt_send, heightAnt_rec));
                    }

                    break;
                }
                case 1:
                {
                    paramWhenSelectPointsOnMap structSelectPoint;
                    structSelectPoint =
                        data4InterfacePoint.second
                            .value<paramWhenSelectPointsOnMap>();
                    QPointF coord = structSelectPoint.coordPoint;

                    int numberPoint = structSelectPoint.numberPoint;
                    switch (state_)
                    {
                        case stateRadiotrack::choosePointsOnMap:
                        {
                            switch (numberPoint)
                            {
                                case 0:
                                {
                                    coordinate_sender->setDataFromWidget(coord);
                                    coordinate_recvier->clearDataFromWidget();
                                    break;
                                }
                                case 1:
                                {
                                    coordinate_recvier->setDataFromWidget(
                                        coord);
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                            break;
                        }
                        case stateRadiotrack::choosePointOnMap4Coverage:
                        {
                            coordinate_sender->setDataFromWidget(coord);
                            break;
                        }
                        case stateRadiotrack::choosePointOnMap4VisCoverage:
                        {
                            coordinate_sender->setDataFromWidget(coord);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }

                    break;
                }
                case 2:
                {
                    structures::paramForDrawing param;
                    param = data4InterfacePoint.second
                                .value<structures::paramForDrawing>();
                    coordinate_sender->setDataFromWidget(
                        param.coordBeginStr.value());
                    coordinate_recvier->setDataFromWidget(
                        param.coordEndStr.value());
                    climat->setCurrentIndex(param.numberChoosingClimate);
                    antSystemHardware->setCurrentIndex(
                        param.numberChoosingHardwareAntSystem);
                    senderHardware->setCurrentIndex(
                        param.numberChoosingHardwareSender);
                    recvierHardware->setCurrentIndex(
                        param.numberChoosingHardwareRecvier);

                    break;
                }
                case 3:
                {
                    track::structures::paramForDrawing paramForCoverage;
                    paramForCoverage =
                        data4InterfacePoint.second
                            .value<structures::paramForDrawing>();
                    if (paramForCoverage.coordBegin.has_value())
                    {
                        coordinate_sender->setDataFromWidget(
                            paramForCoverage.coordBegin.value());
                    }
                    else if (paramForCoverage.coordBeginStr.has_value())
                    {
                        coordinate_sender->setDataFromWidget(
                            paramForCoverage.coordBeginStr.value());
                    }

                    radius->setValue(paramForCoverage.radius);
                    senderHardware->setCurrentIndex(
                        paramForCoverage.numberChoosingHardwareSender);
                    recvierHardware->setCurrentIndex(
                        paramForCoverage.numberChoosingHardwareRecvier);
                    break;
                }
                case 4:
                {
                    structures::paramForDrawing paramForCoverage;
                    paramForCoverage =
                        data4InterfacePoint.second
                            .value<structures::paramForDrawing>();
                    if (paramForCoverage.coordBeginStr.has_value())
                    {
                        coordinate_sender->setDataFromWidget(
                            paramForCoverage.coordBeginStr.value());
                    }

                    radius->setValue(paramForCoverage.radius);
                    heightAntSend->setValue(paramForCoverage.heightAntSend);
                    heightAntRec->setValue(paramForCoverage.heightAntRec);
                    break;
                }
            }
        }

        if (state_ == stateRadiotrack::choosePointOnMap4Coverage)
        {
            connect(senderHardware,
                    static_cast<void (QComboBox::*)(int)>(
                        &QComboBox::currentIndexChanged),
                    [=](int index)
                    {
                        int heightAnt_sender =
                            paramInterface.senders[index].heightAnt;
                        int heightAnt_rec =
                            paramInterface
                                .recviers[recvierHardware->currentIndex()]
                                .heightAnt;
                        radius->setValue(
                            calcValueRadius(heightAnt_sender, heightAnt_rec));
                    });

            connect(recvierHardware,
                    static_cast<void (QComboBox::*)(int)>(
                        &QComboBox::currentIndexChanged),
                    [=](int index)
                    {
                        int heightAnt_rec =
                            paramInterface.recviers[index].heightAnt;
                        int heightAnt_sender =
                            paramInterface
                                .senders[senderHardware->currentIndex()]
                                .heightAnt;
                        radius->setValue(
                            calcValueRadius(heightAnt_sender, heightAnt_rec));
                    });
            connect(btnTypeCalculate, &QPushButton::clicked,
                    [this](bool clicked)
                    {
                        if (btnTypeCalculate->text()
                            == QObject::tr("calculation make for send"))
                        {
                            btnTypeCalculate->setText(
                                QObject::tr("calculation make for get"));
                            moveCoordinateWidget(layoutSender, layoutRecvier);
                        }
                        else
                        {
                            btnTypeCalculate->setText(
                                QObject::tr("calculation make for send"));
                            moveCoordinateWidget(layoutSender, layoutRecvier);
                        }
                    });
        }

        return resultCheck;
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();
        QVBoxLayout* vbox = new QVBoxLayout(wnd);

        senderParam = new QGroupBox(wnd);
        senderParam->setTitle(QObject::tr("Sender"));
        layoutSender = new QGridLayout;

        coordinate_sender =
            new ::widget::widgetCoordinate(QObject::tr("coordinate"));

        recvierParam = new QGroupBox(wnd);
        recvierParam->setTitle(QObject::tr("Recvier"));
        layoutRecvier = new QGridLayout();

        switch (state)
        {
            case stateRadiotrack::choosePointsOnMap:
            {
                layoutSender->addWidget(coordinate_sender->getWidget(), 0, 0, 1,
                                        2);

                //добавить аппаратуру источнику
                QLabel* label_SenderHard = new QLabel(wnd);
                label_SenderHard->setText(QObject::tr("Name hardware"));
                senderHardware = new QComboBox(wnd);

                layoutSender->addWidget(label_SenderHard, 1, 0, 1, 1);
                layoutSender->addWidget(senderHardware, 1, 1, 1, 1);

                coordinate_recvier = new ::widget::widgetCoordinate(
                    QObject::tr("coordinate recvier"));

                //аппаратура у приемника
                QLabel* label_recvHard = new QLabel(wnd);
                label_recvHard->setText(QObject::tr("Name hardware"));
                recvierHardware = new QComboBox(wnd);

                layoutRecvier->addWidget(coordinate_recvier->getWidget(), 0, 0,
                                         1, 2);
                layoutRecvier->addWidget(label_recvHard, 1, 0, 1, 1);
                layoutRecvier->addWidget(recvierHardware, 1, 1, 1, 1);

                recvierParam->setLayout(layoutRecvier);

                // дополнительные параметры: антенная система + климат
                layout4GroupBoxAdditionalParam = new QGridLayout(wnd);
                additonalParam = new QGroupBox(wnd);
                additonalParam->setTitle(QObject::tr("additinal param"));

                QLabel* label_antSystem = new QLabel(wnd);
                label_antSystem->setText(QObject::tr("name ant system"));
                antSystemHardware = new QComboBox(wnd);
                layout4GroupBoxAdditionalParam->addWidget(label_antSystem, 0, 0,
                                                          1, 1);
                layout4GroupBoxAdditionalParam->addWidget(antSystemHardware, 0,
                                                          1, 1, 1);

                QLabel* label_climate = new QLabel(wnd);
                label_climate->setText(QObject::tr("climate"));
                climat = new QComboBox(wnd);
                layout4GroupBoxAdditionalParam->addWidget(label_climate, 1, 0,
                                                          1, 1);
                layout4GroupBoxAdditionalParam->addWidget(climat, 1, 1, 1, 1);
                additonalParam->setLayout(layout4GroupBoxAdditionalParam);

                break;
            }
            case stateRadiotrack::choosePointOnMap4Coverage:
            {
                btnTypeCalculate = new QPushButton(wnd);
                btnTypeCalculate->setText(
                    QObject::tr("calculation make for send"));
                btnTypeCalculate->setToolTip(
                    QObject::tr("choosing type calculate"));

                //добавить аппаратуру источнику
                QLabel* label_SenderHard = new QLabel(wnd);
                label_SenderHard->setText(QObject::tr("Name hardware"));
                senderHardware = new QComboBox(wnd);
                layoutSender->addWidget(coordinate_sender->getWidget(), 0, 0, 1,
                                        2);
                layoutSender->addWidget(label_SenderHard, 1, 0, 1, 1);
                layoutSender->addWidget(senderHardware, 1, 1, 1, 1);

                //аппаратура у приемника
                QLabel* label_recvHard = new QLabel(wnd);
                label_recvHard->setText(QObject::tr("Name hardware"));
                recvierHardware = new QComboBox(wnd);

                layoutRecvier->addWidget(label_recvHard, 1, 0, 1, 1);
                layoutRecvier->addWidget(recvierHardware, 1, 1, 1, 1);
                recvierParam->setLayout(layoutRecvier);

                //радуис
                radius_widget = new QWidget(wnd);
                QGridLayout* grid_widget = new QGridLayout(wnd);

                QLabel* labelRadius = new QLabel();
                labelRadius->setText(QObject::tr("Radius:"));
                radius = new QSpinBox(wnd);
                radius->setValue(25);

                grid_widget->addWidget(labelRadius, 0, 0);
                grid_widget->addWidget(radius, 0, 1);
                radius_widget->setLayout(grid_widget);

                // дополнительные параметры: антенная система + климат
                layout4GroupBoxAdditionalParam = new QGridLayout(wnd);
                additonalParam = new QGroupBox(wnd);
                additonalParam->setTitle(QObject::tr("additinal param"));

                QLabel* label_antSystem = new QLabel(wnd);
                label_antSystem->setText(QObject::tr("name ant system"));
                antSystemHardware = new QComboBox(wnd);
                layout4GroupBoxAdditionalParam->addWidget(label_antSystem, 0, 0,
                                                          1, 1);
                layout4GroupBoxAdditionalParam->addWidget(antSystemHardware, 0,
                                                          1, 1, 1);

                QLabel* label_climate = new QLabel(wnd);
                label_climate->setText(QObject::tr("climate"));
                climat = new QComboBox(wnd);
                layout4GroupBoxAdditionalParam->addWidget(label_climate, 1, 0,
                                                          1, 1);
                layout4GroupBoxAdditionalParam->addWidget(climat, 1, 1, 1, 1);
                additonalParam->setLayout(layout4GroupBoxAdditionalParam);

                vbox->addWidget(btnTypeCalculate);

                break;
            }
            case stateRadiotrack::choosePointOnMap4VisCoverage:
            {
                senderParam->setTitle(QObject::tr("Location"));

                //добавить высоту антенны к источнику
                QLabel* labelHeightAnt = new QLabel(wnd);
                labelHeightAnt->setText(QObject::tr("Height:"));
                heightAntSend = new QSpinBox(wnd);
                heightAntSend->setValue(25);

                layoutSender->addWidget(coordinate_sender->getWidget(), 0, 0, 1,
                                        2);
                layoutSender->addWidget(labelHeightAnt, 1, 0, 1, 1);
                layoutSender->addWidget(heightAntSend, 1, 1, 1, 1);

                recvierParam->setTitle(QObject::tr("Object under study"));

                QLabel* labelHeightAntRec = new QLabel(wnd);
                labelHeightAntRec->setText(QObject::tr("Height:"));
                heightAntRec = new QSpinBox(wnd);
                heightAntRec->setValue(25);

                layoutRecvier->addWidget(labelHeightAntRec, 0, 0, 1, 1);
                layoutRecvier->addWidget(heightAntRec, 0, 1, 1, 1);
                recvierParam->setLayout(layoutRecvier);

                //радуис
                radius_widget = new QWidget(wnd);
                QGridLayout* grid_widget = new QGridLayout(wnd);

                QLabel* labelRadius = new QLabel();
                labelRadius->setText(QObject::tr("Radius:"));
                radius = new QSpinBox(wnd);
                radius->setValue(calcValueRadius(heightAntSend->value(),
                                                 heightAntRec->value()));
                grid_widget->addWidget(labelRadius, 0, 0);
                grid_widget->addWidget(radius, 0, 1);
                radius_widget->setLayout(grid_widget);

                connect(heightAntRec,
                        static_cast<void (QSpinBox::*)(int)>(
                            &QSpinBox::valueChanged),
                        [=](int value)
                        {
                            int heightAntRec_ = value;
                            int heightAntSend_ = heightAntSend->value();

                            radius->setValue(
                                calcValueRadius(heightAntSend_, heightAntRec_));
                        });

                connect(heightAntSend,
                        static_cast<void (QSpinBox::*)(int)>(
                            &QSpinBox::valueChanged),
                        [=](int value)
                        {
                            int heightAntSend_ = value;
                            int heightAntRec_ = heightAntRec->value();

                            radius->setValue(
                                calcValueRadius(heightAntSend_, heightAntRec_));
                        });

                break;
            }
        }

        senderParam->setLayout(layoutSender);

        vbox->addWidget(senderParam);
        vbox->addWidget(recvierParam);

        if (state_ == stateRadiotrack::choosePointsOnMap)
        {
            vbox->addWidget(additonalParam);
        }

        if (state_ == stateRadiotrack::choosePointOnMap4Coverage)
        {
            vbox->addWidget(radius_widget);
            vbox->addWidget(additonalParam);
        }

        if (state_ == stateRadiotrack::choosePointOnMap4VisCoverage)
        {
            vbox->addWidget(radius_widget);
        }

        wnd->setLayout(vbox);
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        std::pair<stateRadiotrack, QVariant> test;
        switch (state_)
        {
            case stateRadiotrack::choosePointsOnMap:
            {
                structures::paramForDrawing param4Drawing;
                param4Drawing.coordBeginStr =
                    coordinate_sender->getDataFromWidget();
                param4Drawing.coordEndStr =
                    coordinate_recvier->getDataFromWidget();
                param4Drawing.numberChoosingClimate = climat->currentIndex();
                param4Drawing.numberChoosingHardwareAntSystem =
                    antSystemHardware->currentIndex();
                param4Drawing.numberChoosingHardwareSender =
                    senderHardware->currentIndex();
                param4Drawing.numberChoosingHardwareRecvier =
                    recvierHardware->currentIndex();
                param4Drawing.coordBegin =
                    coordinate_sender->getCoordFromEdit();
                param4Drawing.coordEnd = coordinate_recvier->getCoordFromEdit();

                QVariant qvar_dataChoosePoint =
                    QVariant::fromValue(param4Drawing);

                stateRadiotrack nextState =
                    getNextState(state_, qvar_dataChoosePoint);
                if (nextState == stateRadiotrack::drawRt)
                {
                    test = {stateRadiotrack::drawRt, qvar_dataChoosePoint};
                }
                else
                {
                    QErrorMessage* errorMessage = new QErrorMessage();
                    errorMessage->showMessage(
                        QObject::tr("Coordinate of points are not interacted"));

                    test = {stateRadiotrack::choosePointsOnMap,
                            qvar_dataChoosePoint};
                }

                break;
            }
            case stateRadiotrack::choosePointOnMap4Coverage:
            {
                structures::coordInsideLineEdit coord =
                    coordinate_sender->getDataFromWidget();
                QVariant qvarCoord = QVariant::fromValue(coord);
                stateRadiotrack nextState = getNextState(
                    stateRadiotrack::choosePointOnMap4Coverage, qvarCoord);

                if (nextState == stateRadiotrack::drawCoverage)
                {
                    structures::paramForDrawing param;
                    param.coordBegin = coordinate_sender->getCoordFromEdit();
                    param.radius = radius->value();
                    param.numberChoosingHardwareSender =
                        senderHardware->currentIndex();
                    param.numberChoosingHardwareRecvier =
                        recvierHardware->currentIndex();
                    param.numberChoosingHardwareAntSystem =
                        antSystemHardware->currentIndex();
                    //перевод индекса в номер климата для функции itm_p2p_tls
                    param.numberChoosingClimate = climat->currentIndex() + 1;
                    QString typeCalculationInStr = btnTypeCalculate->text();
                    if (typeCalculationInStr
                        == QObject::tr("calculation make for send"))
                        param.type = structures::typeCalculation::on_send;
                    else
                        param.type = structures::typeCalculation::on_recv;

                    QVariant qvarParam = QVariant::fromValue(param);
                    test = {stateRadiotrack::drawCoverage, qvarParam};
                }
                else
                {
                    QErrorMessage* errorMessage = new QErrorMessage();
                    errorMessage->showMessage(
                        QObject::tr("Coordinate of points are not interacted"));

                    structures::paramForDrawing param;
                    param.coordBeginStr =
                        coordinate_sender->getDataFromWidget();
                    param.radius = radius->value();
                    param.numberChoosingHardwareSender =
                        senderHardware->currentIndex();
                    param.numberChoosingHardwareRecvier =
                        recvierHardware->currentIndex();

                    QVariant qvarParam = QVariant::fromValue(param);
                    test = {stateRadiotrack::choosePointOnMap4Coverage,
                            qvarParam};
                }

                break;
            }
            case stateRadiotrack::choosePointOnMap4VisCoverage:
            {
                structures::coordInsideLineEdit coord =
                    coordinate_sender->getDataFromWidget();

                QVariant qvarCoord = QVariant::fromValue(coord);

                stateRadiotrack nextState = getNextState(
                    stateRadiotrack::choosePointOnMap4VisCoverage, qvarCoord);

                if (nextState == stateRadiotrack::drawVisCoverage)
                {
                    structures::paramForDrawing param;
                    param.coordBegin = coordinate_sender->getCoordFromEdit();
                    param.radius = radius->value();
                    param.heightAntSend = heightAntSend->value();
                    param.heightAntRec = heightAntRec->value();
                    param.type = structures::typeCalculation::on_send;
                    QVariant qvarParam = QVariant::fromValue(param);
                    test = {stateRadiotrack::drawVisCoverage, qvarParam};
                }
                else
                {
                    QErrorMessage* errMessage = new QErrorMessage();
                    errMessage->showMessage(
                        QObject::tr("Coordinate of points are not interacted"));

                    structures::paramForDrawing param;
                    param.coordBeginStr =
                        coordinate_sender->getDataFromWidget();
                    param.radius = radius->value();
                    param.heightAntSend = heightAntSend->value();
                    param.heightAntRec = heightAntRec->value();

                    QVariant qvarParam = QVariant::fromValue(param);
                    test = {stateRadiotrack::choosePointOnMap4VisCoverage,
                            qvarParam};
                }
            }
        }

        return test;
    };

    ~intefaceChoosePointsOnMap()
    {
        delete wnd;
    };

private:
    int calcValueRadius(int h_ant_send, int h_ant_rec);

    void moveCoordinateWidget(QGridLayout* layoutSender,
                              QGridLayout* layoutRecv);

    QWidget* wnd;
    stateRadiotrack state_;
    QSpinBox* radius;
    QComboBox* senderHardware;
    QComboBox* recvierHardware;
    QGroupBox* senderParam;
    QGroupBox* recvierParam;
    QWidget* radius_widget;
    paramForInitialDataOnUnitsInterface paramInterface;
    QGridLayout* layout4GroupBoxAdditionalParam;
    QGroupBox* additonalParam;
    QComboBox* antSystemHardware;
    QComboBox* climat;
    QGridLayout* layoutSender;
    QGridLayout* layoutRecvier;
    QSpinBox* heightAntSend;
    QSpinBox* heightAntRec;

    ::widget::widgetCoordinate* coordinate_sender;
    ::widget::widgetCoordinate* coordinate_recvier;
    QPushButton* btnTypeCalculate;
};

inline int intefaceChoosePointsOnMap::calcValueRadius(int h_ant_send,
                                                      int h_ant_rec)
{
    int radius = 4 * (sqrt(h_ant_rec) + sqrt(h_ant_send));
    return radius;
}

inline void intefaceChoosePointsOnMap::moveCoordinateWidget(
    QGridLayout* layoutSender, QGridLayout* layoutRecv)
{
    if (btnTypeCalculate->text() == QObject::tr("calculation make for get"))
    {
        // layoutSender->removeWidget(coordinate_sender);
        layoutRecv->addWidget(coordinate_sender->getWidget(), 0, 0, 1, 2);
    }
    if (btnTypeCalculate->text() == QObject::tr("calculation make for send"))
    {
        // layoutRecv->removeWidget(coordinate_sender);
        layoutSender->addWidget(coordinate_sender->getWidget(), 0, 0, 1, 2);
    }
}
