#include "robot.h"

void Robot::begin() {
    Serial.begin(115200);
    Serial.setTimeout(5);
    delay(1500);

    sensors.begin();
    controller.begin();
    motors.begin();
    logger.begin();
    logger.print_header_dataset_verify();
}

void Robot::update() {
    read_input();
    read_sensors();
    update_mode();
    log_dataset_verify();
    compute_command();
    drive_motors();
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
    logger.log(sensors, controller);
}
