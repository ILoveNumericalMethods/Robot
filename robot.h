#pragma once

#include "control.h"
#include "logger.h"
#include "motors.h"
#include "sensors.h"

struct Robot {
    Sensors sensors;
    Controller controller;
    Motors motors;
    Logger logger;

    void begin();
    void update();
    void read_input();
    void read_sensors();
    void update_mode();
    void compute_command();
    void drive_motors();
    void log_state();
};
