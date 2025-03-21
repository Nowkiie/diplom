#pragma once
#include <core/mapcontrol.h>

#include "layermanager_req.h"

namespace qmapcontrol
{
class MapControl_req : public MapControl
{
    Q_OBJECT
public:
    MapControl_req(QSize size, QWidget* parent = NULL, MouseMode = Panning);
    ~MapControl_req();

    void paint_Image(QPointF coordinate, int zoom);
    void addLayer(Layer_req* layer);
signals:
    void tile_load(const QPixmap pixmap, int x, int y);

private:
    LayerManager_req* layermanager_req;
};
}  // namespace qmapcontrol
