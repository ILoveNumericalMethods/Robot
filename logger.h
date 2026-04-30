#pragma once

#include <Arduino.h>

#include "control.h"
#include "sensors.h"

struct Logger {
    unsigned long start_time;

    void begin();
    void print_header();
    void print_header_dataset();
    void print_header_dataset_verify();
    void log(const Sensors& sensors, const Controller& controller);
    void log_dataset(const Sensors& sensors, const Controller& controller);
    void log_dataset_verify(const Sensors& sensors, const Controller& controller);
};
