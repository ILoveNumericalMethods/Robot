#include "logger.h"


bool Logger::is_command(const MotorCommand& command, int left, int right) {
    return command.left == left && command.right == right;
}

void Logger::print_command(const MotorCommand& command) {
    if (is_command(command, -70, 70) || is_command(command, 73, 153) || is_command(command, 60, 120) || is_command(command, 60, 140)) {
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        return;
    }

    
    if (is_command(command, 120, 129) || is_command(command, 100, 100)) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        Serial.print(',');
        Serial.print(0);
        return;
    }

    
    if (is_command(command, 140, 80) || is_command(command, 70, -70) || is_command(command, 120, 60) || is_command(command, 140, 60)) {
        Serial.print(0);
        Serial.print(',');
        Serial.print(0);
        Serial.print(',');
        Serial.print(1);
        return;
    }

    Serial.print(-1);
    Serial.print(',');
    Serial.print(-1);
    Serial.print(',');
    Serial.print(-1);
}


void Logger::begin() {
    start_time = millis();
}


void Logger::print_header() {
    Serial.println("time,mode,sensF,,sensFL,sensFR,sensRR,motorL,motorR");
}


void Logger::log(const Sensors& sensors, const Controller& controller) {
    const unsigned long time = millis() - start_time;

    Serial.print(time);
    Serial.print(',');
    Serial.print(controller.mode);
    Serial.print(',');
    Serial.print(sensors.data.front);
    Serial.print(',');
    Serial.print(sensors.data.front_left);
    Serial.print(',');
    Serial.print(sensors.data.front_right);
    Serial.print(',');
    Serial.print(sensors.data.rear_right);
    Serial.print(',');
    Serial.print(controller.current_command.left);
    Serial.print(',');
    Serial.println(controller.current_command.right);
}


void Logger::print_header_dataset() {
    Serial.println("front_left,prev_front_left,front,prev_front,front_right,prev_front_right,rear_right,prev_rear_right,mode1,mode2,mode3,prev_mode1,prev_mode2,prev_mode3");
}


//void Logger::print_header_dataset_verify() {
//    print_header_dataset();
//}


void Logger::log_dataset(const Sensors& sensors, const Controller& controller) { 
       
    Serial.print(sensors.data.front_left);
    Serial.print(',');

    Serial.print(sensors.data.prev_front_left);
    Serial.print(',');
    
    Serial.print(sensors.data.front);
    Serial.print(',');

    Serial.print(sensors.data.prev_front);
    Serial.print(',');

    Serial.print(sensors.data.front_right);
    Serial.print(',');

    Serial.print(sensors.data.prev_front_right);
    Serial.print(',');

    Serial.print(sensors.data.rear_right);
    Serial.print(',');

    Serial.print(sensors.data.prev_rear_right);
    Serial.print(',');

    print_command(controller.current_command);
    Serial.print(',');

    print_command(controller.previous_command);

    Serial.println();
}


//void Logger::log_dataset_verify(const Sensors& sensors, const Controller& controller) {
//    log_dataset(sensors, controller);
//}