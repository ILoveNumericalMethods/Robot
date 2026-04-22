#include "motors.h"
#include "config.h"
#include "pins.h"

void apply_channel(int in1_pin, int in2_pin, int pwm_pin, int speed) {
    const int pwm_value = abs(speed);

    if (speed > 0) {
        digitalWrite(in1_pin, HIGH);
        digitalWrite(in2_pin, LOW);
    } else if (speed < 0) {
        digitalWrite(in1_pin, LOW);
        digitalWrite(in2_pin, HIGH);
    } else {
        digitalWrite(in1_pin, LOW);
        digitalWrite(in2_pin, LOW);
    }

    analogWrite(pwm_pin, pwm_value);
}

MotorCommand::MotorCommand() : left(0), right(0) {}

MotorCommand::MotorCommand(int left_value, int right_value)
    : left(left_value), right(right_value) {}

void Motors::begin() {
    pinMode(PIN_L_IN_1, OUTPUT);
    pinMode(PIN_L_IN_2, OUTPUT);
    pinMode(PIN_L_PWD, OUTPUT);
    pinMode(PIN_R_IN_1, OUTPUT);
    pinMode(PIN_R_IN_2, OUTPUT);
    pinMode(PIN_R_PWD, OUTPUT);
    pinMode(PIN_STBY, OUTPUT);

    digitalWrite(PIN_STBY, HIGH);
    stop();
}

void Motors::drive(const MotorCommand& command) {
    digitalWrite(PIN_STBY, HIGH);
    drive_left(command.left);
    drive_right(command.right);
}

void Motors::stop() {
    drive_left(0);
    drive_right(0);
}

void Motors::drive_left(int speed) {
    apply_channel(PIN_L_IN_1, PIN_L_IN_2, PIN_L_PWD, speed);
}

void Motors::drive_right(int speed) {
    apply_channel(PIN_R_IN_1, PIN_R_IN_2, PIN_R_PWD, speed);
}
