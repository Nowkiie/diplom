#ifndef MAPEXTENTION_H
#define MAPEXTENTION_H

#include "core/mapcontrol.h"

namespace qmapcontrol
{
    /*!
    *    Базовый класс для реализации "расширений" для карты 
    *    Определяет основной интерфейс для реализации в производных классах
    *    @author Maxim Poylov
    */
    class MapExtention
         : public QObject
    {
        Q_OBJECT

    public:
        MapExtention(MapControl *mapControl, QObject *parent = NULL);
        virtual ~MapExtention();

    private:
        MapExtention(const MapExtention &obj);
        MapExtention &operator =(const MapExtention &obj);

    public slots:
        /*!
        *    Запуск работы расширения (если для этого требуется какое-то событие)
        *   Выполняет необходимую для своей работы настройку
        */
        virtual void start();

        /*!
        *    Остановка работы расширения (если, например, запустилось другое расширение)
        *   Выполняет очистку используемых расширением ресурсов и прекращает работу расширения
        */
        virtual void stop(MapExtention *sender);

    signals:
        /*!
        *    Расширение запущено
        *   Формируется автоматически базовой реализацией start()
        */
        void started(MapExtention *sender);

        /*!
        *    Расширение завершено
        *   Формируется автоматически базовой реализацией stop(MapExtention *sender)
        *      в случае если работу завершает данный объект
        */
        void done(MapExtention *sender);

    protected:
        MapControl *mapControl_;
    };
}

#endif
