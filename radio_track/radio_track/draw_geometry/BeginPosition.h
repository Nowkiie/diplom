#pragma once
#include "ObjectDrawController.h"
#include "earth_point.hpp"
#include <optional>

namespace track
{
class BeginPosition : public ObjectDrawController
{
public:
    BeginPosition() = default;
    void drawObjects(qmapcontrol::Layer* layer) override;
    void clearObjects() override;
    ~BeginPosition() override = default;
    QString controllerName() override;
    void setOwnPoint(earth_math::earth_point own_point);
    std::optional<earth_math::earth_point> ownPoint() const;

private:
    std::optional<earth_math::earth_point> own_point_{};
};
}  // namespace track
