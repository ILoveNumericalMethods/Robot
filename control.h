#pragma once
#include <string>
#include <Arduino.h>
#include "sensors.h"
#include "motors.h"

struct Controller {
    std::string mode;
    bool warning
    MotorCommand command;

    Controller();

    void begin();
    void update_mode(const SensorData& sensors);
    void compute_command(const SensorData& sensors);

    bool danger_position(const SensorData& sensors);
    bool alignedWithWall(const SensorData& sensors);
    bool wall_on_right(const SensorData& sensors)
    bool wall_on_left(const SensorData& sensors)
};