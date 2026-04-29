#include "logger.h"

void Logger::begin() {
    start_time = millis();
}

void Logger::print_header() {
    Serial.println("time,mode,sensF,sensFR,sensRR,motorL,motorR");
}

void Logger::log(const Sensors& sensors, const Controller& controller) {
    const unsigned long time = millis() - start_time;

    Serial.print(time);
    Serial.print(',');
    Serial.print(controller.mode);
    Serial.print(',');
    Serial.print(sensors.data.front_cm);
    Serial.print(',');
    Serial.print(sensors.data.front_right_cm);
    Serial.print(',');
    Serial.print(sensors.data.rear_right_cm);
    Serial.print(',');
    Serial.print(controller.current_command.left);
    Serial.print(',');
    Serial.println(controller.current_command.right);
}

void Logger::log_dataset(const Sensors& sensors, const Controller& controller) {
    
    Serial.print(sensors.data.front_cm);
    Serial.print(',');
    Serial.print(sensors.data.front_delta);
    Serial.print(',');
    Serial.print(sensors.data.front_right_cm);
    Serial.print(',');
    Serial.print(sensors.data.front_right_delta);
    Serial.print(',');
    Serial.print(sensors.data.rear_right_cm);
    Serial.print(',');
    Serial.print(sensors.data.rear_right_delta);
    Serial.print(',');


    if (controller.current_command.left == -70 && controller.current_command.left == 70) {   
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');

    } else if (controller.current_command.left == 80 && controller.current_command.left == 140) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');

    } else if (controller.current_command.left == 120 && controller.current_command.left == 120) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
    } else if (controller.current_command.left == 140 && controller.current_command.left == 80) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
    } else if (controller.current_command.left == 70 && controller.current_command.left == -70) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
    } else {
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
    }

    if (controller.previous_command.left == -70 && controller.previous_command.left == 70) {   
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');

    } else if (controller.previous_command.left == 80 && controller.previous_command.left == 140) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');

    } else if (controller.previous_command.left == 120 && controller.previous_command.left == 120) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
    } else if (controller.previous_command.left == 140 && controller.previous_command.left == 80) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
    } else if (controller.previous_command.left == 70 && controller.previous_command.left == -70) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
    } else {
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
        Serial.print(-1);
        Serial.print(',');
    }
}

