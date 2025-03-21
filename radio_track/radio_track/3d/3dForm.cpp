#include "3dForm.h"

using namespace track;

Form::Form()
{
    form.setupUi(this);
    graph = new Q3DSurface();
    container = QWidget::createWindowContainer(graph, this);
    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(
        QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);

    container->setFocusPolicy(Qt::StrongFocus);
    //form.verticalLayout->addWidget(container,0);
    workWithTile_ = std::make_unique<workWithTile>();
    form.horizontalLayout->addWidget(container, 0);

    form.sliderMaxHeight->setValue(2000);
    form.sliderMinHeight->setValue(0);
    form.radioButtonGeo->setChecked(true);

    valueCoord_ = std::make_unique<coordinate>();

    connect(form.sliderMinHeight, &QSlider::valueChanged,
            [this](int value)
            {
                graph->axisY()->setRange(value, form.sliderMaxHeight->value());
            });

    connect(form.sliderMaxHeight, &QSlider::valueChanged,
            [this](int value)
            {
                graph->axisY()->setRange(form.sliderMinHeight->value(), value);
            });

    connect(form.radioButtonGeo, &QRadioButton::clicked,
            [this](bool clicked)
            {
                modifier->drawReliefForGeoCoord(
                    graph, combinedImageTexture, combinedImageHeights,
                    geoCoordTileBegin, geoCoordTileEnd);
            });

    connect(form.radioButtonDecart, &QRadioButton::clicked,
            [this](bool clicked)
            {
                QPointF decartCoordTileBegin =
                    valueCoord_->geoCoordToDecart(geoCoordTileBegin);

                QPointF decartCoordTileEnd =
                    valueCoord_->geoCoordToDecart(geoCoordTileEnd);

                modifier->drawReliefForDecartCoord(
                    graph, combinedImageTexture, combinedImageHeights,
                    decartCoordTileBegin, decartCoordTileEnd);
            });
}

void Form::closeEvent(QCloseEvent* evnt)
{
    modifier->clearSeries(graph);
    emit workWith3DEnd();
}

Form::~Form() {}

void Form::createComponetes(QVector<tile>& tiles, QImage heights,
                            QImage texture)
{
    modifier = std::make_unique<SurfaceGraph>(
        graph, tiles, heights, form.sliderMaxHeight, form.sliderMinHeight);

    geoCoordTileBegin =
        workWithTile_->posTileToGeoCoord(tiles[0].pos_x, tiles[0].pos_y, 11);

    geoCoordTileEnd =
        workWithTile_->posTileToGeoCoord(tiles[tiles.size() - 1].pos_x + 1,
                                         tiles[tiles.size() - 1].pos_y + 1, 11);

    combinedImageHeights = heights;
    combinedImageTexture = texture;

    if (form.radioButtonGeo->isChecked())
    {
        modifier->drawReliefForGeoCoord(graph, combinedImageTexture,
                                        combinedImageHeights, geoCoordTileBegin,
                                        geoCoordTileEnd);
    }
    else
    {
        QPointF decartCoordTileBegin =
            valueCoord_->geoCoordToDecart(geoCoordTileBegin);

        QPointF decartCoordTileEnd =
            valueCoord_->geoCoordToDecart(geoCoordTileEnd);

        modifier->drawReliefForDecartCoord(
            graph, combinedImageTexture, combinedImageHeights,
            decartCoordTileBegin, decartCoordTileEnd);
    }
}

void Form::clearComponents() {}
