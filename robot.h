#pragma once
#include "sensors.h"
#include "control.h"
#include "motors.h"
#include "logger.h"
#include "ai.h"

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


