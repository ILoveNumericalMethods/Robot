#pragma once
#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"

struct Logger {
    unsigned long start_time;

    void begin();
    void printHeader();
    void log(const SensorData& sensors, const Controller& controller);
};