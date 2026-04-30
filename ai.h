#pragma once
#include "config.h"
#include "motors.h"
#include "sensors.h"
#include "weights.h"



struct RobotBrain {

    float h[8];

    RobotBrain();
    void begin();
    
    float crop_distance(int distance);
    float sigmoid(float x);

    void gru_step(const Sensors& sensors, const MotorCommand& previous_command);
    int compute_action();
    MotorCommand predict(const Sensors& sensors, const MotorCommand& previous_command);
    
};