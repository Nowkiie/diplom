#ifndef GEOMETRYPROCESSORMAPEXTENTION_H
#define GEOMETRYPROCESSORMAPEXTENTION_H

#include "mapextention.h"

#include <QObject>

namespace qmapcontrol
{
    class GeometryProcessor;

    /*!
    *    Интерфейс для получения списка объектов для обработки
    *    @author Maxim Poylov
    */
    class Geometries : public QObject
    {
        Q_OBJECT

        friend GeometryProcessor;

    public:
        Geometries(QObject *parent = 0);
        virtual ~Geometries();

        virtual QList<Geometry*> geometries(int processordID) const = 0;


        void    setCache(int processorID, QVariant value);
        bool    isCached(int processorID) const;
        QVariant    cache(int processorID) const;

    private:
        int        getGeometryProcessorID();

    signals:
        void    updated();

    protected:
        void    beginGeometriesUpdate();
        void    endGeometriesUpdate();

    private:
        QMutex    lock_;
        QMap<int, QVariant>    cache_;
        int        nextID_;
    };

    /*!
    *    Класс-примесь для работы с наборами объектов геометрий
    *
    *    Базовый класс для реализации "расширений", которым необходимо обрабатывать
    *       список объектов
    *   По-умолчанию вызов start() генерирует сигнал needGeometries() для получения
    *       списка объектов, над которыми производить действие
    *        Клиент, подписавшийся на сигнал needGeometries(), должен сформировать список
    *        объектов и передать его расширению через функцию GeometryProcessor::process(...)
    *    @author Maxim Poylov
    */
    class GeometryProcessor
    {
    public:
        GeometryProcessor() :geos_(NULL) {};
        virtual ~GeometryProcessor() {};

    public:
        virtual void    setGeometries(Geometries *geos)
        {
            geos_ = geos;
            cacheID_ = geos->getGeometryProcessorID();
            // надо ли?
            // чаще всего эта функция будет вызываться один раз при создании
            //    расширения карты, а геометрии актуальны ещё не будут...
            //geometriesUpdated();
        }

        int        processorID() { return cacheID_; }

    protected:
        Geometries    *geos_;

    private:
        int            cacheID_;
    };

}
#endif