#pragma once
#include <QWidget>
#include <QPainter>
#include <QBrush>

class widgetForDrawStep : public QWidget
{
    Q_OBJECT
public:
    widgetForDrawStep(int countStep, QWidget* parent = 0)
        : QWidget(parent)
    {
        countStep_ = countStep;
    }

    void setCountStep(int countStep)
    {
        countStep_ = countStep;
    }

    void setParam(int width, int height, int numberStep)
    {
        width_ = width;
        height_ = height;
        numberStep_ = numberStep;
        repaint();
    }

protected:
    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        //painter.setPen(Qt::blue);

        qreal top = (this->height() / 2) - 1.5;
        qreal centerWidget = (width_ / 2);
        qreal widthStepWidget = this->width();
        qreal left = widthStepWidget - centerWidget;
        for (int i = 0; i < countStep_; i++)
        {
            if (i < numberStep_)
            {
                painter.setBrush(Qt::green);
            }
            else
            {
                painter.setBrush(Qt::gray);
            }
            qreal pseudoLeft = left + i * 20;
            painter.drawRoundedRect(QRectF(pseudoLeft, top, 15, 3), 15, 3);
        }
    }

private:
    int countStep_ = 0;
    int width_ = 0;
    int height_ = 0;
    int numberStep_ = 0;
};
