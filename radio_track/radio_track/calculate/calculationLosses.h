#pragma once
#include "../calculate/interface_calculate_loss.h"
#include "itm.h"

namespace track::calculation::losses
{
class calcLosses : public interfaceCalcLoss
{
public:
    calcLosses() = default;
    double calculateLossesInItmModel(double height_ant_tx, double height_ant_rx,
                                     std::vector<double> profile, int climate,
                                     double frequency,
                                     int polarization) override;

private:
};
}  // namespace track::calculation::losses
