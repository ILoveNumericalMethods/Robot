#pragma once

// TB6612FNG



// Ultrasonic
const int PIN_TRIG_REAR_RIGHT = 10;
const int PIN_ECHO_REAR_RIGHT       = 11;
const int PIN_TRIG_FRONT_RIGHT = 12;
const int PIN_ECHO_FRONT_RIGHT       = 11;
const int PIN_TRIG_FRONT  = 12;
const int PIN_ECHO_FRONT        = 12;




// ===== TB6612FNG motor driver =====

// Left motor channel A
const int PIN_R_IN_1 = 2;   // Arduino D2  -> TB6612FNG AIN1
const int PIN_R_IN_2 = 4;   // Arduino D4  -> TB6612FNG AIN2
const int PIN_R_PWD = 5;   // Arduino D5  -> TB6612FNG PWMA, PWM pin

// Right motor channel B
const int PIN_L_IN_1 = 7;   // Arduino D7  -> TB6612FNG BIN1
const int PIN_L_IN_2 = 8;   // Arduino D8  -> TB6612FNG BIN2
const int PIN_L_PWD = 6;   // Arduino D6  -> TB6612FNG PWMB, PWM pin

// Driver standby pin
const int PIN_STBY = 9;   // Arduino D9  -> TB6612FNG STBY


// ===== Ultrasonic sensors HY-SRF04 =====
/*
// Front sensor
const int PIN_TRIG_FRONT = 10;  // Arduino D10 -> Front sensor TRIG
const int PIN_ECHO_FRONT = 11;  // Arduino D11 -> Front sensor ECHO

// Right sensor
const int PIN_TRIG_RIGHT = 12;  // Arduino D12 -> Right sensor TRIG
const int PIN_ECHO_RIGHT = A0;  // Arduino A0  -> Right sensor ECHO

// Left sensor
const int PIN_TRIG_LEFT = A1;   // Arduino A1  -> Left sensor TRIG
const int PIN_ECHO_LEFT = A2;   // Arduino A2  -> Left sensor ECHO
*/
