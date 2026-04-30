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

float RobotBrain::crop_distance(int distance) {
    return static_cast<float>(distance) / MAX_DISTANCE;
}


void RobotBrain::gru_step(const Sensors& sensors, const MotorCommand& previous_command) {
    float input[11];
    input[0] = crop_distance(sensors.data.front_cm);
    input[1] = crop_distance(sensors.data.front_delta);
    input[2] = crop_distance(sensors.data.front_right_cm);
    input[3] = crop_distance(sensors.data.front_right_delta);
    input[4] = crop_distance(sensors.data.rear_right_cm);
    input[5] = crop_distance(sensors.data.rear_right_delta);
    
    if (previous_command.left == -70 && previous_command.right == 70) {   
        input[6] = 1.0f;
        input[7] = 0.0f;
        input[8] = 0.0f;
        input[9] = 0.0f;
        input[10] = 0.0f;

    } else if (previous_command.left == 80 && previous_command.right == 140) {
        input[6] = 0.0f;
        input[7] = 1.0f;
        input[8] = 0.0f;
        input[9] = 0.0f;
        input[10] = 0.0f;

    } else if (previous_command.left == 120 && previous_command.right == 120) {
        input[6] = 0.0f;
        input[7] = 0.0f;
        input[8] = 1.0f;
        input[9] = 0.0f;
        input[10] = 0.0f;
    } else if (previous_command.left == 140 && previous_command.right == 80) {
        input[6] = 0.0f;
        input[7] = 0.0f;
        input[8] = 0.0f;
        input[9] = 1.0f;
        input[10] = 0.0f;
    } else if (previous_command.left == 70 && previous_command.right == -70) {
        input[6] = 0.0f;
        input[7] = 0.0f;
        input[8] = 0.0f;
        input[9] = 0.0f;
        input[10] = 1.0f;
    }
    
    float r[8];
    float z[8];
    float n[8];
    float new_h[8];

    for (int i = 0; i < 8; i++) {
        float sum_r = 0.0f;
        float sum_z = 0.0f;

        for (int j = 0; j < 11; j++) {
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

        for (int j = 0; j < 11; j++) {
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
    int best_action = 0;

    Serial.print(',');
    for (int action = 0; action < 5; action++) {
        float score = pgm_read_float(&HEAD_BIAS[action]);

        for (int j = 0; j < 8; j++) {
            score += pgm_read_float(&HEAD_WEIGHT[action][j]) * h[j];
        }
        if (score > best_score) {
            best_score = score;
            best_action = action;
        }
        Serial.print(score);
        Serial.print(',');
    }

    return best_action;
}



MotorCommand RobotBrain::predict(const Sensors& sensors, const MotorCommand& previous_command){
    gru_step(sensors, previous_command);
    int action = compute_action();
    Serial.println(action);
    if (action == 0){
        return MotorCommand(-70, 70); 
    } else if (action == 1){
        return MotorCommand(80, 140);
    } else if (action == 2){
        return MotorCommand(120, 120);
    } else if (action == 3){
        return MotorCommand(140, 80);
    } else {
        return MotorCommand(70, -70);
    }
}    
