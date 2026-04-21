#include "robot.h"

void Robot::begin() {
    sensors.begin();
    controller.begin();
    motors.begin();
    logger.begin();
    //ai.begin();
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
    controller.handleSerial();
}

void Robot::read_sensors() {
    sensors.update();
}

void Robot::update_mode() {
    controller.update_mode(sensors.data);
}

void Robot::compute_command() {
    controller.compute_command(sensors.data);
}

void Robot::drive_motors() 
    motors.drive(controller.command);
}

void Robot::log_state() {
    logger.log(sensors, controller);
}    

