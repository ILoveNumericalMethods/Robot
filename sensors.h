#pragma once
#include <Wire.h>
#include <VL53L0X.h>
#include "config.h"
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
    
    VL53L0X front_sensor;
    VL53L0X front_left_sensor;
    VL53L0X front_right_sensor;
    VL53L0X rear_right_sensor;

    int read_sensor_cm(VL53L0X& sensor);
    void begin();
    void update();

    bool i2c_alive(uint8_t address); 
    void print_i2c_state();

};
