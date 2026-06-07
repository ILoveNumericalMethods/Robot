# Robot

Autonomous wall-following robot based on Arduino Nano for the Skoltech application.

The goal of the project is to build a mobile robot that can move along the perimeter of a room or a closed area. The robot uses distance measurements to detect nearby walls, follow the boundary, pass corners, and continue moving without external control.

## Demonstration

https://github.com/user-attachments/assets/77121d81-d8dc-4211-ad28-3b47a3111cc4


### Wiring diagram

The diagram below shows the principal wiring scheme:


<img width="1978" height="2067" alt="scheme" src="https://github.com/user-attachments/assets/9276e761-54b8-4b6a-b3bd-a277ed952e91" />


## Hardware

The robot uses the following main components.

| Component      | Purpose                    |
| -------------- | -------------------------- |
| Arduino Nano   | Main microcontroller       |
| VL53L0X v0     | ToF distance sensors       |
| TB6612FNG      | Dual DC motor driver       |
| DC motors      | Left and right wheel drive |
| 6 AA batteries | Power source               |

The robot estimates its position relative to nearby walls using 4 VL53L0X distance sensors located at -45°, 0°, 45°, and 135° from the front direction. Based on these measurements, the controller computes the motor command required to keep the robot moving along the perimeter.

## Mode

The robot can operate in two modes.

| Mode     | Description                                   |
| -------- | --------------------------------------------- |
| `AUTO`   | Autonomous movement based on sensor readings  |
| `MANUAL` | Manual control from a computer through Serial |

## Sensors

The project uses VL53L0X, which is a time-of-flight sensor. It measures distance by emitting an infrared pulse and estimating the time required for the signal to return.

| Sensor direction  | Purpose                                         |
| ----------------- | ----------------------------------------------- |
| Front-left (-45°) | Early corner and obstacle detection             |
| Front (0°)        | Detect obstacles directly in front of the robot |
| Front-right (45°) | Estimate distance and direction to the wall     |
| Rear-right (135°) | Estimate distance and direction to the wall     |

## Software structure

The project is organized into separate modules.

```text
Robot/
├── robot.ino               # Arduino entry point
├── robot.h / robot.cpp     # Main robot logic
├── sensors.h / sensors.cpp # Distance sensor handling
├── motors.h / motors.cpp   # Motor control through TB6612FNG
├── control.h / control.cpp # Control mode and command logic
├── ai.h / ai.cpp           # Neural-network-based controller
├── weights.h               # Exported model weights
├── logger.h / logger.cpp   # Serial logging
├── config.h                # Main configuration constants
├── pins.h                  # Pin definitions
├── manual_control.py       # Script for manual keyboard control from PC
```

## Control loop

An update cycle consists of the following steps:

1. Read Serial commands.
2. Read distance sensors.
3. Update the current control mode.
4. Compute the motor command.
5. Log the current state.
6. Apply the command to the motors.

Simplified flow:

```text
Serial input
     ↓
Read sensors
     ↓
Update mode
     ↓
Compute motor command
     ↓
Log state
     ↓
Drive motors
```

## Neural network controller

The project includes an AI module for autonomous control. Of course, the control task can be solved by a PID regulator, for example, but the idea of the project is to build an AI-powered robot, as suggested by the name of the Master's program. There are also several practical reasons for using AI.

1. The noise characteristics of the sensors are unknown, as well as the sensor failure rate. Therefore, AI can be able to solve this problem. At the beginning of the project, I used ultrasonic sensors with a lot of noise and false measurements. With the ToF sensors that are used now, a deterministic algorithm can also work, but the AI-based approach is still more flexible.

2. A GRU can perform better than a simple algorithm because it can learn the current position of the robot relative to the wall and ignore false measurements from the sensors.

## Limitations 

The current version of the robot has several limitations. The main problems are unsafe starting procedure and messy wiring. In addition, the model was trained for a specific mechanical configuration, including the actual left and right motor rotation speeds, which were not measured separately. Therefore, if the motors or any other important part of the chassis are changed, the dataset should be collected again and the model should be retrained.
