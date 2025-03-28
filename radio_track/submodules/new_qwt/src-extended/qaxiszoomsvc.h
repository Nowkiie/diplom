﻿/**********************************************************/
/*                                                        */
/*                   Класс QAxisZoomSvc                   */
/*                      Версия 1.2.2                      */
/*                                                        */
/* Поддерживает интерфейс изменения одной из границ       */
/* графика, является дополнением к классу QwtChartZoom,   */
/* начиная с версии 1.5.0.                                */
/*                                                        */
/* Разработал Мельников Сергей Андреевич,                 */
/* г. Каменск-Уральский Свердловской обл., 2012 г.,       */
/* при поддержке Ю. А. Роговского, г. Новосибирск.        */
/*                                                        */
/* Разрешается свободное использование и распространение. */
/* Упоминание автора обязательно.                         */
/*                                                        */
/**********************************************************/

#ifndef QAXISZOOMSVC_H
#define QAXISZOOMSVC_H

#include "qwtchartzoom.h"

class QWT_EXPORT QAxisZoomSvc : public QObject
{
    Q_OBJECT

public:
    // конструктор
    explicit QAxisZoomSvc();

    // прикрепление интерфейса к менеджеру масштабирования
    void attach(QwtChartZoom *);

    // включение/выключение легкого режима
    void setLightMode(bool);
    // установка цвета виджета, индицирующего масштабирование шкалы
    void setAxisRubberBandColor(QColor);
    // включение/выключение индикации масштабирования шкалы
    // (имеет эффект, если включен легкий режим)
    void indicateAxisZoom(bool);

protected:
    // обработчик всех событий
    bool eventFilter(QObject *,QEvent *);

private:
    QwtChartZoom *zoom;     // Опекаемый менеджер масштабирования
    bool light;             // Легкий режим (с индикацией масштабирования)
    QWidget *zwid;          // Виджет для отображения индикатора масштабирование шкалы
    QColor awClr;           // Цвет виджета, индицирующего масштабирование шкалы
    bool indiAxZ;           // Флаг индикации масштабирования шкалы
    QCursor tCursor;        // Буфер для временного хранения курсора

    double scb_xl,scb_xr;   // Текущие границы графика по оси x в момент начала преобразования
    double scb_yb,scb_yt;   // Текущие границы графика по оси y в момент начала преобразования
    double scb_wx,scb_hy;   // Текущие ширина и высота графика в момент начала преобразования
    int scb_pxl,scb_pyt;    // Текущие левое и верхнее смещение графика в момент начала преобразования
                            // (в пикселах относительно канвы)
    int scb_pw,scb_ph;      // Текущие ширина и высота графика в момент начала преобразования
                            // (в пикселах)
    int scp_x,scp_y;        // Положение курсора в момент начала преобразования
                            // (в пикселах относительно канвы графика за вычетом смещений графика)
    int sab_pxl,sab_pyt;    // Текущие левое и верхнее смещение графика в момент начала преобразования
                            // (в пикселах относительно виджета шкалы)

    // ограничение размера индикатора
    int limitSize(int,int);
    // получение геометрии индикации масштабирования шкалы
    QRect *axisZoomRect(QPoint,int);
    // прорисовка изображения масштабируемой шкалы
    void showZoomWidget(QPoint,int);

    // ограничение нового размера шкалы
    double limitScale(double,double);
    // применение результатов перемещения границы шкалы
    void axisApplyMove(QPoint,int);

    // обработчик событий от мыши для шкалы
    void axisMouseEvent(QEvent *,int);

    // обработчик нажатия на кнопку мыши над шкалой
    // (включение изменения масштаба шкалы)
    void startAxisZoom(QMouseEvent *,int);
    // обработчик перемещения мыши
    // (выделение новых границ шкалы)
    void procAxisZoom(QMouseEvent *,int);
    // обработчик отпускания кнопки мыши
    // (выполнение изменения масштаба шкалы)
    void endAxisZoom(QMouseEvent *,int);
};

#endif // QAXISZOOMSVC_H
