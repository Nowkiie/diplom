#pragma once
#include <QVector>

class workWithHardware
{
public:
    workWithHardware();
    ~workWithHardware();
    void addNameHardware(QString name);
    void delNameHardware(QString name);
    QVector<QString>& getPointerOnListName();

private:
    QVector<QString> listNameHardware_;
};