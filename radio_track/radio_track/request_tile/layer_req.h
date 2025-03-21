#pragma once
#include <core/layer.h>
#include <adapters/mapadapter.h>
#include "imagemanager_req.h"

namespace qmapcontrol
{
class Layer_req : public Layer
{
    Q_OBJECT
public:
    Layer_req(QString layername, MapAdapter* mapAdapter, MapLoader* mapLoader,
              enum LayerType layertype, bool takeevents = true);
    ~Layer_req();
    void get_Pixmap(QPainter* painter, QPointF coordinate, int zoom);

signals:
    void tile_load(const QPixmap pixmap, int x, int y);

private:
    ImageManager_req* imagemanager_req;
};
}  // namespace qmapcontrol
