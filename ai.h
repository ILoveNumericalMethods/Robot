#pragma once

#include "motors.h"
#include "sensors.h"

struct AiController {

    void begin();
    MotorCommand predict(const SensorData& data, const SensorData& previous_data) const;
};
