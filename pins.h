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


// ===== Ultrasonic sensors HY-SRF04 =====

// Front sensor
const int PIN_TRIG_FRONT = A3;  // Arduino D10 -> Front sensor TRIG
const int PIN_ECHO_FRONT = A4;  // Arduino D11 -> Front sensor ECHO

// Right sensor
const int PIN_TRIG_FRONT_RIGHT = A1;  // Arduino D12 -> Right sensor TRIG
const int PIN_ECHO_FRONT_RIGHT = A2;  // Arduino A0  -> Right sensor ECHO

// Left sensor
const int PIN_TRIG_REAR_RIGHT = 13;   // Arduino A1  -> Left sensor TRIG
const int PIN_ECHO_REAR_RIGHT = A2;   // Arduino A2  -> Left sensor ECHO

