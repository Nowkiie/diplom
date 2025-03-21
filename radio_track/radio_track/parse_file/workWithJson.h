#pragma once
#include <fstream>
#include "../../submodules/json.hpp"
#include "../structParamNet.h"
#include "../structForSendParam.h"

using namespace structParamNet;
using nlohmann::json;

class workWithJson
{
public:
    workWithJson() = default;
    void writeToJson(QVector<unit> units);
    void writeToJsonHardware(paramHardware listHardware);
    QVector<unit> readFromJson();
    paramHardware readFromJsonHardware();
};
