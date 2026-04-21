#include "Control.h"

ManualKeys::ManualKeys() {
    clear();
}

void ManualKeys::clear() {
    w = false;
    a = false;
    s = false;
    d = false;
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
    keys.clear()
}

void Controller::handle_serial() {
    if (!Serial.available()) {
        return;
    }

    std::string line = Serial.readStringUntil('\n');
    line.trim();

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
        action = "auto";
        return;
    }

    if (driveMode != "MANUAL") {
        return;
    }

    if (line == "x" || line.length() == 0) {
        keys.clear();
        return;
    }

    read_key_state(line);
}

void Controller::read_key_state(const String& line) {
    keys.clear();

    for (int i = 0; i < line.length(); i++) {
        char c = line.charAt(i);

        if (c == 'w') keys.w = true;
        if (c == 'a') keys.a = true;
        if (c == 's') keys.s = true;
        if (c == 'd') keys.d = true;
    }
}


void Controller::updateMode(const SensorData& sensors) {
    if mode == "MANUAL" {
        return;
    }

    if (danger_position(sensors)) {
        if (warning) {
            mode = "STOP";
            return
        }
        else {
            warning = true;
        } 
    }
    else {
        warning = true;
    }
     
    if (mode == "TURN"){
        if (wall_on_right(sensors)) {
            mode = "FOLLOW"
            return;
        }
        else 
            return;
    }

    if (wall_on_left(sensors)) {
        mode = "TURN";
        return;
    }

    if (wall_on_right(sensors)) {
        mode = "FOLLOW";
        return;
    }

    mode = "FORWARD";
}

void Controller::compute_manual_command() {
    // конфликтующие пары
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
    action = "stop";
}

void Controller::computeCommand(const SensorData& sensors) {
    if (mode = "MANUAL") {
        comand = compute_manual_command()   
    }

    if (mode == "WAITING") {
        command = MotorCommand(0, 0);
        return;
    }

    if (mode == "TURN") {
        command = MotorCommand(100, 0);
        return;
    }

    if (mode == "FOLLOW") {
        /*put your neural network here*/
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
}


bool Controller::danger_position(const SensorData& sensors) {
    return (sensors.front <= RISE_ERROR_FRONT_DISTENCE or sensors.back_right <= RISE_ERROR_SIDE_DISTENCE or sensors.left 
        <= RISE_ERROR_SIDE_DISTENCE or sensors.right <= RISE_ERROR_SIDE_DISTENCE or sensors.front_right <= RISE_ERROR_SIDE_DISTENCE);
}

bool Controller::wall_on_right(const SensorData& sensors) {
    return  (std::max(sensors.front_right, sensors.right, sensors.back_right) < MAX_DISTANCE_TO_WALL);
}

bool Controller::wall_on_left(const SensorData& sensors) {
    return (sensors.left < sensors.right and sensors.left < MAX_DISTANCE_TO_LEFT_WALL);
}