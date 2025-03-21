#include "maplocalindexfile.h"
#include <cmath>
#include <QFile>
#include <QDir>
#include <QThreadPool>
#include <QBuffer>

#include <QTime>
#include <QDebug>

#include "mapfile.h"

namespace qmapcontrol
{
    bool    IndexFileParams::contains(const QString &fileName) const
    {
        return indexOf(fileName) != -1;
    }

    int        IndexFileParams::indexOf(const QString &fileName) const
    {
        for (int i = 0, cnt = count(); i < cnt; ++i)
        {
            if ((*this)[i].fileName.compare(fileName, Qt::CaseInsensitive) == 0)
                return i;
        }

        return -1;
    }


    IndexFileData *MapLocalIndexFile::load(QString filename)
    {
        QString idxfilename = filename + "i";

        QFile file(idxfilename);
        if (!file.open(QIODevice::ReadOnly)) return NULL;

        IndexFileData *dat = new IndexFileData();

        QTime t;
        t.start();
        dat->items.clear();
        int64_t count = file.size() / sizeof(IndexItem);
        dat->items.resize(count);
        file.read((char*)dat->items.data(), count * sizeof(IndexItem));
        file.close();

        dat->imagefile = filename;

        // заполняем hash
        dat->hashedItems.reserve(count);
        for (auto it = dat->items.begin(); it != dat->items.end(); it++)
        {
            dat->hashedItems[IndexKey(it->Zoom, it->NumX, it->NumY)] = IndexData(it->Size, it->OffSet);
        }

        return dat;
    }

    IndexFile::IndexFile(QString serachFilter, QObject *parent) : QObject(parent)
    {
        _unhashedSearch = true;
        _searchFilter = serachFilter;
        mutex = new QMutex(QMutex::Recursive);

#ifdef CACHED_INDEX
        _index.setMaxCost(1024 * 10);
#endif
    }

    IndexFile::~IndexFile()
    {
        indexLock_.lockForWrite();
        _index.clear();
        indexLock_.unlock();

        for (auto it = _tmpFileData.begin(); it != _tmpFileData.end(); it++)
        {
            delete (*it);
        }

        delete mutex;
    }

    bool IndexFile::getImage(QPixmap &pm, int zoom, int x, int y)
    {

        // если в текущем индексе нет необходимой строки, то производим загрузку с файлов
        IndexData idxData = _getIndexData(zoom + 1, x, y);
        int cx = x, cy = y, cz = zoom; // координаты соответсвующие уровню zoom
        if (idxData.Size == -1)
        {
            // если файлы уже загружались, то не проверяем
            if (_loadedFiles.count() == 0)
            {
                if (!_loadFromSearchPath())
                {
                    //qDebug() << "IndexFile::getImage() can`t load index" << t.elapsed();
                    return false;
                }
                idxData = _getIndexData(zoom + 1, x, y);
            }

            // если необходимая запись так и не найдена, то ищем вышестоящую по уровню
            if (idxData.Size == -1)
            {
               // тайл не найден
               return false;

            }
        }

        // если запись найдена, то пытаемся прочитать изображение из соответсвующего файла
        QString fileName = _loadedFiles[idxData.FileIndex].fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            return false;
        }

        file.seek(idxData.Offset);
        QByteArray imageData = file.read(idxData.Size);

        file.close();

        if (!pm.loadFromData(imageData))
        {
            return false;
        }
        return true;
    }

    bool IndexFile::getImage(QByteArray &ba, int zoom, int x, int y)
    {
        // если в текущем индексе нет необходимой строки, то производим загрузку с файлов
        IndexData idxData = _getIndexData(zoom + 1, x, y);
        int cx = x, cy = y, cz = zoom; // координаты соответсвующие уровню zoom
        if (idxData.Size == -1)
        {
            // если файлы уже загружались, то не проверяем
            if (_loadedFiles.count() == 0)
            {
                if (!_loadFromSearchPath())
                {
                    //qDebug() << "IndexFile::getImage() can`t load index" << t.elapsed();
                    return false;
                }
                idxData = _getIndexData(zoom + 1, x, y);
            }

            // если необходимая запись так и не найдена, то ищем вышестоящую по уровню
            if (idxData.Size == -1)
            {
                // если не найдена запись для необходимого уровня, то ищем соответсвующую на уровнях выше
                do
                {
                    cz--;
                    cx /= 2;
                    cy /= 2;
                    idxData = _getIndexData(cz + 1, cx, cy);
                } while (idxData.Size == -1 && cz > 1);
                // ничего подходящего, не найдено
                if (idxData.Size == -1)
                {
                    //qDebug() << "IndexFile::getImage() can`t find item" << t.elapsed();
                    return false;
                }

            }
        }

        // если запись найдена, то пытаемся прочитать изображение из соответсвующего файла
        QString fileName = _loadedFiles[idxData.FileIndex].fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            //qDebug() << "IndexFile::getImage() can`t open file" << t.elapsed();
            return false;
        }

        file.seek(idxData.Offset);
        ba = file.read(idxData.Size);

        file.close();

        // если загруженный уровень приближения не соответсвует исходному, то берём только часть картинки
        if (cz != zoom)
        {
            QPixmap pm;

            if (!pm.loadFromData(ba))
            {
                return false;
            }

            // если не совпадает, то нужно вернуть растянутую часть картинки
            // определяем область для копирования
            int relTilesCount = std::pow(2, zoom - cz);
            QRect rect;
            rect.setLeft((pm.width() / relTilesCount) * (x % relTilesCount));
            rect.setTop((pm.height() / relTilesCount) * (y % relTilesCount));
            rect.setWidth(pm.width() / relTilesCount);
            rect.setHeight(pm.height() / relTilesCount);
            QPixmap tmp = pm.copy(rect);
            pm = tmp.scaled(pm.width(), pm.height(), Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);


            // сохраняем в виде масиива байт
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            pm.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
        }
        return true;
    }

    bool IndexFile::_loadFromSearchPath()
    {
        bool result = false;

        QStringList parts = _searchFilter.split("/");
        if (parts.length() == 1) parts = _searchFilter.split("\\");

        QString nameFilter = parts.takeLast();
        QDir dir(parts.join("/"), nameFilter);

        // получаем список файлов по маске
        QFileInfoList list = dir.entryInfoList(QDir::Files, QDir::Name);
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);

            QString filename = fileInfo.absoluteFilePath();
            // файл уже загружался
            if (_loadedFiles.contains(filename)) continue;

            IndexFileParam ifp;
            ifp.fileName = filename;



            IndexFileData *dat = new IndexFileData();
            dat->imagefile = filename;

            // проверяем тип файла индекса для загрузки
            // пытаемся прочитать заголовок

            mapfile::FileHeaderBase header;
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly)) continue;
            file.read((char*)&header, sizeof(mapfile::FileHeaderBase));
            file.close();

            if (strcmp(header.signature, "MAPFILE") == 0)
            {
                // новый формат (единый файл)
                if (header.version == 1)
                {
                    QFile file(filename);
                    if (!file.open(QIODevice::ReadOnly)) continue;
                    file.seek(sizeof(mapfile::FileHeaderBase));

                    mapfile::FileHeaderV1 subHeader;
                    file.read((char*)&subHeader, sizeof(mapfile::FileHeaderV1));

                    ifp.dataOffset = subHeader.indexLength;

                    // читаем записи индексов
                    std::vector<mapfile::FileIndex> items;
                    int64_t count = subHeader.indexLength / sizeof(mapfile::FileIndex);
                    items.resize(count);

                    file.read((char*)items.data(), count * sizeof(mapfile::FileIndex));
                    file.close();

                    dat->items.reserve(dat->items.size() + count);    // учитываем данные от предыдущих файлов
                    foreach(mapfile::FileIndex ii, items)
                    {
                        dat->items.push_back(IndexItem(ii.z, ii.x, ii.y, ii.fileSize, ii.offset + subHeader.indexLength + sizeof(mapfile::FileHeaderBase) + sizeof(mapfile::FileHeaderV1)));
                    }
                }
                else if (header.version == 2)
                {
                    QFile file(filename);
                    if (!file.open(QIODevice::ReadOnly)) continue;
                    file.seek(sizeof(mapfile::FileHeaderBase));

                    mapfile::FileHeaderV2 subHeader;
                    file.read((char*)&subHeader, sizeof(mapfile::FileHeaderV2));

                    ifp.dataOffset = 
                        +sizeof(mapfile::FileHeaderBase)
                        + sizeof(mapfile::FileHeaderV2)
                        + subHeader.indexLength
                        + subHeader.clusterLength;

                    // читаем записи кластеров
                    std::vector<mapfile::IndexCluster> clsItems;
                    int64_t count = subHeader.clusterLength / sizeof(mapfile::IndexCluster);
                    clsItems.resize(count);

                    file.read((char*)clsItems.data(), count * sizeof(mapfile::IndexCluster));
                    file.close();

                    // сохраняем данные о кастерах в памяти
                    IndexItems &iis = dat->clusters[subHeader.clusterSize];
                    iis.reserve(iis.count() + count);    // учитываем данные от предыдущих файлов
                    foreach(mapfile::IndexCluster ii, clsItems)
                    {
                        iis.push_back(IndexItem(ii.z, ii.x, ii.y, 
                            ii.size, 
                            ii.offset 
                                + sizeof(mapfile::FileHeaderBase)
                                + sizeof(mapfile::FileHeaderV2)
                                + subHeader.clusterLength
                                ));
                        //qDebug() << ii.z << ii.x << ii.y << ii.size << ii.offset << ii.offset
                        //    + sizeof(mapfile::FileHeaderBase)
                        //    + sizeof(mapfile::FileHeaderV2)
                        //    + subHeader.clusterLength;
                    }
                }
            }
            else
            {
                //старый формат (отдельный файлы)

                filename = filename + "i";

                //qDebug() << "--- INDEX FILE: " << filename;

                QFile file(filename);
                if (!file.open(QIODevice::ReadOnly)) continue;

                QTime t;
                t.start();
                dat->items.clear();
                int64_t count = file.size() / sizeof(IndexItem);
                dat->items.resize(count);
                file.read((char*)dat->items.data(), count * sizeof(IndexItem));
                file.close();
            }

            _loadedFiles.append(ifp);
            mutex->lock();
            _tmpFileData.append(dat);
            mutex->unlock();

            result = true;
        }

        // запускаем процесс хэширования индексов
        if (result)
        {
            HashLoader *hashLoader = new HashLoader(this);
            hashLoader->setAutoDelete(true);
            hashLoader->Setup(mutex, &_tmpFileData, &indexLock_, &_index, &_cluster, &_loadedFiles);

            QThreadPool::globalInstance()->start(hashLoader);
        }

        return result;
    }

    IndexData    IndexFile::_getIndexDataUnhashed(int zoom, int x, int y)
    {
        IndexData result;

        mutex->lock();
        for (auto it = _tmpFileData.begin(); it != _tmpFileData.end() && result.Size == -1; it++)
        {
            for (auto ii = (*it)->items.begin(); ii != (*it)->items.end() && result.Size == -1; ii++)
            {
                if (ii->Zoom == zoom && ii->NumX == x && ii->NumY == y)
                {
                    result =  IndexData(_loadedFiles.indexOf((*it)->imagefile), ii->Size, ii->OffSet);
                }
            }
        }
        mutex->unlock();

        return result;
    }

    IndexData IndexFile::_getIndexData(int zoom, int x, int y)
    {
        // если нехэшированный поиск, то проходим по всем записям временного массива
        if (_unhashedSearch)
        {
            // если запись найдена, то больше ничего искать не нужно
            IndexData idxData = _getIndexDataUnhashed(zoom, x, y);
            if (idxData.Size != -1) return idxData;
        }

        // ищем в индексе
        indexLock_.lockForRead();
#ifndef CACHED_INDEX
        IndexData result = _index.value(IndexKey(zoom, x, y), IndexData());
#else
        IndexData result;
        IndexData *pResult = _index[IndexKey(zoom, x, y)];
        if (pResult) result = *pResult;
#endif
        indexLock_.unlock();


        // если поиск по кластерам, то загружаем индексы кластера
        if (result.Size == -1 && !_cluster.isEmpty())
        {
            // необходимо знать размер кластера, используемого в файле
            //    в разных файлах - могут быть разные
            // вычисляем номер кластера

            indexLock_.lockForRead();
            // для всех доступных размеров кластеров вычисляем
            //    положение кластера
            IndexData id;
            foreach(auto clsSize, _cluster.keys())
            {
                int cx = x / clsSize;
                int cy = y / clsSize;

                id = _cluster[clsSize].value(IndexKey(zoom, cx, cy), id);
                if (id.Size != -1)
                    break;
            }
            indexLock_.unlock();

            if (id.Size != -1)
            {
                // кластер найден - загружаем индексы
                QFile file(_loadedFiles[id.FileIndex].fileName);
                if (file.open(QIODevice::ReadOnly))
                {
                    file.seek(id.Offset);

                    // читаем записи индексов
                    std::vector<mapfile::FileIndex> items;
                    int64_t count = id.Size / sizeof(mapfile::FileIndex);
                    items.resize(count);

                    file.read((char*)items.data(), count * sizeof(mapfile::FileIndex));
                    file.close();

                    IndexFileData *dat = new IndexFileData();
                    dat->items.reserve(count);
                    dat->imagefile = _loadedFiles[id.FileIndex].fileName;
                    foreach(mapfile::FileIndex ii, items)
                    {
                        int dataOffset = _loadedFiles[id.FileIndex].dataOffset;
                        dat->items.push_back(IndexItem(ii.z, ii.x, ii.y, ii.fileSize, 
                            ii.offset + dataOffset));
                    }
                    mutex->lock();
                    _tmpFileData.append(dat);
                    mutex->unlock();


                    // нехэшированный поиск по существующим данным кластера
                    result = _getIndexDataUnhashed(zoom, x, y);

                    // запускаем хэширование
                    HashLoader *hashLoader = new HashLoader(this);
                    hashLoader->setAutoDelete(true);
                    hashLoader->Setup(mutex, &_tmpFileData, &indexLock_, &_index, &_cluster, &_loadedFiles);

                    QThreadPool::globalInstance()->start(hashLoader);
                }
            }
        }

        return result;
    }

    void IndexFile::indexFileDataHashed(IndexFileData *dat)
    {
        mutex->lock();
        _tmpFileData.removeOne(dat);
        delete dat;
        mutex->unlock();
    }

    void IndexFile::hashingComplited()
    {
        mutex->lock();
        _unhashedSearch = false;
        mutex->unlock();
    }

}
