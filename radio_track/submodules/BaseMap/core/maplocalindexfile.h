#pragma once

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QHash>
#include <QMap>
#include <QRunnable>
#include <QMutex>
#include <QReadWriteLock>
#include <QCache>
#include <vector>
#include <stdint.h>

// параметр только для кластерных карт
//    иначе индексные будут работать некорреткно
//#define CACHED_INDEX

namespace qmapcontrol
{

    /*!
    *    Структура для хранения ключа индексной записи
    *    @author Maxim Poylov
    */
    struct IndexKey
    {
        IndexKey(uint32_t zoom, uint32_t numX, uint32_t numY)
            : Zoom(zoom), NumX(numX), NumY(numY)
        {
        }

        uint32_t Zoom;
        uint32_t NumX;
        uint32_t NumY;
    };

    inline bool operator==(const IndexKey &e1, const IndexKey &e2)
    {
        return e1.Zoom == e2.Zoom && e1.NumX == e2.NumX && e1.NumY == e2.NumY;
    }

    inline uint qHash(const IndexKey &key, uint seed)
    {
        // число 27 выбрано из расчета, что под максимальный Zoom нужно 5 разрядов (24-х кратное увеличение),
        // число 3 выбрано из расчета, что максимальная координата может быть 24 разряда
        return (key.Zoom << 27) | (key.NumX << 3) | (key.NumY);
    }


    /*!
    *    Структура для хранения данных индексной записи
    *    @author Maxim Poylov
    */
    struct IndexData
    {
        IndexData()
            :Size(-1)
        {
        }

        IndexData(uint32_t size, uint64_t offset)
            :Size(size), Offset(offset)
        {
        }

        IndexData(uint32_t fileIndex, uint32_t size, uint64_t offset)
            :FileIndex(fileIndex), Size(size), Offset(offset)
        {
        }

        uint32_t FileIndex;
        uint32_t Size;
        uint64_t Offset;
    };

    /*!
    *    Структура для загрузки информации об индесных записях с ключем и данными из файла
    *    @author Maxim Poylov
    */
    struct IndexItem
    {
        IndexItem()
            : Size(-1)
        {
        }

        IndexItem(uint32_t zoom, uint32_t numX, uint32_t numY, uint32_t size, uint64_t offset)
            : Zoom(zoom), NumX(numX), NumY(numY), Size(size), OffSet(offset)
        {
        }

        uint32_t Zoom;
        uint32_t NumX;
        uint32_t NumY;
        uint32_t Size;
        uint64_t OffSet;
    };

    /*!
    *    Структура хранения связи между файлом изображений и списком индексов
    *    @author Maxim Poylov
    */
    typedef QVector<IndexItem>    IndexItems;
    typedef QHash<IndexKey, IndexData>    IndexHash;
    struct IndexFileData
    {
        QString imagefile;
        IndexItems items;
        QHash<IndexKey, IndexData> hashedItems;

        QMap<int, IndexItems>    clusters;
        QMap<int, IndexHash> hashedClusters;
    };

    /*!
    *    Класс для загрузки информации из индексного файла
    *    @author Maxim Poylov
    */
    class MapLocalIndexFile
    {
    public:
        static IndexFileData *load(QString file);
    };

    struct IndexFileParam
    {
        IndexFileParam()
            : dataOffset(0)
        {
        }

        QString    fileName;
        uint64_t    dataOffset;
    };
    //typedef QList<IndexFileParam>    IndexFileParams;

    class IndexFileParams : public QList<IndexFileParam>
    {
    public:
        IndexFileParams() : QList<IndexFileParam>() {}
        IndexFileParams(const IndexFileParams &other) : QList<IndexFileParam>(other) {}

        bool    contains(const QString &fileName) const;
        int        indexOf(const QString &fileName) const;
    };


    class HashLoader;
    /*!
    *    Класс для хранения индексов изображений карты
    *    @author Maxim Poylov
    */
    class IndexFile : public QObject
    {
        Q_OBJECT

    public:
        IndexFile(QString serachPath, QObject *parent = 0);
        ~IndexFile();

        bool getImage(QPixmap &pm, int zoom, int x, int y);
        bool getImage(QByteArray &ba, int zoom, int x, int y);

    private:
        QString _searchFilter;
        IndexFileParams    _loadedFiles;

        bool _unhashedSearch;
        QList<IndexFileData*> _tmpFileData;
#ifndef CACHED_INDEX
        QHash<IndexKey, IndexData> _index;
#else
        QCache<IndexKey, IndexData> _index;
#endif
        QMap<int, IndexHash> _cluster;

        QMutex *mutex;
        QReadWriteLock    indexLock_;

    private:
        bool    _loadFromSearchPath();
        IndexData    _getIndexDataUnhashed(int zoom, int x, int y);
        IndexData    _getIndexData(int zoom, int x, int y);

    private:
        void indexFileDataHashed(IndexFileData *dat);
        void hashingComplited();

        friend HashLoader;
    };

    /*!
    *    Класс для выполнения операции хэширования массива индексов изображений карт
    *    @author Maxim Poylov
    */
    class HashLoader : public QObject, public QRunnable
    {
        Q_OBJECT

    public:
        HashLoader(IndexFile *parent)
        {
            _indexFile = parent;
        }

        void run()
        {
            while (!_input->isEmpty())
            {
                _mutex->lock();

                QList<IndexFileData*>::iterator datIt = _input->end();
                IndexFileData *dat = NULL;
                if (!_input->isEmpty())
                    datIt = _input->begin();

                while (datIt != _input->end())
                {
                    dat = (*datIt);
                    if (dat->items.empty()
                        && dat->clusters.isEmpty())
                    {
                        ++datIt;
                    }
                    else
                        break;
                }

                if (datIt == _input->end())
                {
                    _mutex->unlock();
                    break;
                }


                int fileIndex = _files->indexOf(dat->imagefile);
                Q_ASSERT(fileIndex != -1);

                IndexItems tmpItems;
                // важно, чтобы элементы в dat->itemsоставались, т.к. он используется при первом отображении карты
                //    сразу после загрузки
                tmpItems = dat->items;    // изменён тип объекта для исключения копирования данных
                QMap<int, IndexItems> tmpClusters;
                tmpClusters.swap(dat->clusters);

                _mutex->unlock();

                // заполянем списки индексов и кластеров
                // Старый вариант без блокировки

                //// переносим данные в основное хранилище

                // Новый вариант с блокировкой
#ifndef CACHED_INDEX
                QHash<IndexKey, IndexData> localIndex;
#else
                QHash<IndexKey, IndexData*> localIndex;
#endif
                QMap<int, IndexHash> localCluster;

                for (auto ii = tmpItems.begin(); ii != tmpItems.end(); ii++)
                {
#ifndef CACHED_INDEX
                    localIndex[IndexKey(ii->Zoom, ii->NumX, ii->NumY)] = IndexData(fileIndex, ii->Size, ii->OffSet);
#else
                    localIndex[IndexKey(ii->Zoom, ii->NumX, ii->NumY)] = new IndexData(fileIndex, ii->Size, ii->OffSet);
#endif
                }

                foreach(auto clsSize, tmpClusters.keys())
                {
                    IndexItems &iis = tmpClusters[clsSize];
                    IndexHash &ihs = localCluster[clsSize];
                    for (auto ii = iis.begin(); ii != iis.end(); ii++)
                    {
                        ihs[IndexKey(ii->Zoom, ii->NumX, ii->NumY)] = IndexData(fileIndex, ii->Size, ii->OffSet);
                    }
                }

                // переносим данные в основное хранилище
                _indexLock->lockForWrite();
                for (auto i : localIndex.keys())
                {
#ifndef CACHED_INDEX
                    (*_outputIndex)[i] = localIndex[i];
#else
                    (*_outputIndex).insert(i, localIndex[i]);
#endif
                }
                for (auto i : localCluster.keys())
                    (*_outputCluster)[i] = localCluster[i];
                _indexLock->unlock();

                _indexFile->indexFileDataHashed(dat);
            }

            _indexFile->hashingComplited();
        }

    public:
        void Setup(
            QMutex *mutex, 
            QList<IndexFileData*> *input, 
            QReadWriteLock *indexLock,
#ifndef CACHED_INDEX
            QHash<IndexKey, IndexData> *outputIndex,
#else
            QCache<IndexKey, IndexData> *outputIndex,
#endif
            QMap<int, IndexHash> *outputCluster,
            IndexFileParams *files)
        {
            _mutex = mutex;
            _input = input;
            _indexLock = indexLock;
            _outputIndex = outputIndex;
            _outputCluster = outputCluster;
            _files = files;
        }

    signals:
        void indexFileDataHashed(IndexFileData *dat);
        void hashingComplited();

    private:
        QMutex *_mutex;
        QReadWriteLock *_indexLock;
        QList<IndexFileData*> *_input;
#ifndef CACHED_INDEX
        QHash<IndexKey, IndexData> *_outputIndex;
#else
        QCache<IndexKey, IndexData> *_outputIndex;
#endif
        QMap<int, IndexHash> *_outputCluster;
        IndexFileParams *_files;

        IndexFile *_indexFile;
    };

}