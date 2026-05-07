#pragma once
#include <NewPing.h>
#include "pins.h"

struct SensorData {
    int front;
    int front_right;
    int front_left;
    int rear_right;

    int prev_front;
    int prev_front_right;
    int prev_front_left;
    int prev_rear_right;

    SensorData();
};

struct Sensors {
    SensorData data;
    
    NewPing front_sensor;
    NewPing front_left_sensor;
    NewPing front_right_sensor;
    NewPing rear_right_sensor;

    Sensors();
    void update();
};
