#include "Robot.h"

void Robot::begin() {
    sensors.begin();
    controller.begin();
    motors.begin();
    logger.begin();
    logger.printHeader();
}

void Robot::update() {
    readUserInput();
    readSensors();
    updateMode();
    computeCommand();
    applySafety();
    driveMotors();
    logData();
}

void Robot::readUserInput() {
    controller.handleSerial();
}

void Robot::readSensors() {
    sensors.update();
}

void Robot::updateMode() {
    controller.updateMode(sensors.data);
}

void Robot::computeCommand() {
    controller.computeCommand(sensors.data);
}

void Robot::applySafety() {
    controller.applySafety(sensors.data);
}

void Robot::driveMotors() {
    motors.drive(controller.command);
}

void Robot::logData() {
    logger.log(sensors, controller);
}    

