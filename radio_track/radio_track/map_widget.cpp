#include "map_widget.h"
#include <QActionGroup>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <qpushbutton.h>

#include "extentions/CoordinateNetMapExtention.h"
#include "extentions/ScrollZoomMapExtention.h"
#include "extentions/ZoomInMapExtention.h"
#include "extentions/ZoomOutMapExtention.h"
#include "core/geometrylayer.h"
#include "core/maplayer.h"
#include "adapters/emptymapadapter.h"

#include "calculate/ToDegree.h"
#include "PelengCaption.h"
#include "request_tile/maplayer_req.h"

#include "qpixmap.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <qcolor.h>
#include <qrgb.h>

#include "earth_point.hpp"
#include "earth_functions.hpp"
using namespace track;

//#define DEBUG

MapWidget::MapWidget(QWidget* parent)
    : MapControl(QSize(100, 100))
    , netFactory_(this)
    , mapLayersGroup_(this)
    , extentionManager_(false, this)

{
    mapcontrolReq_ = new qmapcontrol::MapControl_req(QSize(100, 100));
    mapcontrolReqSat_ = new qmapcontrol::MapControl_req(QSize(100, 100));

    connect(mapcontrolReq_, &qmapcontrol::MapControl_req::tile_load, this,
            &MapWidget::tile_get);

    connect(mapcontrolReqSat_, &qmapcontrol::MapControl_req::tile_load, this,
            &MapWidget::tile_get);

    converter_ = std::make_unique<converter_toHeight>();
    workWithTile_ = std::make_unique<workWithTile>();

    MapWidget::initMap();
}

void MapWidget::tile_get(const QPixmap pixmap, int x, int y)
{
    if (pixmap.width() != 0)
    {
        if (!requestFor3D)
        {
            if (numberRequestTile
                != workWithTile_->getPointerOnVectorTile().size() - 1)
            {
                workWithTile_->setPixmapByCoordTile(x, y, pixmap,
                                                    typeMap::height);
                numberRequestTile++;
                requestMapControl();
            }
            else
            {
                workWithTile_->setPixmapByCoordTile(x, y, pixmap,
                                                    typeMap::height);
                emit loadingFinished();
            }
        }
        else
        {
            if (numberRequestTile
                != workWithTile_->getPointerOnVectorSatTile().size() - 1)
            {
                workWithTile_->setPixmapByCoordTile(x, y, pixmap, typeMap::sat);
                numberRequestTile++;
                requestMapControlForSat();
            }
            else
            {
                workWithTile_->setPixmapByCoordTile(x, y, pixmap, typeMap::sat);
                requestFor3D = false;
                emit loadingFinished();
            }
        }
    }
    else
    {
        value_height.push_back(0);
    }
}

QPoint MapWidget::getValueHeightAnt()
{
    int height_ant_send = workWithTile_->getValueHeight(0);
    int height_ant_rec = workWithTile_->getValueHeight(
        workWithTile_->getPointsOnCalcHeights().size() - 1);

    QPoint height_ant = {height_ant_send, height_ant_rec};
    return height_ant;
}

QVector<int>& MapWidget::calculateHeights(QVector<QPointF>& coord_points_track)
{
    workWithTile_->clearArrayHeights();
    for (auto coord : coord_points_track)
    {
        auto coord_px_common = workWithTile_->coordinateTodisplay(coord, 11);
        int pos_tile_y = coord_px_common.y() / 256;
        int pos_tile_x = coord_px_common.x() / 256;
        QPoint coord_tile = {pos_tile_x, pos_tile_y};
        auto coord_begin_tile = coord_tile * 256;
        auto coord_into_tile = coord_px_common - coord_begin_tile;
        workWithTile_->convertColorToHeight(coord_tile, coord_into_tile);
    }

    return workWithTile_->getPointsOnCalcHeights();
}

void MapWidget::clearHeights()
{
    value_height.clear();
}

QImage MapWidget::getFileTexture(QPointF coordPointSend, QPointF coordPointRec)
{
    return workWithTile_->makeCombinedImageSat(coordPointSend, coordPointRec);
}

QImage MapWidget::getFileHeights()
{
    return workWithTile_->makeCombinedImage();
}

void MapWidget::addMapButtonOnToolbar(QToolBar* toolBar)
{
    //иконка для выбора карты
    selectedMenu = new QMenu();
    QToolButton* view = new QToolButton();
    view->setIcon(QIcon(":/resources/icons/earth.ico"));
    view->setToolTip(tr("maps"));
    view->setMenu(selectedMenu);
    view->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(view);

    //иконка для отображения сетки
    QAction* grid = new QAction();
    grid->setIcon(QIcon(":/resources/icons/grid.png"));
    grid->setToolTip(tr("grid"));
    grid->setCheckable(true);
    grid->setChecked(true);
    mapExtentions_.coordinateNetExt->setChecked(true);

    //вкл-выкл сетку
    connect(grid, &QAction::triggered, this,
            [this](bool checked)
            {
                mapExtentions_.coordinateNetExt->setChecked(checked);
            });

    toolBar->addAction(grid);

    //QPushButton* radiotrack = new QPushButton();
}

void MapWidget::addTextOnEdit(QString text)
{
    //dit_coord->setText(text);
}

void MapWidget::drawPoint(QPointF coordinate)
{
    auto latitude = Helper::fromDegree(coordinate.y());
    auto longitude = Helper::fromDegree(coordinate.x());
    auto coordiante_str = PelengCaption::placeString(latitude, longitude);
    auto coordinate_point = PelengCaption::placePoint(latitude, longitude);

    beginPositionController_ = std::make_shared<BeginPosition>();
    beginPositionController_->setOwnPoint(coordinate_point);
    this->registerDrawController(beginPositionController_);
}

QVector<tile>& MapWidget::getPointerOnMatrixTile()
{
    return workWithTile_->getPointerOnVectorTile();
}

void MapWidget::clearPoint()
{
    if (beginPositionController_)
    {
        beginPositionController_->clearObjects();
        this->redrawControllerData(beginPositionController_);
    }
}

void MapWidget::clearCoverage()
{
    if (drawCoverage_)
    {
        drawCoverage_->clearObjects();
        this->redrawControllerData(drawCoverage_);
    }
    if (drawVisCoverage_)
    {
        drawVisCoverage_->clearObjects();
        this->redrawControllerData(drawVisCoverage_);
    }
}

void MapWidget::setActionToRuler(QAction* rulerAction)
{
    connect(rulerAction, &QAction::triggered, mapExtentions_.lenMeasureExt,
            &qmapcontrol::CheckableMapExtention::setChecked);
    connect(mapExtentions_.lenMeasureExt,
            &qmapcontrol::CheckableMapExtention::checkedChanged, rulerAction,
            &QAction::setChecked);
}

void MapWidget::setStatusLabel(QLabel* statusLabel)
{
    connect(mapExtentions_.cursorPosExt,
            qOverload<QString>(&qmapcontrol::CursorPosMapExtention::cursorPos),
            statusLabel, &QLabel::setText);
}

void MapWidget::makeRequestMatrixOfTiles(QPointF& coord_begin,
                                         QPointF& coord_end)
{
    workWithTile_->clearTiles();
    workWithTile_->calcMatrixTiles(coord_begin, coord_end, 11, typeMap::height);
    numberRequestTile = 0;
    requestMapControl();
}

void MapWidget::makeRequestMatrixOfTiles(QPointF& coord_right,
                                         QPointF& coord_up, QPointF& coord_left,
                                         QPointF& coord_down)
{
    workWithTile_->clearTiles();
    workWithTile_->calcMatrixTiles(coord_right, coord_up, coord_left,
                                   coord_down, 11);
    numberRequestTile = 0;
    requestMapControl();
}

void MapWidget::makeRequestTileFor3D(QPointF& coord_begin, QPointF& coord_end)
{
    numberRequestTile = 0;
    workWithTile_->clearSatTiles();
    workWithTile_->calcMatrixTiles(coord_begin, coord_end, 11, typeMap::sat);
    requestFor3D = true;
    requestMapControlForSat();
}

void MapWidget::registerDrawController(
    const ObjectDrawControllerPtr& controller)
{
    if (!controllersLayers_.count(controller->controllerName()))
    {
        const auto layer = new qmapcontrol::GeometryLayer(
            controller->controllerName(), new qmapcontrol::EmptyMapAdapter());
        controller->drawObjects(layer);
        this->addLayer(layer);
        controllersLayers_[controller->controllerName()] = layer;
    }
    else
    {
        controller->drawObjects(
            controllersLayers_[controller->controllerName()]);
    }
}

void MapWidget::redrawControllerData(const ObjectDrawControllerPtr& controller)
{
    if (controllersLayers_.count(controller->controllerName()))
    {
        const auto layer =
            controllersLayers_.value(controller->controllerName());
        layer->clearGeometries();
        controller->drawObjects(layer);
    }
}

void MapWidget::setControllerVisible(const ObjectDrawControllerPtr& controller,
                                     bool isVisible)
{
    if (controllersLayers_.count(controller->controllerName()))
    {
        const auto layer =
            controllersLayers_.value(controller->controllerName());
        layer->setVisible(isVisible);
    }
}

void MapWidget::unregisterDrawController(
    const ObjectDrawControllerPtr& controller)
{
    if (controllersLayers_.count(controller->controllerName()))
    {
        const auto layer =
            controllersLayers_.value(controller->controllerName());
        layer->clearGeometries();
        controller->clearObjects();
    }
}

MapWidget::~MapWidget()
{
    for (const auto& act : mapLayersGroup_.actions())
    {
        delete act;
    }
    delete mapcontrolReq_;

    //delete edit_coord;
    delete selectedMenu;

    delete mapExtentions_.coordinateNetExt;
    delete mapExtentions_.cursorPosExt;
    delete mapExtentions_.lenMeasureExt;
    delete mapExtentions_.switchMapExt;

    coord.clear();
    coord_px.clear();
    value_height.clear();
}

void MapWidget::initMap()
{
    using namespace qmapcontrol;
    createLayers();
    createExtentions();
    connect(
        &netFactory_, &MapNetworkFactory::mapConnected, this,
        [this](QString mapName, QString mapNameUi, int layerCount)
        {
            if (loadedMaps_.contains(mapName))
                return;
            loadedMaps_.push_back(mapName);
            auto* newAction = new QAction(mapNameUi, &mapLayersGroup_);
            newAction->setCheckable(true);

            if (mapSwitchToolbar_ != nullptr)
            {
                mapSwitchToolbar_->addAction(newAction);
            }

            selectedMenu->addAction(newAction);

            for (int l = 0; l < layerCount; l++)
            {
                auto* layer_req = new qmapcontrol::Maplayer_req(
                    "srtm", netFactory_.makeLoader("srtm", 0));

                auto* layerReqSat = new qmapcontrol::Maplayer_req(
                    "srtm", netFactory_.makeLoader("srtm", 0));

                auto* layer = new qmapcontrol::MapLayer(
                    mapName, netFactory_.makeLoader(mapName, l));

                layer->setVisible(false);
                this->addLayer(layer);
                mapcontrolReq_->addLayer(layer_req);
                mapcontrolReqSat_->addLayer(layerReqSat);
                mapExtentions_.switchMapExt->addLayerToAction(layer, newAction);
            }
            if (!firstMapLoaded_)
            {
                firstMapLoaded_ = true;
                newAction->toggle();
                newAction->trigger();
            }
        },
        Qt::QueuedConnection);
    netFactory_.startConnection();

    connect(this, &MapControl::mouseDoubleClickEvent, this,
            &MapWidget::MouseDoubleClickEvent);

    connect(this, &MapControl::mouseEventCoordinate, this,
            &MapWidget::MouseMoveEvent);
}

void MapWidget::drawingCoverage(weight& mapWeight)
{
    drawCoverage_ = std::make_shared<drawCoverage>();
    for (auto& w : mapWeight)
    {
        earth_math::earth_point a =
            earth_math::earth_point(w.second.y(), w.second.x());
        drawCoverage_->setOwnPoint(a, w.first);
        this->registerDrawController(drawCoverage_);
    }
}

void MapWidget::drawingVisCoverage(weight& mapWeight)
{
    drawVisCoverage_ = std::make_shared<drawVisCoverage>(130., 0.);
    for (auto& w : mapWeight)
    {
        earth_math::earth_point a =
            earth_math::earth_point(w.second.y(), w.second.x());
        drawVisCoverage_->setOwnPoint(a, w.first);
        this->registerDrawController(drawVisCoverage_);
    }
}

void MapWidget::drawCirclePoint(QPointF coordinate)
{
    auto latitude = Helper::fromDegree(coordinate.y());
    auto longitude = Helper::fromDegree(coordinate.x());
    auto coordiante_str = PelengCaption::placeString(latitude, longitude);
    auto coordinate_point = PelengCaption::placePoint(latitude, longitude);

    endCoveragePosController_ = std::make_shared<endCoveragePos>();
    endCoveragePosController_->setOwnPoint(coordinate_point);
    this->registerDrawController(endCoveragePosController_);
}

void MapWidget::requestMapControl()
{
    mapcontrolReq_->paint_Image(
        workWithTile_->getCoordTileByNumber(numberRequestTile, typeMap::height),
        11);
}

void MapWidget::requestMapControlForSat()
{
    mapcontrolReqSat_->paint_Image(
        workWithTile_->getCoordTileByNumber(numberRequestTile, typeMap::sat),
        11);
}

void MapWidget::createExtentions()
{
    using namespace qmapcontrol;
    mapExtentions_.switchMapExt = new LayerSwitchMapExtention(this, true, this);
    mapExtentions_.cursorPosExt = new CursorPosMapExtention(this, this);
    auto scrollZoomExt = new ScrollZoomMapExtention(this, this);
    auto zoomInExt = new ZoomInMapExtention(this, this);
    auto zoomOutExt = new ZoomOutMapExtention(this, this);
    mapExtentions_.coordinateNetExt = new CoordinateNetMapExtention(
        this, layers_.coordinateNetLayer, new CoordinateNetGeometry(), this);

    extentionManager_.AddExtention(mapExtentions_.switchMapExt);
    extentionManager_.AddExtention(scrollZoomExt);
    extentionManager_.AddExtention(zoomInExt);
    extentionManager_.AddExtention(zoomOutExt);
    extentionManager_.AddExtention(mapExtentions_.cursorPosExt);
    extentionManager_.AddExtention(mapExtentions_.coordinateNetExt);

    mapExtentions_.lenMeasureExt = new LengthMeasureMapExtention(
        this, layers_.lengthMeasureLayer, new MeasureGeometry(), this);
}

void MapWidget::createLayers()
{
    using namespace qmapcontrol;
    layers_.lengthMeasureLayer =
        new GeometryLayer("Length measure", new EmptyMapAdapter());
    layers_.coordinateNetLayer =
        new GeometryLayer("Coordinate net", new EmptyMapAdapter());

    this->addLayer(layers_.coordinateNetLayer);
    this->addLayer(layers_.lengthMeasureLayer);
}

bool MapWidget::checkMapInListLoadedMap(QString name)
{
    if (loadedMaps_.contains(name))
        return true;
    return false;
}
