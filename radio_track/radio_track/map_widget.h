#pragma once

#include <QActionGroup>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QMenu>
#include <QLineEdit>

#include "core/mapnetworkfactory.h"
#include "extentions/MapExtentionManager.h"
#include "extentions/lengthmeasuremapextention.h"
#include "extentions/layerswitchmapextention.h"
#include "extentions/coordinatenetmapextention.h"
#include "extentions/CursorPosMapExtention.h"

#include "draw_geometry/ObjectDrawController.h"
#include "draw_geometry/BeginPosition.h"
#include "draw_geometry/endCoveragePos.h"
#include "draw_geometry/drawCoverage.h"
#include "draw_geometry/drawVisCoverage.h"

#include "calculate/ToDegree.h"
#include "PelengCaption.h"

#include "core/imagemanager.h"
#include "core/maploader.h"

#include <core/mapcontrol.h>
#include "request_tile/mapcontrol_req.h"

#include "calculate/color_height.h"
#include "commonType.h"
#include "calculate/calculateTile.h"

namespace track
{
class MapWidget : public qmapcontrol::MapControl
{
    Q_OBJECT
signals:
    //void MouseMoveEvent(QMouseEvent* evnt, QPointF coordinate);
    void MouseDoubleClickEvent(QMouseEvent* evnt, QPointF coordinate);
    void loadingFinished();
    void MouseMoveEvent(const QMouseEvent* evnt, const QPointF coordinate);

public:
    MapWidget(QWidget* parent);
    void addMapButtonOnToolbar(QToolBar* toolBar);
    void setActionToRuler(QAction* rulerAction);
    void setStatusLabel(QLabel* statusLabel);
    void registerDrawController(const ObjectDrawControllerPtr& controller);
    void redrawControllerData(const ObjectDrawControllerPtr& controller);
    void setControllerVisible(const ObjectDrawControllerPtr& controller,
                              bool isVisible);
    void unregisterDrawController(const ObjectDrawControllerPtr& controller);
    bool checkMapInListLoadedMap(QString name);
    ~MapWidget();

    /// <summary>
    /// отрисовка выбранной точки на карте
    /// </summary>
    /// <param name="coordinate">координаты точки</param>
    void drawPoint(QPointF coordinate);

    /// <summary>
    /// отрисовка
    /// </summary>
    /// <param name="coordinate"></param>
    void drawCirclePoint(QPointF coordinate);

    void clearPoint();
    void drawingCoverage(weight& mapWeight);
    void drawingVisCoverage(weight& mapWeight);
    void clearCoverage();

    void requestMapControl();
    void requestMapControlForSat();

    QLineEdit* edit_coord;

    void clearHeights();

    void addTextOnEdit(QString text);

    void makeRequestMatrixOfTiles(QPointF& coord_begin, QPointF& coord_end);
    void makeRequestMatrixOfTiles(QPointF& coord_right, QPointF& coord_up,
                                  QPointF& coord_left, QPointF& coord_down);
    void makeRequestTileFor3D(QPointF& coord_begin, QPointF& coord_end);
    QVector<int>& calculateHeights(QVector<QPointF>& coord_points_track);
    QPoint getValueHeightAnt();
    QVector<tile>& getPointerOnMatrixTile();
    QImage getFileTexture(QPointF coordPointSend, QPointF coordPointRec);
    QImage getFileHeights();

private:
    QVector<QPoint> coord_tile;
    qmapcontrol::MapNetworkFactory netFactory_;
    QStringList loadedMaps_;
    QActionGroup mapLayersGroup_;
    qmapcontrol::MapExtentionManager extentionManager_;
    QToolBar* mapSwitchToolbar_ = nullptr;
    struct MapExtentions
    {
        qmapcontrol::LayerSwitchMapExtention* switchMapExt;
        qmapcontrol::LengthMeasureMapExtention* lenMeasureExt;
        qmapcontrol::CursorPosMapExtention* cursorPosExt;
        qmapcontrol::CoordinateNetMapExtention* coordinateNetExt;
    } mapExtentions_{};
    struct MapLayers
    {
        qmapcontrol::Layer* lengthMeasureLayer;
        qmapcontrol::Layer* coordinateNetLayer;
    } layers_{};
    bool firstMapLoaded_ = false;
    QMap<QString, qmapcontrol::Layer*> controllersLayers_;
    virtual void initMap();
    virtual void createExtentions();
    virtual void createLayers();

    QMenu* selectedMenu;

    std::shared_ptr<BeginPosition> beginPositionController_;
    std::shared_ptr<BeginPosition> endPositionController_;
    std::shared_ptr<endCoveragePos> endCoveragePosController_;
    std::shared_ptr<drawCoverage> drawCoverage_;
    std::shared_ptr<drawVisCoverage> drawVisCoverage_;

    uint8_t count = 0;

    qmapcontrol::MapControl_req* mapcontrolReq_;
    qmapcontrol::MapControl_req* mapcontrolReqSat_;
    std::unique_ptr<workWithTile> workWithTile_;
    QVector<QPointF> coord;
    QVector<QPoint> coord_px;

    std::unique_ptr<converter_toHeight> converter_;
    QVector<int> value_height;

    int numberRequestTile = 0;
    bool requestFor3D = false;
    ;
private slots:
    void tile_get(const QPixmap pixmap, int x, int y);
};
}  // namespace track
