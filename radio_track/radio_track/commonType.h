#pragma once
#include <earth_point.hpp>
#include <qvector.h>
#include <map>

struct DataItem
{
    QPointF coordRefencePoint;
};

enum class type_track
{
    closed,
    half_closed,
    half_open,
    open
};

using DataItems = QVector<DataItem>;
using EarthPoint = earth_math::earth_point;
using coordCoverageVisible_ = QVector<QPointF>;
using weight = std::map<type_track, QPointF>;
using test = std::map<int, weight>;
