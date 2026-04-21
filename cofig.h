#pragma once

//distances in cm
const float TARGET_WALL_DISTENCE = 30.0f;
const float RISE_ERROR_FRONT_DISTENCE = 10.0f;
const float RISE_ERROR_SIDE_DISTENCE = 5.0f;

const float MAX_DISTANCE_TO_RIGHT_WALL = 150.0f;
const float MAX_DISTANCE_TO_LEFT_WALL = 50.0f;

// time in ms
const int SENSOR_DELAY = 10;

const int PWM_MAX = 180;
const int PWM_MIN = 60;
const int PWM_BASE = 110;



const float FILTER_ALPHA = 0.5f;

const unsigned long SENSOR_PERIOD_MS = 40;
const unsigned long CONTROL_PERIOD_MS = 50;
const unsigned long LOG_PERIOD_MS = 100;


