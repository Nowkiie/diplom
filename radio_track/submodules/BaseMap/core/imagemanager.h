/*
*
* This file is part of QMapControl,
* an open-source cross-platform map widget
*
* Copyright (C) 2007 - 2008 Kai Winter
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with QMapControl. If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: kaiwinter@gmx.de
* Program URL   : http://qmapcontrol.sourceforge.net/
*
*/

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H


#include <QObject>
#include <QPixmapCache>
#include <QDebug>
#include <QString>
#include <QMutex>
#include <QFile>
#include <QBuffer>
#include <QDir>
#include "maploader.h"


#include <QMutex>

namespace qmapcontrol
{
    class MapNetwork;

    struct ImageManagerUpscale
    {
        int x, y, z;
    };

    class ImageManager : public QObject
    {
        Q_OBJECT;

    public:
        ImageManager(MapLoader *loader, QObject* parent = 0);
        ~ImageManager();

        virtual QPixmap getImage(int x, int y, int z);

        virtual QPixmap prefetchImage(int x, int y, int z);

        void abortLoading();

    private slots:
        void imageLoaded(const QPixmap pixmap, int x, int y, int z);
        // картинка не найдена
        void imageEmpty(int x, int y, int z);
        void imageLoadingComplited();
    signals:

        /**
         \brief получена картинка с заданными координатами

         */
        void imageReceived(int x, int y, int z);
        /** \brief Все изображения загружены */
        void loadingFinished();
    private:
        bool imageIsLoadingUpscale(int x, int y, int z);
        void processUpscaleImage(QPixmap pixmap, int x, int y, int z);
        void sendUpscaledImage(QPixmap prevLevelPixmap, int x, int y, int z);
        QVector<ImageManagerUpscale> upscaleTiles;
        ImageManager(const ImageManager&);
        ImageManager& operator=(const ImageManager&);
        QPixmap emptyPixmap;
        MapLoader* loader;
    };
}
#endif
