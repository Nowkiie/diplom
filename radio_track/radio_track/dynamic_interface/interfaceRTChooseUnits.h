#pragma once
#include "baseInterface.h"
#include "../state.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include "../structForSendParam.h"
#include "../dynamic_interface/paramsList.h"

class interfaceChooseUnits : public baseInterface
{
public:
    interfaceChooseUnits(stateRadiotrack state)
    {
        state_ = state;
        createWidget(state_);
    }

    QWidget* getWidget() override
    {
        return wnd;
    };

    bool setData(QVariant parametr) override
    {
        param = parametr.value<paramForInitialDataOnUnitsInterface>();
        // QVector<unit> units = parametr.value<QVector<unit>>();
        for (auto el : param.units)
        {
            switch (state_)
            {
                case stateRadiotrack::chooseUnits:
                {
                    selectFirstUnit->addItem(el.name);
                    selectSecondUnit->addItem(el.name);
                    break;
                }
                case stateRadiotrack::chooseUnit4Coverage:
                {
                    if (el.hardware_.send.name != "-")
                    {
                        selectFirstUnit->addItem(el.name);
                    }
                    if (el.hardware_.rec.name != "-")
                    {
                        selectSecondUnit->addItem(el.name);
                    }
                    break;
                }
                case stateRadiotrack::chooseUnit4VisCoverage:
                {
                    selectFirstUnit->addItem(el.name);
                    break;
                }
                default:
                    break;
            }
        }
        if (state_ == stateRadiotrack::chooseUnit4Coverage)
        {
            setVisibleDependingOnType();
            for (auto el : param.senders)
            {
                senderHardware->addItem(el.name);
            }

            for (auto el : param.recviers)
            {
                recvierHardware->addItem(el.name);
            }

            for (auto el : param.antSystems)
            {
                antSystemHardware->addItem(el.name);
            }

            climat->addItems(climateParams::getClimateList());
            climat->setCurrentIndex(
                climateParams::climateList::continental_temperate);
        }

        if (state_ == stateRadiotrack::chooseUnit4Coverage)
        {
            radius->setValue(calcValueRadius(
                param.units[selectFirstUnit->currentIndex()]
                    .hardware_.send.heightAnt,
                param.recviers[recvierHardware->currentIndex()].heightAnt));

            connect(selectFirstUnit,
                    static_cast<void (QComboBox::*)(int)>(
                        &QComboBox::currentIndexChanged),
                    [=](int value)
                    {
                        int sender_heightAnt =
                            param.units[value].hardware_.send.heightAnt;
                        int recv_heightAnt =
                            param.recviers[recvierHardware->currentIndex()]
                                .heightAnt;
                        radius->setValue(
                            calcValueRadius(sender_heightAnt, recv_heightAnt));
                    });

            connect(recvierHardware,
                    static_cast<void (QComboBox::*)(int)>(
                        &QComboBox::currentIndexChanged),
                    [=](int value)
                    {
                        int recv_heightAnt = param.recviers[value].heightAnt;
                        int sender_heightAnt =
                            param.units[selectFirstUnit->currentIndex()]
                                .hardware_.send.heightAnt;
                        radius->setValue(
                            calcValueRadius(sender_heightAnt, recv_heightAnt));
                    });

            connect(btnTypeCalculate, &QPushButton::clicked,
                    [this](bool clicked)
                    {
                        if (btnTypeCalculate->text()
                            == QObject::tr("calculation make for send"))
                        {
                            btnTypeCalculate->setText(
                                QObject::tr("calculation make for get"));
                            setVisibleDependingOnType();
                        }
                        else
                        {
                            btnTypeCalculate->setText(
                                QObject::tr("calculation make for send"));
                            setVisibleDependingOnType();
                        }
                    });
        }

        return true;
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();

        senderParam = new QGroupBox(wnd);
        senderParam->setTitle(QObject::tr("Sender"));
        layoutSender = new QGridLayout(wnd);

        labelSendPoint = new QLabel(wnd);
        labelSendPoint->setText(QObject::tr("Name unit:"));
        selectFirstUnit = new QComboBox(wnd);

        layoutSender->addWidget(labelSendPoint, 0, 0, 1, 1);
        layoutSender->addWidget(selectFirstUnit, 0, 1, 1, 1);

        senderParam->setLayout(layoutSender);

        QVBoxLayout* vbox = new QVBoxLayout(wnd);

        layoutRecvier = new QGridLayout(wnd);
        recvierParam = new QGroupBox(wnd);
        recvierParam->setTitle(QObject::tr("recvier"));

        switch (state)
        {
            case stateRadiotrack::chooseUnits:
            {
                selectSecondUnit = new QComboBox(wnd);
                QLabel* labelRecPoint = new QLabel(wnd);
                labelRecPoint->setText(QObject::tr("Name recv:"));
                layoutRecvier->addWidget(labelRecPoint, 0, 0);
                layoutRecvier->addWidget(selectSecondUnit, 0, 1);
                break;
            }
            case stateRadiotrack::chooseUnit4Coverage:
            {
                btnTypeCalculate = new QPushButton(wnd);
                btnTypeCalculate->setText(
                    QObject::tr("calculation make for send"));
                vbox->addWidget(btnTypeCalculate);

                //аппаратура для передатчика
                labelSendHardware = new QLabel(wnd);
                labelSendHardware->setText(QObject::tr("Name hardware"));
                senderHardware = new QComboBox(wnd);

                layoutSender->addWidget(labelSendHardware, 1, 0);
                layoutSender->addWidget(senderHardware, 1, 1);

                //пункты для приемника
                labelRecPoint = new QLabel(wnd);
                labelRecPoint->setText(QObject::tr("Name unit"));
                selectSecondUnit = new QComboBox(wnd);

                //аппаратура для приемника
                labelRecHardware = new QLabel(wnd);
                labelRecHardware->setText(QObject::tr("Name hardware"));
                recvierHardware = new QComboBox(wnd);

                layoutRecvier->addWidget(labelRecPoint, 0, 0);
                layoutRecvier->addWidget(selectSecondUnit, 0, 1);
                layoutRecvier->addWidget(labelRecHardware, 1, 0);
                layoutRecvier->addWidget(recvierHardware, 1, 1);

                radius = new QSpinBox();
                radius->setValue(25);

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
                break;
            }
            case stateRadiotrack::chooseUnit4VisCoverage:
            {
                senderParam->setTitle(QObject::tr("Location"));

                QLabel* labelHeightAntSend = new QLabel(wnd);
                labelHeightAntSend->setText(QObject::tr("Height:"));
                heightAntSend = new QSpinBox(wnd);
                heightAntSend->setValue(25);

                layoutSender->addWidget(labelHeightAntSend, 1, 0, 1, 1);
                layoutSender->addWidget(heightAntSend, 1, 1, 1, 1);

                recvierParam->setTitle(QObject::tr("Object under study"));
                QLabel* labelHeightAntRec = new QLabel(wnd);
                labelHeightAntRec->setText(QObject::tr("Height:"));
                heightAntRec = new QSpinBox(wnd);
                heightAntRec->setValue(25);

                layoutRecvier->addWidget(labelHeightAntRec, 0, 0, 1, 1);
                layoutRecvier->addWidget(heightAntRec, 0, 1, 1, 1);
                recvierParam->setLayout(layoutRecvier);

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

                connect(heightAntRec,
                        static_cast<void (QSpinBox::*)(int)>(
                            &QSpinBox::valueChanged),
                        [=](int value)
                        {
                            int heightAntSend_ = heightAntSend->value();
                            int heightAtRec_ = value;
                            radius->setValue(
                                calcValueRadius(heightAntSend_, heightAtRec_));
                        });

                break;
            }
        }

        vbox->addWidget(senderParam);
        recvierParam->setLayout(layoutRecvier);
        vbox->addWidget(recvierParam);
        if (state_ == stateRadiotrack::chooseUnit4Coverage)
        {
            vbox->addWidget(radius_widget);
            vbox->addWidget(additonalParam);
        }
        if (state_ == stateRadiotrack::chooseUnit4VisCoverage)
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
            case stateRadiotrack::chooseUnits:
            {
                paramWhenUseUnits paramUnits;
                paramUnits.numberFirstUnit = selectFirstUnit->currentIndex();
                paramUnits.numberSecondUnit = selectSecondUnit->currentIndex();
                QVariant qvar_param = QVariant::fromValue(paramUnits);
                stateRadiotrack nextState =
                    getNextState(stateRadiotrack::chooseUnits, qvar_param);
                if (nextState == stateRadiotrack::chooseUnits)
                {
                    QErrorMessage* errMessage = new QErrorMessage;
                    errMessage->showMessage(QObject::tr(
                        "uncorrect entered data: units must not match"));
                }
                test = {nextState, qvar_param};
                break;
            }
            case stateRadiotrack::chooseUnit4Coverage:
            {
                paramForDrawCoverageWithUnit paramUnits;

                int count = 0;
                //перевод
                for (int i = 0; i < param.units.size(); i++)
                {
                    if (btnTypeCalculate->text()
                        == QObject::tr("calculation make for get"))
                    {
                        if (param.units[i].hardware_.rec.name != "-")
                        {
                            if (count == selectSecondUnit->currentIndex())
                            {
                                paramUnits.numberUnit = i;
                                paramUnits.type =
                                    structures::typeCalculation::on_recv;
                                paramUnits.numberChoosingHardwareSender =
                                    senderHardware->currentIndex();
                                break;
                            }
                            count++;
                        }
                    }
                    if (btnTypeCalculate->text()
                        == QObject::tr("calculation make for send"))
                    {
                        if (param.units[i].hardware_.send.name != "-")
                        {
                            if (count == selectFirstUnit->currentIndex())
                            {
                                paramUnits.numberUnit = i;
                                paramUnits.type =
                                    structures::typeCalculation::on_send;
                                paramUnits.numberChoosingHardwareRecvier =
                                    recvierHardware->currentIndex();
                                break;
                            }
                            count++;
                        }
                    }
                }

                paramUnits.radius = radius->value();
                paramUnits.numberChoosingClimate = climat->currentIndex();
                paramUnits.numberChoosingHardwareAntSystem =
                    antSystemHardware->currentIndex();
                QVariant qvar_param = QVariant::fromValue(paramUnits);
                test = {stateRadiotrack::drawCoverage, qvar_param};
                break;
            }
            case stateRadiotrack::chooseUnit4VisCoverage:
            {
                paramForDrawCoverageWithUnit paramUnits;
                paramUnits.numberUnit = selectFirstUnit->currentIndex();
                paramUnits.radius = radius->value();
                paramUnits.heightAntSend = heightAntSend->value();
                paramUnits.heightAntRec = heightAntRec->value();
                paramUnits.type = structures::typeCalculation::on_send;
                QVariant qvar_param = QVariant::fromValue(paramUnits);
                test = {stateRadiotrack::drawVisCoverage, qvar_param};

                break;
            }
        }

        return test;
    };

    ~interfaceChooseUnits()
    {
        delete wnd;
    };

private:
    int calcValueRadius(int send_heightAnt, int rec_heightAnt);

    void setVisibleDependingOnType();

    QWidget* wnd;
    QComboBox* selectFirstUnit;
    QComboBox* selectSecondUnit;
    QSpinBox* radius;
    QWidget* radius_widget;
    stateRadiotrack state_;
    QComboBox* recvierHardware;
    QComboBox* senderHardware;
    QGroupBox* recvierParam;
    QGroupBox* senderParam;
    QGridLayout* layout4GroupBoxAdditionalParam;
    QGroupBox* additonalParam;
    QComboBox* antSystemHardware;
    QComboBox* climat;
    paramForInitialDataOnUnitsInterface param;
    QLabel* labelSendPoint;
    QPushButton* btnTypeCalculate;
    QGridLayout* layoutSender;
    QGridLayout* layoutRecvier;
    QLabel* labelRecHardware;
    QLabel* labelSendHardware;
    QLabel* labelRecPoint;
    QSpinBox* heightAntRec;
    QSpinBox* heightAntSend;
};

inline int interfaceChooseUnits::calcValueRadius(int send_heightAnt,
                                                 int rec_heightAnt)
{
    int radius = 4 * (sqrt(send_heightAnt) + sqrt(rec_heightAnt));
    return radius;
}

inline void interfaceChooseUnits::setVisibleDependingOnType()
{
    if (btnTypeCalculate->text() == QObject::tr("calculation make for get"))
    {
        labelSendHardware->setVisible(true);
        senderHardware->setVisible(true);

        labelSendPoint->setVisible(false);
        selectFirstUnit->setVisible(false);

        labelRecHardware->setVisible(false);
        recvierHardware->setVisible(false);

        labelRecPoint->setVisible(true);
        selectSecondUnit->setVisible(true);
    }
    if (btnTypeCalculate->text() == QObject::tr("calculation make for send"))
    {
        labelSendHardware->setVisible(false);
        senderHardware->setVisible(false);

        labelSendPoint->setVisible(true);
        selectFirstUnit->setVisible(true);

        labelRecHardware->setVisible(true);
        recvierHardware->setVisible(true);

        labelRecPoint->setVisible(false);
        selectSecondUnit->setVisible(false);
    }
}
