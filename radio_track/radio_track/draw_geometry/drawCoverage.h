#pragma once
#include "ObjectDrawController.h"
#include "earth_point.hpp"
#include <optional>
#include "..\commonType.h"

namespace track
{
class drawCoverage : public ObjectDrawController
{
public:
    drawCoverage() = default;
    void drawObjects(qmapcontrol::Layer* layer) override;
    void clearObjects() override;
    ~drawCoverage() override = default;
    QString controllerName() override;
    void setOwnPoint(earth_math::earth_point own_point, type_track weight);
    std::optional<earth_math::earth_point> ownPoint() const;

private:
    std::optional<earth_math::earth_point> own_point_{};
    uint8_t count;
    QBrush drawBrush;
    type_track weight_;
};
}  // namespace track
