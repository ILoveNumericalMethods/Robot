#pragma once
#include <Arduino.h>
#include "sensors.h"
#include "control.h"
#include "motors.h"
#include "logger.h"

struct Robot {
    Sensors sensors;
    Controller controller;
    Motors motors;

    void begin();
    void update();

    void readSensors();
    void updateMode();
    void computeCommand();
    void driveMotors();
    void logData();
};


