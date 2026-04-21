#pragma once
#include <Arduino.h>
#include "sensors.h"
#include "control.h"
#include "motors.h"
#include "logger.h"
#include "ai.h"

struct Robot {
    Sensors sensors;
    Controller controller;
    Motors motors;

    void begin();
    void update();

    void read_sensors();
    void update_mode();
    void compute_command();
    void drive_motors();
    void log_state();
};


