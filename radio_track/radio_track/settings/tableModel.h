#pragma once
#include <QAbstractTableModel>
#include "workWithUnit.h"
#include "../structParamNet.h"

using namespace settings;

class tableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit tableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;
    void append();
    void remove(int idx);
    void change(int idx);
    unit getUnitByNumber(int number);
    QVector<unit> getPointerOnVectorUnit();
    void initialMenu(QVariant listHardwares);
    void writeUnits(QVector<unit> units);
    bool returnStatusWorkWithUnit();
    void writeCoord(QPointF coord);

private:
    int count = 2;
    std::shared_ptr<workWithUnit> workWithUnit_;
    bool work_with_unit = false;
};
