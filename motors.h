#pragma once
#include <Arduino.h>

struct MotorCommand {
    int left;
    int right;

    MotorCommand();
    MotorCommand(int leftValue, int rightValue);
};

struct Motors {
    void begin();
    void drive(const MotorCommand& command);
    void stop();
/* эти пины ориентировочные
    const int AIN1 = 2;
    const int AIN2 = 4;
    const int PWMA = 5;

    const int BIN1 = 7;
    const int BIN2 = 8;
    const int PWMB = 6;

    const int STBY = 9;
*/
    void drive_left(const int speed);
    void drive_right(const int speed);
};