#include "mapcontrol_req.h"

namespace qmapcontrol
{
MapControl_req::MapControl_req(QSize size, QWidget* parent, MouseMode mousemode)
    : MapControl(size, parent, mousemode)
{
    layermanager_req = new LayerManager_req(this, size);

    connect(layermanager_req, &LayerManager_req::tile_load, this,
            &MapControl_req::tile_load, Qt::QueuedConnection);
}

void MapControl_req::paint_Image(QPointF coordinate, int zoom)
{
    layermanager_req->request_Image(coordinate, zoom);
}

void MapControl_req::addLayer(Layer_req* layer)
{
    layermanager_req->addLayer(layer);
}

MapControl_req::~MapControl_req()
{
    delete layermanager_req;
}
}  // namespace qmapcontrol