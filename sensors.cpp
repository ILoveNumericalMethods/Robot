#include "sensors.h"

#include "config.h"

SensorData::SensorData()
    : front_cm(INVALID_DISTANCE),
      front_right_cm(INVALID_DISTANCE),
      rear_right_cm(INVALID_DISTANCE) {}

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
    data.front_cm = front_sensor.distance();
    data.front_cm = 0;
    delay(TIME_BETWEEN_SENSORS);

    data.front_right_cm = front_right_sensor.distance();
    data.front_right_cm = 0;
    delay(TIME_BETWEEN_SENSORS);

    data.rear_right_cm = rear_right_sensor.distance();
    data.rear_right_cm = 0;
    delay(TIME_BETWEEN_SENSORS);
}
