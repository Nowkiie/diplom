#pragma once

#include "ObjectDrawController.h"
#include "earth_point.hpp"
#include <optional>

namespace track
{
class endCoveragePos : public ObjectDrawController
{
public:
    endCoveragePos() = default;
    void drawObjects(qmapcontrol::Layer* layer) override;
    void clearObjects() override;
    ~endCoveragePos() override = default;
    QString controllerName() override;
    void setOwnPoint(earth_math::earth_point own_point);
    std::optional<earth_math::earth_point> ownPoint() const;

private:
    std::optional<earth_math::earth_point> own_point_{};
};
}  // namespace track
