#include "logger.h"
#include <Arduino.h>

void Logger::begin() {
    start_time = millis();
}

void Logger::print_header() {
    Seral.print("time, mode, sensF, sensFR, sensRR, motorL, motorR");
}

void Logger::log(const Sensors& sensors, const Controller& controller) {
    unsigned long time = millis() - start_time;

    Serial.print(time);
    Serial.print(",");

    Serial.print(controller.mode);
    Serial.print(",");

    Serial.print(sensors.data.front_cm);
    Serial.print(",");

    Serial.print(sensors.data.front_right_cm);
    Serial.print(",");

    Serial.print(sensors.data.rear_right_cm);
    Serial.print(",");

    Serial.print(controller.command.left);
    Serial.print(",");

    Serial.println(controller.command.right);
    Serial.print(",");
}