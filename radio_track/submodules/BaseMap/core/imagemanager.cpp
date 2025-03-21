
#include "imagemanager.h"
#include "maplocalpath.h"
#include "urlconverter.h"

namespace qmapcontrol
{

    const int defaultCacheSize = 50*1024;

    ImageManager::ImageManager(MapLoader *loader, QObject* parent)
        :QObject(parent), emptyPixmap(QPixmap(2,2)), 
        loader(loader)
    {

        if (QPixmapCache::cacheLimit() < defaultCacheSize)
        {
            QPixmapCache::setCacheLimit(defaultCacheSize);
        }

        emptyPixmap.fill(Qt::transparent);

        connect(loader, &MapLoader::imageLoaded, 
            this, &ImageManager::imageLoaded);

        connect(loader, &MapLoader::imageEmpty,
            this, &ImageManager::imageEmpty);

        connect(loader, &MapLoader::imageLoadingComplited,
            this, &ImageManager::imageLoadingComplited);

    }

    ImageManager::~ImageManager()
    {
        delete loader;
    }


    QPixmap ImageManager::getImage(int x, int y, int z)
    {
        QPixmap pm;
        QString fakeUrl = tilesToUrl(x, y, z, this);

        if (!QPixmapCache::find(fakeUrl, pm) && 
            !loader->imageIsLoading(x, y, z) &&
            !imageIsLoadingUpscale(x, y, z))
        {
            loader->loadImage(x, y, z);
            return emptyPixmap;
        }
        return pm;
    }

    QPixmap ImageManager::prefetchImage(int x, int y, int z)
    {
        return getImage(x, y, z);
    }

    void ImageManager::abortLoading()
    {
        loader->abortLoading();
    }
    void ImageManager::imageLoaded(const QPixmap pixmap, int x, int y, int z)
    {
        QString fakeUrl = tilesToUrl(x, y, z, this);
        QPixmapCache::insert(fakeUrl, pixmap);
        emit imageReceived(x, y, z);
        processUpscaleImage(pixmap, x, y, z);
    }
    void ImageManager::imageEmpty(int x, int y, int z)
    {
        if (z == 0)
        {
            return;
        }

        //проверяем, есть ли изображение с предыдущего уровня
        QString fakeUrl = tilesToUrl(x / 2, y / 2, z - 1, this);

        QPixmap pm;
        if (QPixmapCache::find(fakeUrl, pm))
        {
            sendUpscaledImage(pm, x, y, z);
        }
        else
        {
            //запрос изображения
            prefetchImage(x / 2, y / 2, z - 1);
            //сделаем ресайз при получении
            upscaleTiles.push_back({ x, y, z });
        }
    }
    void ImageManager::imageLoadingComplited()
    {
        //большетайлов не будет
        upscaleTiles.clear();
        emit loadingFinished();
    }

    bool ImageManager::imageIsLoadingUpscale(int x, int y, int z)
    {
        for (const auto &us : upscaleTiles)
        {
            if (us.x == x && us.y == y && us.z == z)
                return true;
        }
        return false;
    }

    /**
     \brief Обработка полученного изображения для апскайла
   
     */
    void ImageManager::processUpscaleImage(QPixmap pixmap, int x, int y, int z)
    {
        QVector<ImageManagerUpscale> currentUpscaleTiles;

        for (auto iter = upscaleTiles.begin(); iter != upscaleTiles.end();)
        {
            if (iter->x / 2 == x && iter->y / 2 == y && iter->z == z + 1)
            {
                currentUpscaleTiles.push_back(*iter);
                iter = upscaleTiles.erase(iter);
                continue;
            }
            ++iter;
        }
        for (const auto &ut : currentUpscaleTiles)
        {
            sendUpscaledImage(pixmap, ut.x, ut.y, ut.z);
        }
    }
    void ImageManager::sendUpscaledImage(
        QPixmap prevLevelPixmap, int x, int y, int z)
    {
        // растягиваем изображение с предыдущего уровня
        QSize partSize = prevLevelPixmap.size() / 2;
        QPoint partPoint(x % 2 ? partSize.width() : 0,
            y % 2 ? partSize.height() : 0);
        QRect partRect(partPoint, partSize);

        QPixmap currentLevelPixmap = prevLevelPixmap.copy(partRect);
        currentLevelPixmap = currentLevelPixmap.scaled(prevLevelPixmap.size(),
            Qt::AspectRatioMode::IgnoreAspectRatio,
            Qt::TransformationMode::SmoothTransformation);
        // если отстуствуют 2 и более уровней выполняем рекурсивно
        
        QString fakeUrl = tilesToUrl(x, y, z, this);
        QPixmapCache::insert(fakeUrl, currentLevelPixmap);
        
        processUpscaleImage(currentLevelPixmap, x, y, z);
        emit imageReceived(x, y, z);
    }
}

