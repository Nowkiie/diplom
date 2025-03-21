#pragma once
#include <QPointF>
#include <QVector>
#include "calculate/calculateTile.h"
#include "settings/formUnit.h"
#include "structParamNet.h"
#include "struct/structEnetringData.h"

struct paramWhenSelectPointsOnMap
{
    QPointF coordPoint;
    int numberPoint;
};
Q_DECLARE_METATYPE(paramWhenSelectPointsOnMap);

struct chooseParamPointsInterface
{
    std::pair<int, QVariant> param;
};
Q_DECLARE_METATYPE(chooseParamPointsInterface);

struct paramResultCalculateRt
{
    QVector<int> profileHeights;
    QVector<double> distances;
    double freq; //todo(PtakhovaA): удалить частоту из структуры, получать частоту из параметров системы
};
Q_DECLARE_METATYPE(paramResultCalculateRt);

struct paramWhenDraw3D
{
    QVector<track::tile> tiles;
    QImage fileHeights;
    QImage fileTexture;
};

Q_DECLARE_METATYPE(paramWhenDraw3D);

struct paramWhenUseUnits
{
    int numberFirstUnit;
    int numberSecondUnit;
};

Q_DECLARE_METATYPE(paramWhenUseUnits);

struct paramForDrawCoverageWithUnit
{
    //common parameter
    double radius;
    int numberUnit = -1;
    track::structures::typeCalculation type;

    //parameter for radio coverage
    int numberChoosingHardwareSender;
    int numberChoosingHardwareRecvier;
    int numberChoosingHardwareAntSystem;
    int numberChoosingClimate;

    //parameter for visual coverage
    int heightAntSend;
    int heightAntRec;
};

Q_DECLARE_METATYPE(paramForDrawCoverageWithUnit);

struct paramHardware
{
    QVector<structParamNet::antSystem> ant_system{};
    QVector<structParamNet::recvier> recv{};
    QVector<structParamNet::sender> send{};
};

Q_DECLARE_METATYPE(paramHardware);

struct paramForInitialDataOnUnitsInterface
{
    QVector<structParamNet::sender> senders{};
    QVector<structParamNet::recvier> recviers{};
    QVector<structParamNet::antSystem> antSystems{};
    QVector<structParamNet::unit> units;
};

Q_DECLARE_METATYPE(paramForInitialDataOnUnitsInterface);