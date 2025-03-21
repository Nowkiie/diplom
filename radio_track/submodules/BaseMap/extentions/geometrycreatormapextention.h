#ifndef GEOMETRYCREATORMAPEXTENTION_H
#define GEOMETRYCREATORMAPEXTENTION_H

#include "checkablemapextention.h"

namespace qmapcontrol
{

    /*!
    *    Базовый-класс для расширении для создания объектов на карте
    *    @author Maxim Poylov
    */
    class GeometryCreatorMapExtention :
        public CheckableMapExtention
    {
        Q_OBJECT

    public:
        GeometryCreatorMapExtention(MapControl *mapControl, Layer *layer, QObject *parent = NULL);
        virtual ~GeometryCreatorMapExtention();

        /*!
        *    Устанавливает управляющую клавишу, сочетание с которой
        *        может использоваться для внутренних целей программы
        */
        void setKeyboardModifier(Qt::KeyboardModifier key);
        Qt::KeyboardModifier keyboardModifier() const;

        //virtual void setLayer(Layer *layer);
        /*!
        *    Возвращает слой, на котором создаются объекты
        */
        Layer *getLayer();

    public slots:
        virtual void start();
        virtual void stop(MapExtention *sender);

    signals:
        void objectCreated(GeometryCreatorMapExtention *sender, Geometry *object);

    protected:
        Layer *layer_;
        Qt::KeyboardModifier key_;
    };

}
#endif