#pragma once
#include <core/layermanager.h>
#include "layer_req.h"

namespace qmapcontrol
{
//class MapControl_req;

class LayerManager_req : public LayerManager
{
    Q_OBJECT
public:
    LayerManager_req(MapControl*, QSize);
    ~LayerManager_req();
    void request_Image(QPointF coordinate, int zoom);

    void addLayer(Layer_req* layer);
signals:
    void tile_load(const QPixmap pixmap, int x, int y);

private:
    QPixmap composedOffscreenImage;
    QList<Layer_req*> mylayers;
};
}  // namespace qmapcontrol
