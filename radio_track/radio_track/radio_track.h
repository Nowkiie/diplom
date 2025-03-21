#pragma once

//todo(PtakhovaA): fix include, change "" on <>

//todo(PtakhovaA): make dir and filters for file same
#include <QtWidgets/QMainWindow>
#include "ui_radio_track.h"
#include "SettingControll.h"

#include "3d/3dForm.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "calculate/calculatePoint.h"
#include "calculate/calc_coverage.h"
#include "calculate/coordinate.h"
#include "calculate/calculateTile.h"
#include "settings/settingsForm.h"
#include "dynamic_interface/dynamicInterface.h"
#include "dynamic_interface/factory.h"
#include "settings/tableModel.h"
#include "settings/paramNet.h"
#include "radio_track.h"
#include "calculate/calculationLosses.h"
#include "state.h"

using namespace settings;

namespace track
{
struct layerTilePos
{
    int x_pos;
    int y_pos;
};

class radio_track : public QMainWindow
{
    Q_OBJECT

public:
    radio_track(PSettingControl appSettings, QWidget* parent = Q_NULLPTR);

    ~radio_track() = default;

signals:
    void userChoosePointOnMap(QPointF coordPoint, int numberPoint);

private:
    Ui::radio_trackClass ui;
    std::unique_ptr<calculatePoint> calculatePoint_;
    std::shared_ptr<dynamicInterface> dynamicInterface_;
    std::shared_ptr<factoryInterface> factoryInterface_;
    QLabel* statLabel_;
    PSettingControl appSettings_;
    std::unique_ptr<visiable_coverage> calculateVis_;
    std::unique_ptr<Form> reliefForm_;
    std::unique_ptr<settingsForm> settForm_;
    std::unique_ptr<tableModel> tableData_;
    std::unique_ptr<paramNet> paramNet_;
    std::unique_ptr<coordinate> valueCoordinate_;
    std::unique_ptr<calculation::losses::calcLosses> calcLosses_;
    std::unique_ptr<coordinate> coordinate_;

    void closeEvent(QCloseEvent* event) override;

    void startCalculateRadiotrack();
    void calculateVisiableCoverage();

    void matchingDistancePointWithHeights(QVector<int>& height);

    void findMinCoord(QPointF& coord_begin, QPointF& coord_end);

    void updateInfoAboutHardware();

    void initialData();

    void checkAvailibityData();
    void createToolButton();
    void actionWithSettingsForm();

    void getCoordFromCoverageStruct(QVariant coverageStruct);

    void calcRefereancePoints();

    bool begin_operation = false;

    uint64_t count_point = 0;

    QPointF coordinate_point_begin;
    QPointF coordinate_point_end;

    int coord_x_px;
    int coord_y_px;

    QwtPlotCurve* curve_profileHeights = new QwtPlotCurve();
    QwtPlotCurve* curve_signal = new QwtPlotCurve();
    QwtPlotCurve* curve_zonePhrenel = new QwtPlotCurve();
    double distance_ = 0;

    QVector<QPointF> points;
    QVector<QPointF> points_f;
    QVector<QPointF> lineSignal;
    QVector<QPointF> points_phrenel;
    int height_ant_source = -1;
    int height_ant_rec = -1;

    int value_height_send;
    int value_height_rec;

    int number_ReferencePoint = 0;

    bool checked_coverage = false;
    bool visual_coverage = false;
    bool draw3D = false;

    double dist;

    QToolButton* panelRelief;
    QLabel* info;
    int heightAntSend = 0;
    int heightAntRec = 25;
    double power;
    double sens;
    double gain;
    double freq;
    int climate;
    polarization pol;
    structures::typeCalculation type_;

private slots:
};

}  // namespace track
