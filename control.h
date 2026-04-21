#pragma once
#include <string>
#include <Arduino.h>
#include "sensors.h"
#include "motors.h"

struct ManualKeys {
    bool w;
    bool a;
    bool s;
    bool d;

    ManualKeys();
    void clear();
};

struct Controller {
    std::string mode;
    ManualKeys keys
    bool warning
    MotorCommand command;

    Controller();

    void begin();
    void update_mode(const SensorData& sensors);
    void compute_command(const SensorData& sensors);

    void compute_manual_command();
    void Controller::read_key_state(const String& line);
    void Controller::handle_Serial();

    bool danger_position(const SensorData& sensors);
    bool wall_is_found(const SensorData& sensors);
};