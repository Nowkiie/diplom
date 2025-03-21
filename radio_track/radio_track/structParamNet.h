#pragma once
#include <QVector>
#include <QString>
#include <QMetaType>
#include "struct/structEnetringData.h"

namespace structParamNet
{
enum class polarization
{
    horizontal,
    vertical
};

enum class typeSendParam
{
    unit,
    ant_system,
    send,
    recvier,
    system_link
};

Q_DECLARE_METATYPE(polarization)

struct recvier
{
    QString name;
    double sensitivity;
    int heightAnt;
};

Q_DECLARE_METATYPE(recvier)

struct sender
{
    QString name;
    double power;
    double sample_rate;
    int heightAnt;
};

Q_DECLARE_METATYPE(sender)

struct antSystem
{
    QString name;
    double antGain;
    std::pair<double, double> sectorSendRec;
    std::pair<double, double> sectorAngle;
    polarization typePolar;
};

Q_DECLARE_METATYPE(antSystem)

struct hardware
{
    antSystem ant_system;
    recvier rec;
    sender send;
};

Q_DECLARE_METATYPE(hardware)

struct unit
{
    QString name;
    QPointF coord;
    std::optional<track::structures::coordInsideLineEdit> coord_str;
    int heightRelief;
    hardware hardware_;
};

Q_DECLARE_METATYPE(unit)

struct systemLink
{
    QString name;
    QVector<unit> units;
};

Q_DECLARE_METATYPE(systemLink)
}  // namespace structParamNet
