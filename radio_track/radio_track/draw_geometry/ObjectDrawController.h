#pragma once
#include <memory>
#include "core/mapcontrol.h"
#include <iostream>
class ObjectDrawController
{
public:
    virtual void drawObjects(qmapcontrol::Layer* layer) = 0;
    virtual void clearObjects() = 0;
    virtual QString controllerName() = 0;
    virtual ~ObjectDrawController() = default;
};
using ObjectDrawControllerPtr = std::shared_ptr<ObjectDrawController>;
