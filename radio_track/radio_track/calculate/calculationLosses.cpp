#include "calculationLosses.h"

using namespace track::calculation::losses;

double calcLosses::calculateLossesInItmModel(double height_ant_tx,
                                             double height_ant_rx,
                                             std::vector<double> profile,
                                             int climate, double frequency,
                                             int polarization)
{
    //todo(PtakhovaA): заменить частоту на значения из параметров
    double N_0 = 301.0;
    double epsilon = 15;
    double sigma = 0.005;
    int mdvar = 3;
    double time = 60;
    double location = 60;
    double situation = 70;
    double A__db{};
    long warnings;
    IntermediateValues interValues;

    int r = ITM_P2P_TLS_Ex(height_ant_tx, height_ant_rx, profile.data(),
                           climate, N_0, frequency, polarization, epsilon,
                           sigma, mdvar, time, location, situation, &A__db,
                           &warnings, &interValues);

    return A__db;
}
