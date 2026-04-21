#include "Motors.h"


MotorCommand::MotorCommand() {
    left = 0;
    right = 0;
}

MotorCommand::MotorCommand(int leftValue, int rightValue) {
    left = leftValue;
    right = rightValue;
}

void Motors::begin() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
}

void Motors::drive(const MotorCommand& command) {
    driveLeft(command.left);
    driveRight(command.right);
}

void Motors::stop() {
    driveLeft(0);
    driveRight(0);
}

void Motors::driveLeft(int speed) {

    if (speed > 0) {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, speed);
    } else if (speed < 0) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        analogWrite(PWMA, -speed);
    } else {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, 0);
    }
}

void Motors::driveRight(int speed) {

    if (speed > 0) {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
        analogWrite(PWMB, speed);
    } else if (speed < 0) {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        analogWrite(PWMB, -speed);
    } else {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
        analogWrite(PWMB, 0);
    }
}