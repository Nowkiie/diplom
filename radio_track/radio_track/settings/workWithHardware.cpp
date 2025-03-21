#include "workWithHardware.h"

workWithHardware::workWithHardware()
{
    addNameHardware("ytsf");
    addNameHardware("gdsuf");
    addNameHardware("ywqec");
    addNameHardware("qwyeg");
    addNameHardware("yf");
    addNameHardware("yfwqty");
}

void workWithHardware::addNameHardware(QString name)
{
    listNameHardware_.push_back(name);
}

void workWithHardware::delNameHardware(QString name)
{
    /* auto it =std::find_if(listNameHardware_.begin(), listNameHardware_.end(), name);
    if (it!=listNameHardware_.end())
    {
        int idx = it - listNameHardware_.begin();
        listNameHardware_.remove(idx);
    }*/
}

QVector<QString>& workWithHardware::getPointerOnListName()
{
    return listNameHardware_;
}

workWithHardware::~workWithHardware()
{
    listNameHardware_.clear();
}
