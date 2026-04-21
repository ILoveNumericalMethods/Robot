#include "sensors.h"
#include "config.h"


SensorData::SensorData() {
    front_cm = INVALID_DISTANCE;
    front_right_cm = INVALID_DISTANCE;
    rear_right_cm = INVALID_DISTANCE;
}

Sensors::Sensors() {
    data = SensorData();
    front_sensor = iarduino_HC_SR04(PIN_TRIG_FRONT, PIN_ECHO_FRONT);
    front_right_sensor = iarduino_HC_SR04(PIN_TRIG_FRONT_RIGHT, PIN_ECHO_FRONT_RIGHT);
    rear_right_sensor = iarduino_HC_SR04(PIN_TRIG_REAR_RIGHT, PIN_ECHO_REAR_RIGHT);
}

void Sensors::begin() {
    front_sensor.averaging = AVERAGING;
    front_right_sensor.averaging = AVERAGING;
    rear_right_sensor.averaging = AVERAGING;
}

void Sensors::update() {
    data.front_cm = front_sensor.distance();
    delay(TIME_BETWEEN_SENSORS);
    data.front_cm = front_right_sensor.distance();
    delay(TIME_BETWEEN_SENSORS);
    data.front_cm = rear_right_sensor.distance();
    delay(TIME_BETWEEN_SENSORS);

}



