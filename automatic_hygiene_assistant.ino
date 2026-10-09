#include <Arduino.h>
#include <ESP32Servo.h>

// ---------- CONFIRMED L298N PINS ----------
const int ENA = 27;
const int IN1 = 25;
const int IN2 = 26;
const int ENB = 13;
const int IN3 = 14;
const int IN4 = 12;

// ---------- CONFIRMED ULTRASONIC PINS ----------
const int TRIG_L = 5;
const int ECHO_L = 18;
const int TRIG_F = 22;
const int ECHO_F = 19;
const int TRIG_R = 17;
const int ECHO_R = 4;

// ---------- PROPOSED ADDITIONAL PINS: WIRE TO MATCH ----------
const int CAPACITIVE_SENSOR_PIN = 34;  // digital OUT; input-only GPIO
const int MOISTURE_SENSOR_PIN   = 35;  // digital OUT; input-only GPIO
const int SERVO_SIGNAL_PIN      = 23;
const int N20_IN1               = 16;  // N20 driver input 1
const int N20_IN2               = 21;  // N20 driver input 2
const int SUCTION_DRIVER_PIN    = 32;  // MOSFET/driver input, active-HIGH

// ---------- CONFIGURATION ----------
const int BASE_SPEED = 140;
const int SLOW_SPEED = 100;
const int TURN_SPEED = 150;
const int OBSTACLE_DISTANCE_CM = 20;
const int VERY_CLOSE_DISTANCE_CM = 12;
const unsigned long REVERSE_TIME_MS = 250;
const unsigned long TURN_TIME_MS = 450;
const unsigned long CLEAR_FORWARD_MS = 300;

const int SERVO_HOME_DEG = 0;     // Adjust for your mechanism
const int SERVO_WORK_DEG = 90;    // Adjust for your mechanism
const int WET_LEVEL = HIGH;       // Change to LOW if your sensor is active-LOW

Servo mechanismServo;
unsigned long lastStatusPrint = 0;

// ---------- ULTRASONIC DISTANCE ----------
long getDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);
  if (duration == 0) return 300;
  return (long)(duration * 0.0343f / 2.0f);
}

// ---------- DRIVE MOTORS VIA L298N ----------
void setLeftMotor(int direction, int pwm) {
  pwm = constrain(pwm, 0, 255);
  if (direction > 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  } else if (direction < 0) {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); pwm = 0;
  }
  analogWrite(ENA, pwm);
}

void setRightMotor(int direction, int pwm) {
  pwm = constrain(pwm, 0, 255);
  if (direction > 0) {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (direction < 0) {
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); pwm = 0;
  }
  analogWrite(ENB, pwm);
}

void stopRobot() {
  setLeftMotor(0, 0);
  setRightMotor(0, 0);
}

void forward(int pwm) {
  setLeftMotor(1, pwm); setRightMotor(1, pwm);
}

void backward(int pwm) {
  setLeftMotor(-1, pwm); setRightMotor(-1, pwm);
}

void pivotLeft(int pwm) {
  setLeftMotor(-1, pwm); setRightMotor(1, pwm);
}

void pivotRight(int pwm) {
  setLeftMotor(1, pwm); setRightMotor(-1, pwm);
}

// ---------- N20 MOTOR VIA ASSUMED TWO-INPUT DRIVER ----------
void n20Stop() {
  digitalWrite(N20_IN1, LOW);
  digitalWrite(N20_IN2, LOW);
}

void n20Forward() {
  digitalWrite(N20_IN1, HIGH);
  digitalWrite(N20_IN2, LOW);
}

void n20Reverse() {
  digitalWrite(N20_IN1, LOW);
  digitalWrite(N20_IN2, HIGH);
}

// ---------- OBSTACLE AVOIDANCE ----------
void avoidObstacle() {
  stopRobot();
  delay(120);

  backward(SLOW_SPEED);
  delay(REVERSE_TIME_MS);
  stopRobot();
  delay(100);

  long leftCM = getDistanceCM(TRIG_L, ECHO_L);
  long rightCM = getDistanceCM(TRIG_R, ECHO_R);

  if (leftCM > rightCM) pivotLeft(TURN_SPEED);
  else pivotRight(TURN_SPEED);

  delay(TURN_TIME_MS);
  stopRobot();
  delay(100);

  forward(SLOW_SPEED);
  delay(CLEAR_FORWARD_MS);
  stopRobot();
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(TRIG_L, OUTPUT); pinMode(ECHO_L, INPUT);
  pinMode(TRIG_F, OUTPUT); pinMode(ECHO_F, INPUT);
  pinMode(TRIG_R, OUTPUT); pinMode(ECHO_R, INPUT);

  pinMode(CAPACITIVE_SENSOR_PIN, INPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);

  pinMode(N20_IN1, OUTPUT);
  pinMode(N20_IN2, OUTPUT);
  n20Stop();

  pinMode(SUCTION_DRIVER_PIN, OUTPUT);
  digitalWrite(SUCTION_DRIVER_PIN, LOW);  // suction OFF during startup

  mechanismServo.setPeriodHertz(50);
  mechanismServo.attach(SERVO_SIGNAL_PIN, 500, 2400);
  mechanismServo.write(SERVO_HOME_DEG);

  digitalWrite(TRIG_L, LOW);
  digitalWrite(TRIG_F, LOW);
  digitalWrite(TRIG_R, LOW);
  stopRobot();

  Serial.println("Automatic Hygiene Assistant Robot");
  Serial.println("Check all proposed additional wiring before running.");
}

void loop() {
  long leftCM = getDistanceCM(TRIG_L, ECHO_L);
  long frontCM = getDistanceCM(TRIG_F, ECHO_F);
  long rightCM = getDistanceCM(TRIG_R, ECHO_R);

  int capacitiveState = digitalRead(CAPACITIVE_SENSOR_PIN);
  int moistureState = digitalRead(MOISTURE_SENSOR_PIN);
  bool wetDetected = (moistureState == WET_LEVEL);

  // Cleaning outputs: suction runs while robot is in its cleaning loop.
  // N20 motor runs forward; confirm this matches its actual mechanical purpose.
  digitalWrite(SUCTION_DRIVER_PIN, HIGH);
  n20Forward();

  // Servo moves to work position when moisture is detected; otherwise home.
  // This behavior is an assumption and should be changed to match the mechanism.
  mechanismServo.write(wetDetected ? SERVO_WORK_DEG : SERVO_HOME_DEG);

  if (millis() - lastStatusPrint >= 500) {
    lastStatusPrint = millis();
    Serial.print("L="); Serial.print(leftCM);
    Serial.print(" F="); Serial.print(frontCM);
    Serial.print(" R="); Serial.print(rightCM);
    Serial.print(" cm | Capacitive="); Serial.print(capacitiveState);
    Serial.print(" | Moisture="); Serial.print(moistureState);
    Serial.print(" | WetDetected="); Serial.println(wetDetected ? "YES" : "NO");
  }

  if (frontCM <= VERY_CLOSE_DISTANCE_CM) {
    avoidObstacle();
  } else if (frontCM <= OBSTACLE_DISTANCE_CM) {
    forward(SLOW_SPEED);
    delay(80);
    stopRobot();
    avoidObstacle();
  } else {
    forward(BASE_SPEED);
    delay(60);
  }
}
