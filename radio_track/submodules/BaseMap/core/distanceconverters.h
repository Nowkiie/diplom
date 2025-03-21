#pragma once

#include "core/idistanceconverter.h"

namespace qmapcontrol {

class DistanceKilometersConverter : public IDistanceConverter {
public:
    DistanceKilometersConverter();
    double fromKilometers(double kilometers) const override;
    QString toText(double kilometers, bool addLabel = true) const override;
};

class DistanceMilesConverter : public IDistanceConverter {
public:
    DistanceMilesConverter();
    double fromKilometers(double kilometers) const override;
    QString toText(double miles, bool addLabel = true) const override;
};

class DistanceNauticalMilesConverter : public IDistanceConverter {
public:
    DistanceNauticalMilesConverter();
    double fromKilometers(double kilometers) const override;
    QString toText(double nauticalMiles, bool addLabel = true) const override;
};

} // namespace qmapcontrol