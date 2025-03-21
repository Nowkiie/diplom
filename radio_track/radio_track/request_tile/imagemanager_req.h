#pragma once
#include <core/imagemanager.h>

namespace qmapcontrol
{
class ImageManager_req : public ImageManager
{
    Q_OBJECT
public:
    ImageManager_req(MapLoader* loader, QObject* parent = 0);
    ~ImageManager_req();
    QPixmap getImage(int x, int y, int z) override;
    void save_coordTile(int x, int y, int z);
private slots:
    void image_loaded(const QPixmap pixmap, int x, int y, int z);
    void image_empty(int x, int y, int z);

signals:
    void tile_load(const QPixmap pixmap, int x, int y);

private:
    MapLoader* loader;
    QPixmap emptyPixmap;

    int coord_x;
    int coord_y;
    int coord_z;

    bool wait_tile = false;
};
}  // namespace qmapcontrol
