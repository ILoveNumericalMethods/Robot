#include "config.h"
#pragma once

// ===== TB6612FNG motor driver =====

// Left motor channel A
const int PIN_L_IN_1 = 6;   
const int PIN_L_IN_2 = 4;   
const int PIN_L_PWD = 5;   

// Right motor channel B
const int PIN_R_IN_1 = 7;   
const int PIN_R_IN_2 = 8;   
const int PIN_R_PWD = 9;   

// Driver standby pin
const int PIN_STBY = 12;   // Arduino D9  -> TB6612FNG STBY


const int XSHUT_FRONT_LEFT = A2;
const int FRONT_LEFT_ADRESS = 0x2A;

const int XSHUT_FRONT = A1;
const int FRONT_ADRESS = 0x2B;

const int XSHUT_FRONT_RIGHT = A3;
const int FRONT_RIGHT_ADRESS = 0x2C;

const int XSHUT_REAR_RIGHT = A0;
const int REAR_RIGHT_ADRESS = 0x2D;

const int XSHUTS[NUMBER_OF_SENSORS] = {XSHUT_FRONT_LEFT, XSHUT_FRONT, XSHUT_FRONT_RIGHT, XSHUT_REAR_RIGHT};
const int SENSOR_ADDRESSES[NUMBER_OF_SENSORS] = {FRONT_LEFT_ADRESS, FRONT_ADRESS, FRONT_RIGHT_ADRESS, REAR_RIGHT_ADRESS};
