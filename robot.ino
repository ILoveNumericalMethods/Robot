#include "robot.h"

Robot robot;

void setup() {
    robot.begin();
}

void loop() {
    robot.update();
}
