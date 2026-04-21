#pragma once
#include <Arduino.h>

struct SensorData {
    float front;
    float left;
    float right;
    float front_right;
    float back_right;

    SensorData();
};

struct Sensors {
    SensorData data;

    void begin();
    void update();

    float read_front();
    float read_front_right();
    float read_right();
    float read_left();
    float read_back_right();
};