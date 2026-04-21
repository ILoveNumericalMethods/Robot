#include "Logger.h"

void Logger::begin() {
    start_time = millis();
}

void Logger::printHeader() {
    Seral.print("time, mode, sensF, sensFR, sensR, sensBR, sensL, motorL, motorR");
}

void Logger::log(const SensorData& sensors, const Controller& controller) {
    unsigned long time = millis() - start_time;

    Serial.print(time);
    Serial.print(",");

    Serial.print(controller.mode);
    Serial.print(",");

    Serial.print(sensors.front);
    Serial.print(",");

    Serial.print(sensors.front_right);
    Serial.print(",");

    Serial.print(sensors.right);
    Serial.print(",");

    Serial.print(sensors.back_right);
    Serial.print(",");

    Serial.print(sensors.left);
    Serial.print(",");

    Serial.print(controller.command.left);
    Serial.print(",");

    Serial.println(controller.command.right);
    Serial.print(",");
}