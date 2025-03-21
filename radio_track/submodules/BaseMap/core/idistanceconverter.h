#pragma once

#include <QString>
#include <memory>

namespace qmapcontrol {

class IDistanceConverter {
public:
    virtual ~IDistanceConverter() {};
    // конвертация к целевым единицам измерения
    virtual double fromKilometers(double kilometers) const = 0;
    // числовая величина дистанции
    virtual QString toText(double units, bool addLabel = true) const = 0;
};

typedef std::shared_ptr<IDistanceConverter> IDistanceConverterPtr;

} // namespace qmapcontrol