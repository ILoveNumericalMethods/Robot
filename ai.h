#pragma once

#include "config.h"
#include "sensors.h"
#include "motors.h"
#include "weights.h"


struct RobotBrain {

    float h[8];

    RobotBrain();

    float sigmoid(float x);
    float norm_distance(int x);
    
    void begin();

    MotorCommand predict(const Sensors& sensors, const MotorCommand& previous_command);

    bool is_command(const MotorCommand& command, int left, int right);

    void fill_previous_command_input(const MotorCommand& previous_command, float input[]);

    void gru_step(const Sensors& sensors, const MotorCommand& previous_command);

    int compute_action();
};