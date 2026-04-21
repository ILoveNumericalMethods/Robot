#pragma once


struct MotorCommand {
    int left;
    int right;

    MotorCommand();
    MotorCommand(int left_value, int right_value);
};

class Motors {
public:
    void begin();
    void drive(const MotorCommand& command);
    void stop();

private:
    void drive_left(int speed);
    void drive_right(int speed);
};

void apply_channel(int in1_pin, int in2_pin, int pwm_pin, int speed);
