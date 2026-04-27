#include "control.h"

#include "ai.h"
#include "config.h"

ManualKeys::ManualKeys() {
    clear();
}

void ManualKeys::clear() {
    w = false;
    a = false;
    s = false;
    d = false;
}

bool ManualKeys::empty() const {
    return !w && !a && !s && !d;
}

Controller::Controller() {
    mode = "WAITING";
    warning = false;
    command = MotorCommand(0, 0);
}

void Controller::begin() {
    mode = "WAITING";
    warning = false;
    command = MotorCommand(0, 0);
    keys.clear();
}

void Controller::handle_serial() {
    if (!Serial.available()) {
        return;
    }

    String last_move_line = "";

    while (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        line.trim();

        if (line.length() == 0) {
            continue;
        }

        if (line == "m" || line == "u") {
            handle_serial_line(line);
        } else {
            last_move_line = line;
        }
    }

    if (last_move_line.length() > 0) {
        handle_serial_line(last_move_line);
    }
}

void Controller::handle_serial_line(const String& line) {
    if (line == "m") {
        mode = "MANUAL";
        keys.clear();
        command = MotorCommand(0, 0);
        return;
    }

    if (line == "u") {
        mode = "WAITING";
        keys.clear();
        command = MotorCommand(0, 0);
        return;
    }

    if (mode != "MANUAL") {
        return;
    }

    if (line == "x") {
        keys.clear();
        command = MotorCommand(0, 0);
        return;
    }

    read_key_state(line);
}

void Controller::read_key_state(const String& line) {
    keys.clear();

    for (int i = 0; i < line.length(); ++i) {
        char c = line.charAt(i);

        if (c == 'w') {
            keys.w = true;
        } else if (c == 'a') {
            keys.a = true;
        } else if (c == 's') {
            keys.s = true;
        } else if (c == 'd') {
            keys.d = true;
        }
    }
}

void Controller::update_mode(const Sensors& sensors) {
    if (mode == "MANUAL") {
        return;
    }

    /*
    if (danger_position(sensors)) {
        if (warning) {
            mode = "STOP";
            return;
        }
        warning = true;
    } else {
        warning = false;
    }
    */

    if (mode == "FOLLOW") {
        return;
    }

    if (wall_is_found(sensors)) {
        mode = "FOLLOW";
        return;
    }

    mode = "FORWARD";
}

void Controller::compute_manual_command() {
    if (keys.empty()) {
        command = MotorCommand(0, 0);
        return;
    }

    if ((keys.w && keys.s) || (keys.a && keys.d)) {
        command = MotorCommand(0, 0);
        return;
    }

    if (keys.w && keys.d) {
        command = MotorCommand(140, 80);
        return;
    }

    if (keys.w && keys.a) {
        command = MotorCommand(80, 140);
        return;
    }

    if (keys.s && keys.d) {
        command = MotorCommand(-140, -80);
        return;
    }

    if (keys.s && keys.a) {
        command = MotorCommand(-80, -140);
        return;
    }

    if (keys.w) {
        command = MotorCommand(120, 120);
        return;
    }

    if (keys.s) {
        command = MotorCommand(-100, -100);
        return;
    }

    if (keys.a) {
        command = MotorCommand(-90, 90);
        return;
    }

    if (keys.d) {
        command = MotorCommand(90, -90);
        return;
    }

    command = MotorCommand(0, 0);
}

void Controller::compute_command(const Sensors& sensors) {
    if (mode == "MANUAL") {
        compute_manual_command();
        return;
    }

    if (mode == "WAITING") {
        command = MotorCommand(0, 0);
        return;
    }

    if (mode == "FOLLOW") {
        AiController ai;
        command = ai.predict(sensors.data, sensors.data);
        return;
    }

    if (mode == "STOP") {
        command = MotorCommand(0, 0);
        return;
    }

    if (mode == "FORWARD") {
        command = MotorCommand(90, 90);
        return;
    }

    command = MotorCommand(0, 0);
}

bool Controller::danger_position(const Sensors& sensors) {
    return sensors.data.front_cm <= RISE_ERROR_DISTENCE ||
           sensors.data.rear_right_cm <= RISE_ERROR_DISTENCE ||
           sensors.data.front_right_cm <= RISE_ERROR_DISTENCE;
}

bool Controller::wall_is_found(const Sensors& sensors) {
    return sensors.data.front_cm < MAX_DISTANCE_TO_WALL ||
           sensors.data.front_right_cm < MAX_DISTANCE_TO_WALL ||
           sensors.data.rear_right_cm < MAX_DISTANCE_TO_WALL;
}
