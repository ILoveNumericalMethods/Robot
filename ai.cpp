#include "ai.h"
#include <math.h>


RobotBrain::RobotBrain() {
    begin();
}


void RobotBrain::begin() {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
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

    return 0.5f + 0.5f * static_cast<float>(x - 80) / 40.0f;
}


bool RobotBrain::is_command(const MotorCommand& command, int left, int right) {
    return command.left == left && command.right == right;
}


void RobotBrain::fill_previous_command_input(const MotorCommand& previous_command, float input[]) {
    input[8] = 0.0f;
    input[9] = 0.0f;
    input[10] = 0.0f;

    if (is_command(previous_command, 60, 120) || is_command(previous_command, 73, 153)) {
        input[8] = 1.0f;   // wa
        return;
    }

    if (is_command(previous_command, 120, 130) || is_command(previous_command, 100, 100)) {
        input[9] = 1.0f;   // w
        return;
    }

    if (is_command(previous_command, 140, 80) || is_command(previous_command, 120, 60)) {
        input[10] = 1.0f;  // wd
        return;
    }

    input[9] = 1.0f;       // default: w
}


void RobotBrain::gru_step(
    const Sensors& sensors,
    const MotorCommand& previous_command
) {
    float input[INPUT_SIZE];

    input[0] = norm_distance(sensors.data.front_left);
    input[1] = norm_distance(sensors.data.prev_front_left);

    input[2] = norm_distance(sensors.data.front);
    input[3] = norm_distance(sensors.data.prev_front);

    input[4] = norm_distance(sensors.data.front_right);
    input[5] = norm_distance(sensors.data.prev_front_right);

    input[6] = norm_distance(sensors.data.rear_right);
    input[7] = norm_distance(sensors.data.prev_rear_right);

    fill_previous_command_input(previous_command, input);

    float r[HIDDEN_SIZE];
    float z[HIDDEN_SIZE];
    float n[HIDDEN_SIZE];
    float new_h[HIDDEN_SIZE];

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        float sum_r = 0.0f;
        float sum_z = 0.0f;

        for (int j = 0; j < INPUT_SIZE; j++) {
            sum_r += pgm_read_float(&GRU_WEIGHT_IH[i][j]) * input[j];
            sum_z += pgm_read_float(&GRU_WEIGHT_IH[HIDDEN_SIZE + i][j]) * input[j];
        }

        for (int j = 0; j < HIDDEN_SIZE; j++) {
            sum_r += pgm_read_float(&GRU_WEIGHT_HH[i][j]) * h[j];
            sum_z += pgm_read_float(&GRU_WEIGHT_HH[HIDDEN_SIZE + i][j]) * h[j];
        }

        sum_r += pgm_read_float(&GRU_BIAS_IH[i]);
        sum_r += pgm_read_float(&GRU_BIAS_HH[i]);

        sum_z += pgm_read_float(&GRU_BIAS_IH[HIDDEN_SIZE + i]);
        sum_z += pgm_read_float(&GRU_BIAS_HH[HIDDEN_SIZE + i]);

        r[i] = sigmoid(sum_r);
        z[i] = sigmoid(sum_z);
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        float input_part = 0.0f;
        float hidden_part = 0.0f;

        for (int j = 0; j < INPUT_SIZE; j++) {
            input_part += pgm_read_float(
                &GRU_WEIGHT_IH[2 * HIDDEN_SIZE + i][j]
            ) * input[j];
        }

        input_part += pgm_read_float(
            &GRU_BIAS_IH[2 * HIDDEN_SIZE + i]
        );

        for (int j = 0; j < HIDDEN_SIZE; j++) {
            hidden_part += pgm_read_float(
                &GRU_WEIGHT_HH[2 * HIDDEN_SIZE + i][j]
            ) * h[j];
        }

        hidden_part += pgm_read_float(
            &GRU_BIAS_HH[2 * HIDDEN_SIZE + i]
        );

        n[i] = tanh(input_part + r[i] * hidden_part);
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        new_h[i] = (1.0f - z[i]) * n[i] + z[i] * h[i];
    }

    for (int i = 0; i < HIDDEN_SIZE; i++) {
        h[i] = new_h[i];
    }
}


int RobotBrain::compute_action() {
    float best_score = -1000000.0f;
    int best_action = 1;

    for (int action = 0; action < ACTION_SIZE; action++) {
        float score = pgm_read_float(&HEAD_BIAS[action]);

        for (int j = 0; j < HIDDEN_SIZE; j++) {
            score += pgm_read_float(&HEAD_WEIGHT[action][j]) * h[j];
        }

        if (score > best_score) {
            best_score = score;
            best_action = action;
        }
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
        return MotorCommand(73, 153);   
    }

    if (action == 1) {
        return MotorCommand(120, 130);  
    }

    return MotorCommand(140, 80);       
}