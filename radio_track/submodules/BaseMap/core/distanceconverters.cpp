#include "distanceconverters.h"

#include <cmath>

const char* const M = "м";
const char* const Km = "км";
const char* const Mile = "мил";
const char* const NM = "ммил";

QString numberToText(double number, int precision) {
    double mod;
    const auto tail = std::modf(number, &mod);
    if (static_cast<int>(tail * precision) == 0) {
        return QString::number(number, 'f', 0);
    }

    return QString::number(number, 'f', precision);
}

QString textWithLabel(const QString& value, const char* const label) {
    return QString("%1 %2").arg(value).arg(label);
}

namespace qmapcontrol {

DistanceKilometersConverter::DistanceKilometersConverter()
    : IDistanceConverter() {}

double DistanceKilometersConverter::fromKilometers(double kilometers) const {
    return kilometers;
}

QString DistanceKilometersConverter::toText(double kilometers, bool addLabel) const {
    // Если выводим с label, то для расстояния меньше 1 км выводим результат в метрах
    if (addLabel) {
        const bool lessThenKm = kilometers < 1.0;
        const double value = lessThenKm ? kilometers * 1000.0 : kilometers;
        const auto textValue = numberToText(value, lessThenKm ? 0 : 2);

        return textWithLabel(textValue, lessThenKm ? M : Km);
    }

    // Без label выводим только расстояние в километрах
    return numberToText(kilometers, 2);
}

//-----------------------------------------------------------------------------
DistanceMilesConverter::DistanceMilesConverter()
    : IDistanceConverter() {}

double DistanceMilesConverter::fromKilometers(double kilometers) const {
    return kilometers / 1.609347218694;
}

QString DistanceMilesConverter::toText(double miles, bool addLabel) const {
    QString textValue = numberToText(miles, miles >= 1 ? 2 : 3);
    if (addLabel) {
        return textWithLabel(textValue, Mile);
    }

    return textValue;
}

//-----------------------------------------------------------------------------
DistanceNauticalMilesConverter::DistanceNauticalMilesConverter()
    : IDistanceConverter() {}

double DistanceNauticalMilesConverter::fromKilometers(double kilometers) const {
    return kilometers / 1.852;
}

QString DistanceNauticalMilesConverter::toText(double nauticalMiles, bool addLabel) const {
    QString textValue = numberToText(nauticalMiles, nauticalMiles >= 1 ? 2 : 3);
    if (addLabel) {
        return textWithLabel(textValue, NM);
    }

    return textValue;
}

}  // namespace qmapcontrol
