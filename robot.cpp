#include "robot.h"

void Robot::begin() {
    Serial.begin(115200);
    Serial.setTimeout(5);
    delay(1500);

    controller.begin();
    motors.begin();
    logger.begin();
    //logger.print_header_dataset_verify();
    logger.print_header_dataset();
}

void Robot::update() {
    loop_start = millis();

    read_input();
    read_sensors();
    update_mode();
    compute_command();
    log_state();
    drive_motors();
    
    loop_delay = millis() - loop_start;
    if (loop_delay > 120) {
        Serial.print("превышено вермя цикла!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    else {delay(loop_delay);}
}

void Robot::read_input() {
    controller.handle_serial();
}

void Robot::read_sensors() {
    sensors.update();
}

void Robot::update_mode() {
    controller.update_mode(sensors);
}

void Robot::compute_command() {
    controller.compute_command(sensors);
}

void Robot::drive_motors() {
    motors.drive(controller.current_command);
}

void Robot::log_state() {
    //logger.log(sensors, controller);
    logger.log_dataset(sensors, controller);
}
