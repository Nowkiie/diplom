#pragma once
#include <QStringList>
#include <earth_point.hpp>

namespace track
{
class PelengCaption
{
public:
    static QString placeString(int64_t latitude_ms, int64_t longitude_ms)
    {
        earth_math::earth_point point{
            earth_math::degree_latitude::from_milliseconds(latitude_ms),
            earth_math::degree_longitude::from_milliseconds(longitude_ms)};

        return QString::fromLocal8Bit(
            point.to_string(earth_math::show_seconds).c_str());
    }

    static earth_math::earth_point placePoint(int64_t latitude_ms,
                                              int64_t longitude_ms)
    {
        earth_math::earth_point point{
            earth_math::degree_latitude::from_milliseconds(latitude_ms),
            earth_math::degree_longitude::from_milliseconds(longitude_ms)};

        return point;
    }
};
}  // namespace track
