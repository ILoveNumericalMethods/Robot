#pragma once
#include <iarduino_HC_SR04.h>
#include "pins.h"

struct SensorData {
    int front_cm;
    int front_right_cm;
    int rear_right_cm;

    SensorData();
};

class Sensors {
public:
    SensorData data;

    Sensors();

    void begin();
    void update();
    S
    iarduino_HC_SR04 front_sensor;
    iarduino_HC_SR04 front_right_sensor;
    iarduino_HC_SR04 rear_right_sensor;
};