Automatic Hygiene Assistant Robot

An ESP32-based autonomous cleaning robot designed to reduce manual effort through obstacle detection, automatic navigation, and dust collection.

Project Overview

The Automatic Hygiene Assistant Robot combines embedded systems, sensors, motor control, and a suction mechanism to perform floor-cleaning operations with minimal human intervention.

The ESP32 processes sensor readings and controls the robot's movement. Ultrasonic sensors detect obstacles, while DC gear motors enable navigation and a suction motor collects dust and lightweight debris.

Objectives

- Develop an affordable autonomous floor-cleaning robot.
- Detect and avoid obstacles using ultrasonic sensors.
- Control motor speed and direction using an L298N motor driver.
- Collect dust using a DC suction motor and dustbin.
- Provide portable operation using a lithium-ion battery and voltage regulation.

Hardware Components

- ESP32 microcontroller
- Ultrasonic sensor
- L298N motor driver
- DC gear motors
- DC suction motor
- Lithium-ion battery
- Buck converter
- Capacitive proximity sensor
- N20 gear motor
- Servo motor

Technologies Used

- Embedded C/C++
- Arduino IDE
- ESP32 microcontroller programming
- Sensor interfacing
- PWM-based motor control
- Obstacle avoidance
- Embedded hardware integration

Working Principle

1. **Sensing:** Ultrasonic sensors measure the distance to nearby obstacles.
2. **Processing:** The ESP32 processes sensor data and determines the robot's next movement.
3. **Motor Control:** The L298N driver controls the direction and speed of the drive motors.
4. **Navigation:** The robot moves forward and changes direction when an obstacle is detected.
5. **Cleaning:** The suction motor collects dust and lightweight debris into a dustbin.
6. **Power Management:** A lithium-ion battery supplies power, while a buck converter regulates voltage for the electronics.

Results

Indoor testing demonstrated obstacle avoidance, autonomous movement, and dust collection on smooth floor surfaces. The robot uses simple zigzag or random navigation patterns, so some cleaning-path overlap may occur.

Future Improvements

- IoT-based remote monitoring and control
- LiDAR-based mapping and navigation
- AI-assisted cleaning strategies
- Automatic docking and charging
- Improved suction performance
- Additional mopping functionality

 Project Information

- **Project Type:** Mini Project
- **Domain:** Embedded Systems and Robotics
- **Controller:** ESP32
- **Development Environment:** Arduino IDE
- **Institution:** REVA University, School of Electronics and Communication Engineering

Project Team

-Rahul C
- Chinmay HS
- Lokesh G
- Venkatesh N
