#include "Robot.h"

Robot robot;

void setup() {
    Serial.begin(9600);
    
    robot.begin();
}

void loop() {
    robot.update();
    delay(50);
}
