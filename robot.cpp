#include "robot.h"

void Robot::begin() {
    Serial.begin(9600);
    delay(1500);
    
    sensors.begin();
    controller.begin();
    motors.begin();
    logger.begin();
    logger.print_header();
}

void Robot::update() {
    read_input();
    read_sensors();
    update_mode();
    compute_command();
    drive_motors();
    log_state();
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
    motors.drive(controller.command);
}

void Robot::log_state() {
    logger.log(sensors, controller);
}
