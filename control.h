#pragma once

#include <Arduino.h>
#include "ai.h"
#include "motors.h"
#include "sensors.h"

struct ManualKeys {
    bool w;
    bool a;
    bool s;
    bool d;

    ManualKeys();

    void clear();
    bool empty() const;
};

struct Controller {
    String mode;
    ManualKeys keys;
    bool warning;
    MotorCommand current_command;
    MotorCommand previous_command;
    RobotBrain ver33;

    Controller();

    void begin();

    void update_mode(const Sensors& sensors);
    void compute_command(const Sensors& sensors);
    void compute_manual_command();

    void handle_serial();
    void handle_serial_line(const String& line);
    void read_key_state(const String& line);

    bool danger_position(const Sensors& sensors);
    bool wall_is_found(const Sensors& sensors);
};