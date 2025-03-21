#include "imagemanager_req.h"
#include <core/urlconverter.h>

using namespace qmapcontrol;

ImageManager_req::ImageManager_req(MapLoader* loader, QObject* parent)
    : ImageManager(loader, parent)
    , loader(loader)
{
    connect(loader, &MapLoader::imageLoaded, this,
            &ImageManager_req::image_loaded);

    connect(loader, &MapLoader::imageEmpty, this,
            &ImageManager_req::image_empty);
}

void ImageManager_req::image_empty(int x, int y, int z)
{
    if (x == coord_x && y == coord_y && z == coord_z)
    {
        emit tile_load(emptyPixmap, x, y);
    }
}

void ImageManager_req::image_loaded(const QPixmap pixmap, int x, int y, int z)
{
    if (x == coord_x && y == coord_y && z == coord_z)
    {
        emit tile_load(pixmap, x, y);
    }
}

void ImageManager_req::save_coordTile(int x, int y, int z)
{
    coord_x = x;
    coord_y = y;
    coord_z = z;
}

QPixmap ImageManager_req::getImage(int x, int y, int z)
{
    QPixmap pm;
    loader->loadImage(x, y, z);

    return pm;
}

ImageManager_req::~ImageManager_req()
{
    delete loader;
}