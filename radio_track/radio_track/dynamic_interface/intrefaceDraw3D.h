#pragma once
#include "baseInterface.h"
#include "QtDataVisualization/Q3DSurface"
#include "../3d/surfaceGraph.h"
#include <QtGui/qscreen.h>
#include <QHBoxLayout>
#include "../calculate/calculateTile.h"
#include <QSlider>
#include <QVBoxLayout>

using namespace QtDataVisualization;

class interfaceDraw3d : public baseInterface
{
public:
    interfaceDraw3d(stateRadiotrack state)
    {
        state_ = state;
        workWithTile_ = std::make_shared<workWithTile>();
        createWidget(state_);
    };

    void createWidget(stateRadiotrack state)
    {
        wnd = new QWidget();
        graph = new Q3DSurface();
        container = QWidget::createWindowContainer(graph, this);
        QSize screensize = graph->screen()->size();

        sliderMinHeight = new QSlider(wnd);
        sliderMinHeight->setValue(0);
        sliderMinHeight->setRange(0, 200);
        sliderMinHeight->setMaximumSize(30, 120);
        sliderMinHeight->setMinimumSize(30, 120);

        sliderMaxHeight = new QSlider(wnd);
        sliderMaxHeight->setValue(2000);
        sliderMaxHeight->setRange(1000, 4000);
        sliderMaxHeight->setMaximumSize(30, 120);
        sliderMaxHeight->setMinimumSize(30, 120);

        QVBoxLayout* vbox;
        vbox = new QVBoxLayout();
        QLabel* minHeight = new QLabel(wnd);
        minHeight->setText("min");
        vbox->addWidget(minHeight);
        vbox->addWidget(sliderMinHeight);
        QWidget* minH = new QWidget;
        minH->setLayout(vbox);

        QVBoxLayout* vbox2;
        vbox2 = new QVBoxLayout();
        QLabel* maxHeight = new QLabel();
        maxHeight->setText("max");
        vbox2->addWidget(maxHeight);
        vbox2->addWidget(sliderMaxHeight);
        QWidget* maxH = new QWidget();
        maxH->setLayout(vbox2);

        QHBoxLayout* panelSetLayout = new QHBoxLayout();
        panelSetLayout->addWidget(minH);
        panelSetLayout->addWidget(maxH);

        panelSettings = new QWidget();
        panelSettings->setLayout(panelSetLayout);
        panelSettings->setMaximumSize(100, 200);
        panelSettings->setMinimumSize(100, 200);

        hbox = new QHBoxLayout();
        hbox->addWidget(panelSettings);
        hbox->addWidget(container, 0);
        wnd->setLayout(hbox);
    }

    QWidget* getWidget() override
    {
        return wnd;
    };

    bool setData(QVariant parametr1) override
    {
        paramWhenDraw3D paramFor3D = parametr1.value<paramWhenDraw3D>();

        QVector<track::tile> tiles = paramFor3D.tiles;
        QImage heights = paramFor3D.fileHeights;
        QImage texture = paramFor3D.fileTexture;

        modifier_ = std::make_unique<SurfaceGraph>(
            graph, tiles, heights, sliderMaxHeight, sliderMinHeight);

        geoCoordTileBegin = workWithTile_->posTileToGeoCoord(
            tiles[0].pos_x, tiles[0].pos_y, 11);

        geoCoordTileEnd = workWithTile_->posTileToGeoCoord(
            tiles[tiles.size() - 1].pos_x + 1,
            tiles[tiles.size() - 1].pos_y + 1, 11);

        combinedImageHeights = heights;
        combinedImageTexture = texture;

        modifier_->drawReliefForGeoCoord(graph, combinedImageTexture,
                                         combinedImageHeights,
                                         geoCoordTileBegin, geoCoordTileEnd);

        return true;
    };

    std::pair<stateRadiotrack, QVariant> getStateAndData() override
    {
        std::pair<stateRadiotrack, QVariant> newStateAndData = {
            stateRadiotrack::defau, ""};

        return newStateAndData;
    };

    ~interfaceDraw3d()
    {
        delete wnd;
    };

private:
    stateRadiotrack state_;
    Q3DSurface* graph;
    QWidget* container;
    QWidget* wnd;
    std::unique_ptr<SurfaceGraph> modifier_;
    QHBoxLayout* hbox;
    std::shared_ptr<workWithTile> workWithTile_;
    QPointF geoCoordTileBegin;
    QPointF geoCoordTileEnd;
    QImage combinedImageHeights;
    QImage combinedImageTexture;
    QSlider* sliderMaxHeight;
    QSlider* sliderMinHeight;

    QWidget* panelSettings;
    QGroupBox* decartCoord;
    QGroupBox* geoCoord;
};