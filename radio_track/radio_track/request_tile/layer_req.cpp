#include "layer_req.h"

using namespace qmapcontrol;

Layer_req::Layer_req(QString layername, MapAdapter* mapAdapter,
                     MapLoader* mapLoader, enum LayerType layertype,
                     bool takeevents)
    : Layer(layername, mapAdapter, mapLoader, layertype, takeevents)

{
    imagemanager_req = new ImageManager_req(mapLoader);

    connect(imagemanager_req, &ImageManager_req::tile_load, this,
            &Layer_req::tile_load);
}

void Layer_req::get_Pixmap(QPainter* painter, QPointF coordinate, int zoom)
{
    QPixmap pixmap;
    imagemanager_req->save_coordTile(coordinate.x(), coordinate.y(), zoom);
    pixmap = imagemanager_req->getImage(coordinate.x(), coordinate.y(), zoom);
}

Layer_req::~Layer_req() {}