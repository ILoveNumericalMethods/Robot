#include "ai.h"
#include <math.h>


RobotBrain::RobotBrain() {
    begin();
}


void RobotBrain::begin() {
    for (int i = 0; i < 8; i++) {
        h[i] = 0.0f;
    }
}


float RobotBrain::sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}


float RobotBrain::norm_distance(int x) {
    if (x <= 80) {
        return 0.5f * static_cast<float>(x) / 80.0f;
    }

    return 0.5f + 0.5f * static_cast<float>(x - 80) / 320.0f;
}


float RobotBrain::norm_delta(int x) {
    int sign = 1;

    if (x < 0) {
        sign = -1;
        x = -x;
    }

    float norm_abs;

    if (x <= 20) {
        norm_abs = 0.5f * static_cast<float>(x) / 20.0f;
    } else {
        norm_abs = 0.5f + 0.5f * static_cast<float>(x - 20) / 380.0f;
    }

    return static_cast<float>(sign) * norm_abs;
}

float RobotBrain::norm_angle(int x) {
    int sign = 1;

    if (x < 0) {
        sign = -1;
        x = -x;
    }

    float norm_abs;

    if (x <= 40) {
        norm_abs = 0.5f * static_cast<float>(x) / 40.0f;
    } else {
        norm_abs = 0.5f + 0.5f * static_cast<float>(x - 40) / 360.0f;
    }

    return static_cast<float>(sign) * norm_abs;
}

float RobotBrain::norm_wall(float x) {
    int sign = 1;

    if (x < 0) {
        sign = -1;
        x = -x;
    }

    float norm_abs;

    if (x <= 20) {
        norm_abs = 0.5f * x / 20.0f;
    } else {
        norm_abs = 0.5f + 0.5f * x - 20.0f / 380.0f;
    }

    return static_cast<float>(sign) * norm_abs;
}



bool RobotBrain::is_command(const MotorCommand& command, int left, int right) {
    return command.left == left && command.right == right;
}


void RobotBrain::fill_previous_command_input(const MotorCommand& previous_command, float input[]) {
    input[6] = 0.0f;
    input[7] = 0.0f;
    input[8] = 0.0f;

    if (is_command(previous_command, 60, 120) || is_command(previous_command, 80, 140)) {
        input[6] = 1.0f;
        return;
    }

    if (is_command(previous_command, 120, 120) || is_command(previous_command, 100, 100)
    ) {
        input[7] = 1.0f;
        return;
    }

    if (is_command(previous_command, 140, 80) || is_command(previous_command, 120, 60)) {
        input[8] = 1.0f;
        return;
    }

    input[7] = 1.0f;
}


void RobotBrain::gru_step(
    const Sensors& sensors,
    const MotorCommand& previous_command
) {
    float input[9];

    input[0] = norm_distance(sensors.data.front_cm);
    input[1] = norm_delta(sensors.data.front_delta);

    input[2] = norm_distance(sensors.data.front_right_cm);
    input[3] = norm_delta(sensors.data.front_right_delta);

    input[4] = norm_distance(sensors.data.rear_right_cm);
    input[5] = norm_delta(sensors.data.rear_right_delta);

    //input[6] = norm_angle(sensors.data.right_angle);
    //input[7] = norm_wall(sensors.data.distance_to_wall);

    fill_previous_command_input(previous_command, input);

    //debug
    //input[8]=0;
    //input[9]=1;
    //input[10]=0;
    //debug

    float r[8];
    float z[8];
    float n[8];
    float new_h[8];

    for (int i = 0; i < 8; i++) {
        float sum_r = 0.0f;
        float sum_z = 0.0f;

        for (int j = 0; j < 9; j++) {
            sum_r += pgm_read_float(&GRU_WEIGHT_IH[i][j]) * input[j];
            sum_z += pgm_read_float(&GRU_WEIGHT_IH[8 + i][j]) * input[j];
        }

        for (int j = 0; j < 8; j++) {
            sum_r += pgm_read_float(&GRU_WEIGHT_HH[i][j]) * h[j];
            sum_z += pgm_read_float(&GRU_WEIGHT_HH[8 + i][j]) * h[j];
        }

        sum_r += pgm_read_float(&GRU_BIAS_IH[i]);
        sum_r += pgm_read_float(&GRU_BIAS_HH[i]);

        sum_z += pgm_read_float(&GRU_BIAS_IH[8 + i]);
        sum_z += pgm_read_float(&GRU_BIAS_HH[8 + i]);

        r[i] = sigmoid(sum_r);
        z[i] = sigmoid(sum_z);
    }

    for (int i = 0; i < 8; i++) {
        float input_part = 0.0f;
        float hidden_part = 0.0f;

        for (int j = 0; j < 9; j++) {
            input_part += pgm_read_float(&GRU_WEIGHT_IH[16 + i][j]) * input[j];
        }

        input_part += pgm_read_float(&GRU_BIAS_IH[16 + i]);

        for (int j = 0; j < 8; j++) {
            hidden_part += pgm_read_float(&GRU_WEIGHT_HH[16 + i][j]) * h[j];
        }

        hidden_part += pgm_read_float(&GRU_BIAS_HH[16 + i]);

        n[i] = tanh(input_part + r[i] * hidden_part);
    }

    for (int i = 0; i < 8; i++) {
        new_h[i] = (1.0f - z[i]) * n[i] + z[i] * h[i];
    }

    for (int i = 0; i < 8; i++) {
        h[i] = new_h[i];
    }
}


int RobotBrain::compute_action() {
    float best_score = -1000000.0f;
    int best_action = 1; 

    for (int action = 0; action < 3; action++) {
        float score = pgm_read_float(&HEAD_BIAS[action]);

        for (int j = 0; j < 8; j++) {
            score += pgm_read_float(&HEAD_WEIGHT[action][j]) * h[j];
        }

        if (score > best_score) {
            best_score = score;
            best_action = action;
        }

       // Serial.print(score);
        //Serial.print(',');
    }

    return best_action;
}


MotorCommand RobotBrain::predict(
    const Sensors& sensors,
    const MotorCommand& previous_command
) {
    gru_step(sensors, previous_command);

    int action = compute_action();

    if (action == 0) {
        return MotorCommand(60, 140);   // wa
    }

    if (action == 1) {
        return MotorCommand(120, 120);  // w
    }

    return MotorCommand(140, 60);       // wd
}