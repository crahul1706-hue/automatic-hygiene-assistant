# 🤖 Automatic Hygiene Assistant Robot

An ESP32-based autonomous cleaning robot designed to reduce manual cleaning effort through obstacle detection, automatic navigation, and dust collection.

## 📌 Project Overview

The Automatic Hygiene Assistant Robot integrates embedded systems, sensors, motor control, and a suction mechanism to perform floor-cleaning operations with minimal human intervention.

The ESP32 microcontroller acts as the central control unit. It processes distance measurements from ultrasonic sensors and controls the drive motors through an L298N motor driver. A suction motor collects dust and lightweight debris into a dustbin.

## 🎯 Objectives

- Develop a low-cost autonomous floor-cleaning robot.
- Detect and avoid obstacles using ultrasonic sensors.
- Control motor speed and direction using an L298N motor driver.
- Collect dust and lightweight debris using a suction mechanism.
- Provide portable operation using a lithium-ion battery and voltage regulation.
- Demonstrate practical applications of embedded systems and robotics.

## 🛠️ Hardware Components

- ESP32 microcontroller
- Ultrasonic sensors
- L298N motor driver
- DC gear motors
- DC suction motor
- Lithium-ion battery
- Buck converter
- Capacitive proximity sensor
- Moisture sensor
- N20 gear motor
- Servo motor

*The additional sensors and motors are included in the system design; their exact functions depend on the final wiring and implementation.*

## 💻 Software and Technologies

- Embedded C/C++
- Arduino IDE
- ESP32 microcontroller programming
- Sensor interfacing
- PWM-based motor control
- Obstacle avoidance
- Embedded hardware integration

## ⚙️ Working Principle

1. **Obstacle Detection:** Ultrasonic sensors measure the distance to nearby objects.
2. **Data Processing:** The ESP32 processes the sensor readings.
3. **Motor Control:** The L298N driver controls the direction and speed of the drive motors.
4. **Navigation:** The robot moves forward and changes direction when an obstacle is detected.
5. **Dust Collection:** The suction motor draws dust and lightweight debris into a collection bin.
6. **Power Management:** A lithium-ion battery supplies power, while a buck converter provides regulated voltage to suitable electronic components.


## 🧪 Testing and Results

The project report describes indoor testing for obstacle detection, autonomous movement, and dust collection.

The robot demonstrated basic obstacle avoidance and cleaning on smooth floor surfaces. Simple navigation patterns can produce overlapping paths because the system does not implement advanced mapping and localization.

## ⚠️ Current Limitations

- Basic obstacle-avoidance navigation rather than precise mapping.
- Cleaning effectiveness depends on suction power and floor type.
- Small or low-height obstacles may not always be detected reliably.
- Additional sensor and motor functions require verification against the final hardware wiring.

## 🚀 Future Enhancements

- IoT-based remote monitoring and control.
- LiDAR-based mapping and navigation.
- AI-assisted cleaning strategies.
- Automatic docking and charging.
- Improved suction performance and dustbin capacity.
- Additional mopping functionality.


## 🎓 Project Information

- **Project Title:** Automatic Hygiene Assistant Robot
- **Project Type:** Mini Project
- **Domain:** Embedded Systems and Robotics
- **Controller:** ESP32
- **Programming Environment:** Arduino IDE
- **Institution:** REVA University
- **Department:** School of Electronics and Communication Engineering
- **Academic Year:** 2025–2026

## 👥 Project Team

-Rahul C
- Chinmay HS
- Lokesh G
- Venkatesh N

