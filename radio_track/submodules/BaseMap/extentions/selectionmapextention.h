#ifndef SELECTIONMAPEXTENTION_H
#define SELECTIONMAPEXTENTION_H

#include "geometries/staticgeometry.h"
#include "geometryprocessormapextention.h"
#include "checkablemapextention.h"

namespace qmapcontrol
{

    /*!
    *    Базовый класс для реализации "расширений" выполняющих выбор объектов
    *   По-умолчанию вызов start() генерирует сигнал needGeometries() для получения
    *       списка объектов, над которыми производить действие
    *        Клиент, подписавшийся на сигнал needGeometries(), должен сформировать список
    *        объектов и передать его расширению через функцию GeometryProcessor::process(...)
    *    @author Maxim Poylov
    */
    class SelectionMapExtention :
        public qmapcontrol::CheckableMapExtention
        , public qmapcontrol::GeometryProcessor
    {
        Q_OBJECT

    public:
        enum SelectionModifiers
        {
            SM_INIT,
            SM_APPEND
        };

    public:
        SelectionMapExtention(MapControl *mapControl, QObject *parent = NULL);
        virtual ~SelectionMapExtention();

        /*!
        *    Свойство - объекты добавляются к существующему списку
        *        или заменяют его
        */
        void setModifiers(SelectionModifiers modifiers);
        SelectionModifiers getModifiers();

    public slots:
        virtual void start();
        virtual void stop(MapExtention *sender);

    signals:
        /*!
        *    Сигнал - объекты выделены
        */
        void selected(QList<Geometry*> geometries, SelectionMapExtention::SelectionModifiers modifiers);

    private:
        SelectionModifiers modifier_;

    //signals:
    //    void needGeometries(GeometryProcessor *sender);
    };

}

#endif
