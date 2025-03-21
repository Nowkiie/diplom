#include "tableModel.h"

tableModel::tableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    workWithUnit_ = std::make_shared<workWithUnit>();
    // this->setHeaderData(0, Qt::Horizontal, "name");

    connect(workWithUnit_.get(), &workWithUnit::unitCreated,
            [this]()
            {
                int newRow = workWithUnit_->getCountUnits();
                beginInsertRows(QModelIndex(), newRow, newRow);
                workWithUnit_->getUnitByNumber(
                    workWithUnit_->getPointerOnVectorUnits().size() - 1);
                endInsertRows();
            });

    connect(workWithUnit_.get(), &workWithUnit::unitWindowClosed,
            [this]()
            {
                work_with_unit = false;
            });
}

QVariant tableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            //TODO: добавить столбцы = разделить аппартуру на виды
            case 0:
                return QObject::tr("Unit name");
            case 1:
                return QObject::tr("Hardware");
            default:
                return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

int tableModel::rowCount(const QModelIndex& parent) const
{
    return workWithUnit_->getCountUnits();
}

int tableModel::columnCount(const QModelIndex& parent) const
{
    return 3;
}

void tableModel::writeCoord(QPointF coord)
{
    workWithUnit_->writeCoord(coord);
}

QVector<unit> tableModel::getPointerOnVectorUnit()
{
    return workWithUnit_->getPointerOnVectorUnits();
}

void tableModel::initialMenu(QVariant listHardwares)
{
    workWithUnit_->initialMenu(listHardwares);
}

void tableModel::writeUnits(QVector<unit> units)
{
    if (!units.isEmpty() && !workWithUnit_->getStatusSavParamter())
    {
        workWithUnit_->writeUnit(std::move(units));
        int newRow = workWithUnit_->getCountUnits();
        beginInsertRows(QModelIndex(), 1, newRow);
        endInsertRows();
    }
}

QVariant tableModel::data(const QModelIndex& index, int role) const
{
    // TODO: при удалении/изменении названий аппартуры добавить подцветку пунктов, содерж. старую версию

    QVariant value;
    switch (role)
    {
        case Qt::DisplayRole:
        {
            unit writingUnit = workWithUnit_->getUnitByNumber(index.row());
            switch (index.column())
            {
                case 0:
                {
                    value = writingUnit.name;
                    break;
                }
                case 1:
                {
                    QString listHardwareInString = "[";

                    QString antSystInText =
                        writingUnit.hardware_.ant_system.name + ",";
                    listHardwareInString += antSystInText;
                    QString sendInText = writingUnit.hardware_.send.name + ",";
                    listHardwareInString += sendInText;
                    QString recvInText = writingUnit.hardware_.rec.name;
                    listHardwareInString += recvInText;
                    value = listHardwareInString + "]";
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        default:
        {
            break;
        }
    }

    return value;
}

unit tableModel::getUnitByNumber(int number)
{
    return workWithUnit_->getUnitByNumber(number);
}

bool tableModel::returnStatusWorkWithUnit()
{
    return work_with_unit;
}

void tableModel::append()
{
    work_with_unit = true;
    workWithUnit_->addUnit();
}

void tableModel::remove(int idx)
{
    beginRemoveRows(QModelIndex(), idx, idx);
    workWithUnit_->delUnitByNumber(idx);
    endRemoveRows();
}

void tableModel::change(int idx)
{
    work_with_unit = true;
    workWithUnit_->updateUnit(idx);
    QModelIndex item_idx_s = index(idx, 0);
    QModelIndex item_idx_e = index(idx, columnCount(QModelIndex()));

    emit dataChanged(item_idx_s, item_idx_e);
}
