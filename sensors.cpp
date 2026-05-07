#include "sensors.h"

#include "config.h"

SensorData::SensorData()
    : front(INVALID_DISTANCE),
      front_left(INVALID_DISTANCE),
      front_right(INVALID_DISTANCE),
      rear_right(INVALID_DISTANCE),
      prev_front(INVALID_DISTANCE),
      prev_front_left(INVALID_DISTANCE),
      prev_front_right(INVALID_DISTANCE),
      prev_rear_right(INVALID_DISTANCE) {}

Sensors::Sensors()
    : data(),
      front_sensor(PIN_TRIG_FRONT, PIN_ECHO_FRONT, INVALID_DISTANCE),
      front_left_sensor(PIN_TRIG_FRONT_LEFT, PIN_ECHO_FRONT_LEFT, INVALID_DISTANCE),
      front_right_sensor(PIN_TRIG_FRONT_RIGHT, PIN_ECHO_FRONT_RIGHT, INVALID_DISTANCE),
      rear_right_sensor(PIN_TRIG_REAR_RIGHT, PIN_ECHO_REAR_RIGHT, INVALID_DISTANCE) {}


void Sensors::update() {
    unsigned int echoTime_us;
    unsigned int startTime = millis(); 
    data.prev_front = data.front;
    //echoTime_us = front_sensor.ping_median(2);   // медианное время в мкс
    //data.front = front_sensor.convert_cm(echoTime_us); // переводим в см
    data.front = front_sensor.ping_cm(INVALID_DISTANCE);
    if (data.front == 0) {data.front = 200;}
    delay(TIME_BETWEEN_SENSORS);

    data.prev_rear_right = data.rear_right;
    //echoTime_us = rear_right_sensor.ping_median(2);   // медианное время в мкс
    //data.rear_right = rear_right_sensor.convert_cm(echoTime_us); // переводим в см
    data.rear_right = rear_right_sensor.ping_cm(INVALID_DISTANCE);
    if (data.rear_right == 0) {data.rear_right = 200;}
    delay(TIME_BETWEEN_SENSORS);

    data.prev_front_left = data.front_left;
    //echoTime_us = front_left_sensor.ping_median(2);   // медианное время в мкс
    //data.front_left = front_left_sensor.convert_cm(echoTime_us); // переводим в см
    data.front_left = front_left_sensor.ping_cm(INVALID_DISTANCE);
    if (data.front_left == 0) {data.front_left = 200;}
    delay(TIME_BETWEEN_SENSORS);


    data.prev_front_right = data.front_right;
    //echoTime_us = front_right_sensor.ping_median(2);   // медианное время в мкс
    //data.front_right = front_right_sensor.convert_cm(echoTime_us); // переводим в см
    data.front_right = front_right_sensor.ping_cm(INVALID_DISTANCE);
    if (data.front_right == 0) {data.front_right = 200;}
    delay(TIME_BETWEEN_SENSORS);
}
