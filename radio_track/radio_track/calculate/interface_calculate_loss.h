#pragma once
#include <vector>

namespace track::calculation::losses
{
class interfaceCalcLoss
{
public:
    virtual double calculateLossesInItmModel(double height_ant_tx,
                                             double height_ant_rx,
                                             std::vector<double> profile,
                                             int climate, double frequency,
                                             int polarization) = 0;
    virtual ~interfaceCalcLoss() = default;
};
}  // namespace track::calculation::losses
