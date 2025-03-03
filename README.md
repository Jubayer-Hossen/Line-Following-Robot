# Line Following Robot

A sophisticated line following robot implementation using Arduino Nano, featuring PID control for smooth line tracking.

## Overview

This project implements a line following robot that uses 5 IR sensors to detect and follow a line path. The robot employs PID (Proportional-Integral-Derivative) control for precise movement and features automatic course correction capabilities.

## Hardware Requirements

- Arduino Nano Microcontroller
- L298N Motor Driver Module
- 5 Channel Infrared Reflective PIR Sensor Module
- DC Motors (2x)
- Power Supply
- Chassis and Wheels

## Pin Configuration

### Motor Connections
| Motor | Function  | Arduino Pin |
|-------|-----------|-------------|
| Left  | Forward   | D8          |
| Left  | Backward  | D7          |
| Left  | PWM       | D6          |
| Right | Forward   | D10         |
| Right | Backward  | D9          |
| Right | PWM       | D11         |

### IR Sensor Connections
| Sensor Number | Arduino Pin |
|---------------|-------------|
| Sensor 0      | A0         |
| Sensor 1      | A1         |
| Sensor 2      | A2         |
| Sensor 3      | A3         |
| Sensor 4      | A4         |

## Features

- PID-based line following algorithm
- Automatic course correction
- Variable speed control
- Detection of line interruptions and intersections
- Smooth turning capabilities

## How It Works

### Sensor Reading
The robot uses 5 IR sensors to detect the line position. Each sensor returns an analog value that is converted to a binary value (0 or 1) based on a threshold. The sensor readings are used to calculate the position of the line relative to the center of the sensor array.

### PID Control
The robot implements PID control with the following parameters:
- Base speed: 120
- Proportional constant (Kp): 190
- Derivative constant (Kd): 500

The PID controller helps maintain smooth movement by:
1. Calculating the error between the current position and desired position
2. Applying proportional and derivative corrections
3. Adjusting motor speeds accordingly

### Navigation Logic
- The robot follows the line by continuously adjusting motor speeds based on PID calculations
- When all sensors detect the line (total = 5), it handles intersections
- When no sensors detect the line (total = 0), the robot stops until it finds the line again
- The robot can detect and handle left and right turns automatically

## Code Structure

The code is organized into several main functions:
- `setup()`: Initializes pin modes and serial communication
- `loop()`: Main program loop that calls the PID line following function
- `Sensor_reading()`: Reads and processes sensor values
- `PID_LINE_FOLLOW()`: Implements the PID control algorithm
- `motor()`: Controls the motors with speed and direction

## Installation

1. Clone this repository or download the code
2. Connect the hardware according to the pin configuration
3. Upload the code to your Arduino Nano using the Arduino IDE
4. Place the robot on a line with good contrast against the background
5. Power on the robot and adjust the sensor threshold if necessary

## Adjustable Parameters

You can modify these parameters in the code to tune the robot's performance:
- `threshold`: Sensor reading threshold (default: 600)
- `kp`: Proportional constant (default: 190)
- `kd`: Derivative constant (default: 500)
- `base_speed`: Default motor speed (default: 120)
- `turn_speed`: Speed during turns (default: 120)

## Troubleshooting

If the robot is not following the line properly:
1. Check if all sensors are working and properly aligned
2. Verify the threshold value is appropriate for your line and surface
3. Adjust the PID constants (kp, kd) for better performance
4. Ensure proper power supply to both the Arduino and motors
5. Verify all connections according to the pin configuration

## Contributing

Feel free to fork this project and submit pull requests with improvements. You can also open issues for bug reports or feature requests.

## License

This project is open-source and available under the MIT License.

## Author

Jubayer Hossen

## Acknowledgments

- Thanks to the Arduino community for their valuable resources
- Special thanks to contributors and testers