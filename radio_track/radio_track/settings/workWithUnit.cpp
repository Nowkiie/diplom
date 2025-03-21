#include "workWithUnit.h"

using namespace settings;

workWithUnit::workWithUnit()
{
    unitWindow_ = std::make_shared<unitWindow>();
    connect(unitWindow_.get(), &unitWindow::unitCreated,
            [this](unit unit)
            {
                units_.push_back(unit);
                unitWindow_->close();
                emit unitCreated();
            });

    connect(unitWindow_.get(), &unitWindow::close,
            [this]()
            {
                emit unitWindowClosed();
            });

    connect(unitWindow_.get(), &unitWindow::unitUpdate,
            [this](unit unit)
            {
                units_[numberUpdateNumber].name = unit.name;
                units_[numberUpdateNumber].coord.setY(unit.coord.y());
                units_[numberUpdateNumber].coord.setX(unit.coord.x());
                units_[numberUpdateNumber].hardware_ = unit.hardware_;
                //units_.push_back(unit);
                unitWindow_->close();
            });
}

void workWithUnit::writeCoord(QPointF coord)
{
    unitWindow_->writeCoord(coord);
}

bool workWithUnit::getStatusSavParamter()
{
    return saveParametr;
}

void workWithUnit::writeUnit(QVector<unit> units)
{
    units_ = units;
    saveParametr = true;
}

void workWithUnit::initialMenu(QVariant listHardwares)
{
    unitWindow_->initialMenu(listHardwares);
}

void workWithUnit::updateUnit(int number)
{
    unit updatingUnit = getUnitByNumber(number);
    numberUpdateNumber = number;
    unitWindow_->show();
    unitWindow_->updateUnit(getUnitByNumber(number));
}

void workWithUnit::addUnit()
{
    // units_.push_back(unit);
    unitWindow_->show();
    unitWindow_->raise();
}

void workWithUnit::delUnitByNumber(int number)
{
    units_.remove(number);
}

workWithUnit::~workWithUnit()
{
    units_.clear();
}

int workWithUnit::getCountUnits()
{
    return units_.size();
}

unit workWithUnit::getUnitByNumber(int number)
{
    return units_[number];
}

QVector<unit> workWithUnit::getPointerOnVectorUnits()
{
    return units_;
}
