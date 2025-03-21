#pragma once
#include <QPointF>
#include <QMetaType>
#include <QString>
#include <optional>

namespace track::structures
{

struct coordInsideLineEdit
{
    QString latDegree;
    QString latSec;
    QString latArcsec;
    QString lonDegree;
    QString lonSec;
    QString lonArcsec;
    QString lonPolarCoord;
    QString latPolarCoord;
};

Q_DECLARE_METATYPE(coordInsideLineEdit);

struct enteringDataInChoosePoints
{
    coordInsideLineEdit coord_begin;
    coordInsideLineEdit coord_end;
};

Q_DECLARE_METATYPE(enteringDataInChoosePoints);

struct coordPointsInChoosePoints
{
    QPointF coordBegin;
    QPointF coordEnd;
};

Q_DECLARE_METATYPE(coordPointsInChoosePoints);

enum class typeCalculation
{
    on_send,
    on_recv,
};

struct paramForDrawing
{
    //common parameter
    std::optional<QPointF> coordBegin;
    std::optional<coordInsideLineEdit> coordBeginStr;

    //parameter for radiotrack
    std::optional<QPointF> coordEnd;
    std::optional<coordInsideLineEdit> coordEndStr;

    //common parameter for coverage
    double radius;
    typeCalculation type;

    //parameter for radio coverage and radiotrack
    int numberChoosingHardwareSender;
    int numberChoosingHardwareRecvier;
    int numberChoosingHardwareAntSystem;
    int numberChoosingClimate;

    //parameter for visual coverage
    int heightAntSend;
    int heightAntRec;
};

Q_DECLARE_METATYPE(paramForDrawing);

}  // namespace track::structures
