#include "Sensors.h"

SensorData::SensorData() {
    front = 100.0f;
    front_right = 100.0f;
    right = 100.0f;
    left = 100.0f;
    back_right = 100.0f;
}

void Sensors::begin() {
    // Пока заглушка.
    // Когда придут реальные датчики, здесь будут pinMode и инициализация.
}

void Sensors::update() {
    data.front = read_front();
    delay(SENSOR_DELAY);
    data.back_right = read_back_right();
    delay(SENSOR_DELAY);
    data.front_right = read_front_right();
    delay(SENSOR_DELAY);
    data.left = read_left();
    delay(SENSOR_DELAY);
    data.right = read_right();
    delay(SENSOR_DELAY);
}

/* TO DO
float Sensors::readMockFront() {
    return ;
}

float Sensors::readMockFrontRight() {
    return ;
}

float Sensors::readMockRight() {
    return ;
}

float Sensors::readMockRearRight() {
    return ;
}

float Sensors::readMockLeft() {
    return ;
}
*/