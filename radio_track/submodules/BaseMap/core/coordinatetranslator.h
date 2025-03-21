#ifndef COORDINATETRANSLATOR_H
#define COORDINATETRANSLATOR_H

#include <QPointF>

namespace qmapcontrol
{

    /*!
    *    Базовый класс для реализации привязки координат курсора
    *        к точкам на карте
    *    @author Maxim Poylov
    */
    class CoordinateTranslator
    {
    public:
        CoordinateTranslator();
        virtual ~CoordinateTranslator();

        /*!
        *    Выполняет по необходимости замену исходного значения координаты coordinate, на вычисленное
        */
        virtual QPointF translate(QPointF coordinate) = 0;
    };

}

#endif