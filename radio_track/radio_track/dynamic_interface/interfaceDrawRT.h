#pragma once
#include <QLabel>

#include "baseInterface.h"
#include "qwt_plot.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <qwt_plot_curve.h>
#include "../calculate/calculatePoint.h"
#include "../structForSendParam.h"
#include "../calculate/calculationLosses.h"

class intefaceDrawRt : public baseInterface
{
    Q_OBJECT
public:
    intefaceDrawRt(stateRadiotrack state)
    {
        calcPoint_ = std::make_shared<track::calculatePoint>();
        calcLosses_ =
            std::make_shared<track::calculation::losses::calcLosses>();
        createWidget(state);

        connect(heightAntSend, QOverload<int>::of(&QSpinBox::valueChanged),
                [this](int value)
                {
                    redrawRt();
                });

        connect(heightAntRec, QOverload<int>::of(&QSpinBox::valueChanged),
                [this](int value)
                {
                    redrawRt();
                });

        connect(hardwareSender,
                QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this](int index)
                {
                    int range_freq = hardwares.send[index].sample_rate;
                    QString range_freq_text =
                        "{" + QString::number(range_freq) + ", "
                        + QString::number(range_freq) + "}";
                    rangeFreqValue->setText(range_freq_text);
                    currentValueFreq->setText(QString::number(range_freq));
                });
    };

    bool setData(QVariant parametr1) override
    {
        std::pair<stateRadiotrack, QVariant> link_state_data =
            parametr1.value<std::pair<stateRadiotrack, QVariant>>();

        stateRadiotrack state = link_state_data.first;
        switch (state)
        {
            case stateRadiotrack::initParamDrawRt:
            {
                hardwares = link_state_data.second.value<paramHardware>();

                for (auto const& sender : hardwares.send)
                {
                    hardwareSender->addItem(sender.name);
                }

                for (auto const& recvier : hardwares.recv)
                {
                    hardwareRecv->addItem(recvier.name);
                }

                for (auto const& antSystem : hardwares.ant_system)
                {
                    listNet->addItem(antSystem.name);
                }

                powerSender->setText(QString::number(
                    hardwares.send[hardwareSender->currentIndex()].power));

                sensRecvier->setText(QString::number(
                    hardwares.recv[hardwareRecv->currentIndex()].sensitivity));
                break;
            }
            case stateRadiotrack::outputResultCalculate:
            {
                paramResultCalculateRt resultCalculateRt =
                    link_state_data.second.value<paramResultCalculateRt>();

                profileHeights = resultCalculateRt.profileHeights;
                distance = resultCalculateRt.distances;
                freq = hardwares.send[hardwareSender->currentIndex()].sample_rate;

                lineSignal = calculateLineSignal(profileHeights, distance);
                calculatePointsPhrenel(lineSignal, distance,
                                       distance[distance.size() - 1], freq);
                matchingDistancePointWithHeights(profileHeights);

                drawRT(lineSignal, points, points_phrenel);
                outputCalculateLosses();
                curve->replot();

                break;
            }
            default:
            {
                //todo(PtakhovaA): write in log
                break;
            }
        }

        return true;
    };

    QWidget* getWidget() override
    {
        return wnd;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        std::pair<stateRadiotrack, QVariant> newStateAndData = {
            stateRadiotrack::defau, ""};

        return newStateAndData;
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();

        curve = new QwtPlot(wnd);

        //todo(PtakhovaA): rename widgets
        QLineEdit* hardwareSenderInfo = new QLineEdit(wnd);
        hardwareSenderInfo->setText(QObject::tr("Hardware name"));
        hardwareSenderInfo->setEnabled(false);
        hardwareSender = new QComboBox(wnd);
        QLineEdit* powerInfo = new QLineEdit(wnd);
        powerInfo->setText(QObject::tr("power sender (dBm)"));
        powerInfo->setEnabled(false);
        powerSender = new QLineEdit(wnd);
        powerSender->setEnabled(false);

        labelSend = new QLabel(wnd);
        labelSend->setText(QObject::tr("height ant (m)"));

        heightAntSend = new QSpinBox(wnd);
        heightAntSend->setValue(25);

        gainAntSendEdit = new QLineEdit(wnd);
        gainAntSendEdit->setEnabled(false);
        QLabel* labelGainSend = new QLabel(wnd);
        labelGainSend->setText(QObject::tr("gain"));

        groupBoxSend = new QGroupBox(wnd);
        groupBoxSend->setTitle(QObject::tr("sender"));
        QGridLayout* layoutGroupBoxSend = new QGridLayout(wnd);
        layoutGroupBoxSend->addWidget(hardwareSenderInfo, 0, 0);
        layoutGroupBoxSend->addWidget(hardwareSender, 0, 1);
        layoutGroupBoxSend->addWidget(powerInfo, 1, 0);
        layoutGroupBoxSend->addWidget(powerSender, 1, 1);
        layoutGroupBoxSend->addWidget(labelGainSend, 2, 0);
        layoutGroupBoxSend->addWidget(gainAntSendEdit, 2, 1);
        layoutGroupBoxSend->addWidget(labelSend, 3, 0);
        layoutGroupBoxSend->addWidget(heightAntSend, 3, 1);

        groupBoxSend->setLayout(layoutGroupBoxSend);

        QLineEdit* hardwareRecvierInfo = new QLineEdit(wnd);
        hardwareRecvierInfo->setText(QObject::tr("Hardware name"));
        hardwareRecvierInfo->setEnabled(false);
        hardwareRecv = new QComboBox(wnd);
        QLineEdit* sensInfo = new QLineEdit(wnd);
        sensInfo->setText(QObject::tr("sens recvier (dBm)"));
        sensInfo->setEnabled(false);
        sensRecvier = new QLineEdit(wnd);
        sensRecvier->setEnabled(false);
        labelRec = new QLabel(wnd);
        labelRec->setText(QObject::tr("height ant (m)"));

        heightAntRec = new QSpinBox(wnd);
        heightAntRec->setValue(25);

        gainAntRecEdit = new QLineEdit(wnd);
        gainAntRecEdit->setEnabled(false);
        QLabel* labelGainRec = new QLabel(wnd);
        labelGainRec->setText(QObject::tr("gain"));

        QGridLayout* layoutGroupBoxRec = new QGridLayout(wnd);
        layoutGroupBoxRec->addWidget(hardwareRecvierInfo, 0, 0);
        layoutGroupBoxRec->addWidget(hardwareRecv, 0, 1);
        layoutGroupBoxRec->addWidget(sensInfo, 1, 0);
        layoutGroupBoxRec->addWidget(sensRecvier, 1, 1);
        layoutGroupBoxRec->addWidget(labelGainRec, 2, 0);
        layoutGroupBoxRec->addWidget(gainAntRecEdit, 2, 1);
        layoutGroupBoxRec->addWidget(labelRec, 3, 0);
        layoutGroupBoxRec->addWidget(heightAntRec, 3, 1);

        groupBoxRec = new QGroupBox(wnd);
        groupBoxRec->setTitle(QObject::tr("Recvier"));
        groupBoxRec->setLayout(layoutGroupBoxRec);

        listNet = new QComboBox(wnd);
        groupBoxNet = new QGroupBox(wnd);
        groupBoxNet->setTitle(QObject::tr("Net"));
        QVBoxLayout* layoutGroupBoxNet = new QVBoxLayout(wnd);
        layoutGroupBoxNet->addWidget(listNet);
        groupBoxNet->setLayout(layoutGroupBoxNet);

        groupBoxFreq = new QGroupBox(wnd);
        groupBoxFreq->setTitle(QObject::tr("Freq (MHz)"));
        QLineEdit* rangeInfo = new QLineEdit(wnd);
        rangeInfo->setText(QObject::tr("range of acceptable value"));
        rangeInfo->setEnabled(false);
        rangeFreqValue = new QLineEdit(wnd);
        rangeFreqValue->setEnabled(false);
        QLineEdit* currentFreqInfo = new QLineEdit(wnd);
        currentFreqInfo->setText(QObject::tr("current value"));
        currentFreqInfo->setEnabled(false);
        currentValueFreq = new QLineEdit(wnd);
        QHBoxLayout* layoutFreqGroupBox = new QHBoxLayout(wnd);
        layoutFreqGroupBox->addWidget(rangeInfo);
        layoutFreqGroupBox->addWidget(rangeFreqValue);
        layoutFreqGroupBox->addWidget(currentFreqInfo);
        layoutFreqGroupBox->addWidget(currentValueFreq);
        groupBoxFreq->setLayout(layoutFreqGroupBox);

        QVBoxLayout* vbox = new QVBoxLayout(wnd);
        QGridLayout* hbox = new QGridLayout(wnd);

        hbox->addWidget(groupBoxSend, 0, 0);
        hbox->addWidget(groupBoxRec, 0, 1);
        hbox->addWidget(groupBoxNet, 1, 0);
        hbox->addWidget(groupBoxFreq, 1, 1);
        QWidget* panelSettingsAnt = new QWidget(wnd);
        panelSettingsAnt->setLayout(hbox);

        //param for info about A_db
        additionalInfo = new QGroupBox(wnd);
        additionalInfo->setTitle(QObject::tr("Additional info"));

        QGridLayout* layout_addionalInfo = new QGridLayout();

        powerEdit = new QLineEdit(wnd);
        powerEdit->setEnabled(false);
        sensEdit = new QLineEdit(wnd);
        sensEdit->setEnabled(false);
        lossesEdit = new QLineEdit(wnd);
        lossesEdit->setEnabled(false);

        layout_addionalInfo->addWidget(powerEdit, 0, 0, 1, 1);
        layout_addionalInfo->addWidget(sensEdit, 0, 1, 1, 1);
        layout_addionalInfo->addWidget(lossesEdit, 0, 2, 1, 1);

        additionalInfo->setLayout(layout_addionalInfo);

        vbox->addWidget(additionalInfo);
        vbox->addWidget(curve);
        vbox->addWidget(panelSettingsAnt);

        wnd->setLayout(vbox);
    };

    ~intefaceDrawRt()
    {
        profileHeights.clear();
        lineSignal.clear();
        points_phrenel.clear();
        delete wnd;
    };

private:
    QVector<QPointF> calculateLineSignal(const QVector<int>& profileHeights,
                                         const QVector<double>& distances)
    {
        int heightSend = profileHeights[0] + heightAntSend->value();
        int heightRec =
            profileHeights[profileHeights.size() - 1] + heightAntRec->value();

        QVector<QPointF> lineSignal =
            calcPoint_->calculatePointsTrack(distances, heightSend, heightRec);

        return lineSignal;
    }

    void calculatePointsPhrenel(QVector<QPointF> lineSignal,
                                const QVector<double>& distances,
                                double distance, double freq)
    {
        QVector<QPointF> points_f = calcPoint_->calculatePhrenelZone(
            lineSignal, distances, distance, freq);
        for (int i = 0; i < points_f.size(); i++)
        {
            double x = points_f[i].x();
            double y = points_f[i].y() + lineSignal[i].y();
            points_phrenel.push_back({x, y});
        }

        for (int i = 0; i < points_f.size(); i++)
        {
            double x = points_f[i].x();
            double y = lineSignal[i].y() - points_f[i].y();
            points_phrenel.push_back({x, y});
        }
    }

    void drawRT(QVector<QPointF> lineSignal, QVector<QPointF> profileHeights,
                QVector<QPointF> pointsPhrenel)
    {
        curve_lineSignal->setPen(Qt::red);
        curve_lineSignal->setSamples(lineSignal);
        curve_lineSignal->attach(curve);

        curve_profileHeights->setPen(Qt::green);
        curve_profileHeights->setSamples(profileHeights);
        curve_profileHeights->attach(curve);

        curve_zonePhrenel->setPen(Qt::black);
        curve_zonePhrenel->setSamples(pointsPhrenel);
        curve_zonePhrenel->attach(curve);
    }

    void redrawRt()
    {
        lineSignal.clear();
        lineSignal = calculateLineSignal(profileHeights, distance);
        points_phrenel.clear();
        calculatePointsPhrenel(lineSignal, distance,
                               distance[distance.size() - 1], freq);

        drawRT(lineSignal, points, points_phrenel);
        curve->replot();
    }

    void matchingDistancePointWithHeights(QVector<int>& height)
    {
        double k = 0;
        double H = 0;
        int R = 6371 * 2;
        double common_distance = distance[distance.size() - 1];
        for (int i = 0; i < distance.size(); i++)
        {
            //
            k = distance[i] / common_distance;
            H = 1000 * ((common_distance * common_distance / R) * k * (1 - k));
            points << QPointF(distance[i], height[i] + H);
        }
    }

    QVector<double> formItmProfile()
    {
        QVector<double> itmProfile{};
        std::transform(profileHeights.begin(), profileHeights.end(),
                       std::back_inserter(itmProfile),
                       [](int num)
                       {
                           return static_cast<double>(num);
                       });
        itmProfile.push_front(distance[distance.size() - 1]*1000/distance.size());
        itmProfile.push_front(profileHeights.size());
        return itmProfile;
    }

    void outputCalculateLosses()
    {
        QVector<double> profile = formItmProfile();

        double loss = calcLosses_->calculateLossesInItmModel(
            heightAntSend->value(), heightAntRec->value(),
            profile.toStdVector(), 4, freq,
            static_cast<int>(
                hardwares.ant_system[listNet->currentIndex()].typePolar));

        lossesEdit->setText(QObject::tr("Total loss:")+ QString::number(loss));
    }

    QWidget* wnd;
    QSpinBox* heightAntSend;
    QSpinBox* heightAntRec;
    QLabel* labelSend;
    QLabel* labelRec;
    QComboBox* hardwareSender;
    QComboBox* hardwareRecv;
    QLineEdit* powerSender;
    QLineEdit* sensRecvier;
    QGroupBox* groupBoxSend;
    QGroupBox* groupBoxRec;
    QGroupBox* groupBoxNet;
    QGroupBox* groupBoxFreq;
    QComboBox* listNet;
    QLineEdit* currentValueFreq;
    QLineEdit* rangeFreqValue;
    QwtPlot* curve;
    QwtPlotCurve* curve_profileHeights = new QwtPlotCurve();
    QwtPlotCurve* curve_lineSignal = new QwtPlotCurve();
    QwtPlotCurve* curve_zonePhrenel = new QwtPlotCurve();
    QLineEdit* powerEdit;
    QLineEdit* sensEdit;
    QLineEdit* gainAntSendEdit;
    QLineEdit* gainAntRecEdit;
    QLineEdit* lossesEdit;
    QGroupBox* additionalInfo;

    paramHardware hardwares;
    QVector<QPointF> lineSignal;
    QVector<int> profileHeights;
    QVector<QPointF> points_phrenel;
    QVector<double> distance;
    QVector<QPointF> points;
    double freq;

    std::shared_ptr<track::calculatePoint> calcPoint_;
    std::shared_ptr<track::calculation::losses::calcLosses> calcLosses_;
};
