#include "layermanager_req.h"

using namespace qmapcontrol;

LayerManager_req::LayerManager_req(MapControl* mapcontrol, QSize size)
    : LayerManager(mapcontrol, size)
{
}

void LayerManager_req::addLayer(Layer_req* layer)
{
    mylayers.append(layer);

    connect(layer, &Layer_req::tile_load, this, &LayerManager_req::tile_load,
            Qt::QueuedConnection);
}

void LayerManager_req::request_Image(QPointF coordinate, int zoom)
{
    QPainter imagePainter(&composedOffscreenImage);
    Layer_req* l = mylayers.at(0);
    if (l->isVisible())
    {
        if (l->layertype() == Layer::MapLayer)
        {
            l->get_Pixmap(&imagePainter, coordinate, zoom);
        }
    }
}

LayerManager_req::~LayerManager_req()
{
    for (const auto& layers : mylayers)
    {
        delete layers;
    }
}