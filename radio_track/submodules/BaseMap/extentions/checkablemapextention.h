#ifndef CHECKABLEMAPEXTENTION_H
#define CHECKABLEMAPEXTENTION_H

#include "mapextention.h"

namespace qmapcontrol
{

    /*!
    *    Базовый класс для реализации "расширений", которые могут находиться в двух состаяниях "включен/выключен"
    *    @author Maxim Poylov
    */
    class CheckableMapExtention :
        public MapExtention
    {
        Q_OBJECT
    public:
        CheckableMapExtention(MapControl *mapControl, QObject *parent = NULL);
        virtual ~CheckableMapExtention();

        /*!
        *    Установка признака - переход в отключенное состояние по нажатию клавиши клавиатуры
        */
        void setEnableStopOnKeyboard(bool enable);

    public slots:
        virtual void start();
        virtual void stop(MapExtention *sender);

        /*!
        *    Установка состояния "включен/выключен"
        */
        virtual void setChecked(bool checked);

    signals:
        /*!
        *    Сигнал о изменении состояния "включен/выключен"
        */
        void checkedChanged(bool checked);

    public:
        /*!
        *    Текущее состояние
        */
        bool isChecked();

    private slots:
        void keyboardEvent_(const QKeyEvent *event);

    private:
        bool isChecked_;
        bool isEnabledStopOnKeyboard_;
        QMetaObject::Connection stopOnKeyboard_;
    };

}
#endif