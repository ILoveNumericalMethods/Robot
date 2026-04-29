#include "sensors.h"

#include "config.h"

SensorData::SensorData()
    : front_cm(INVALID_DISTANCE),
      front_right_cm(INVALID_DISTANCE),
      rear_right_cm(INVALID_DISTANCE),
      front_delta(INVALID_DISTANCE),
      front_right_delta(INVALID_DISTANCE),
      rear_right_delta(INVALID_DISTANCE) {}

Sensors::Sensors()
    : data(),
      front_sensor(PIN_TRIG_FRONT, PIN_ECHO_FRONT),
      front_right_sensor(PIN_TRIG_FRONT_RIGHT, PIN_ECHO_FRONT_RIGHT),
      rear_right_sensor(PIN_TRIG_REAR_RIGHT, PIN_ECHO_REAR_RIGHT) {}

void Sensors::begin() {
    front_sensor.averaging = AVERAGING;
    front_right_sensor.averaging = AVERAGING;
    rear_right_sensor.averaging = AVERAGING;
}

void Sensors::update() {
    int temp_dist = front_sensor.distance();

    data.front_delta = temp_dist - data.front_cm;
    data.front_cm = temp_dist;
    delay(TIME_BETWEEN_SENSORS);

    temp_dist = front_right_sensor.distance();
    data.front_right_delta = temp_dist - data.front_right_cm;
    data.front_right_cm = temp_dist;
    delay(TIME_BETWEEN_SENSORS);

    temp_dist = rear_right_sensor.distance();
    data.rear_right_delta = temp_dist - data.rear_right_cm;
    data.rear_right_cm = temp_dist;
    delay(TIME_BETWEEN_SENSORS);
}
