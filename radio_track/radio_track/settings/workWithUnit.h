#pragma once
#include <QString>
#include <QVector>
#include "formUnit.h"

namespace settings
{

class workWithUnit : public QWidget
{
    Q_OBJECT

public:
    workWithUnit();
    ~workWithUnit();
    void addUnit();
    void delUnitByNumber(int number);
    int getCountUnits();
    unit getUnitByNumber(int number);
    void updateUnit(int number);
    QVector<unit> getPointerOnVectorUnits();
    void initialMenu(QVariant listHardwares);
    void writeUnit(QVector<unit> units);
    bool getStatusSavParamter();
    void writeCoord(QPointF coord);
signals:
    void unitCreated();
    void unitWindowClosed();

private:
    QVector<unit> units_;
    std::shared_ptr<unitWindow> unitWindow_;
    int numberUpdateNumber;
    bool saveParametr = false;
};
}  // namespace settings
