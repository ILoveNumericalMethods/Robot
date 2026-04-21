#pragma once
#include "sensors.h"
#include "motors.h"

struct Logger {
    unsigned long start_time;

    void begin();
    void print_header();
    void log(const Sensors& sensors, const Controller& controller);
};