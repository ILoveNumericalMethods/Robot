#pragma once

#include <Arduino.h>
#include <iarduino_HC_SR04.h>

#include "pins.h"

struct SensorData {
    float front_cm;
    float front_right_cm;
    float rear_right_cm;

    SensorData();
};

class Sensors {
public:
    Sensors();

    void begin();
    void update();
    const SensorData& get_data() const;

private:
    SensorData data;

    iarduino_HC_SR04 front_sensor;
    iarduino_HC_SR04 front_right_sensor;
    iarduino_HC_SR04 rear_right_sensor;
};