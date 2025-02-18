/*
PROJECT RESPONSIBLES
ENİS DAL 
BÜNYAMİN EREN 
UĞUR ÇOBAN 
TAYFUN KARARTAŞ 
SABRİ SEVİNÇLİ 

4 DOF ROBOT ARM PROJECT
*/

#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REV 2048

#define M1_IN1 52
#define M1_IN2 50
#define M1_IN3 48
#define M1_IN4 46

#define M2_IN1 44
#define M2_IN2 42
#define M2_IN3 40
#define M2_IN4 38

#define M3_IN1 36
#define M3_IN2 34
#define M3_IN3 32
#define M3_IN4 30

#define SERVO_PIN 3

#define JOYSTICK1_X A0
#define JOYSTICK1_Y A1
#define JOYSTICK2_X A2
#define JOYSTICK2_Y A3

Stepper motor1(STEPS_PER_REV, M1_IN1, M1_IN3, M1_IN2, M1_IN4);
Stepper motor2(STEPS_PER_REV, M2_IN1, M2_IN3, M2_IN2, M2_IN4);
Stepper motor3(STEPS_PER_REV, M3_IN1, M3_IN3, M3_IN2, M3_IN4);

Servo servo;

void setup() {
  motor1.setSpeed(10); 
  motor2.setSpeed(10);
  motor3.setSpeed(10);

  servo.attach(SERVO_PIN);

  pinMode(JOYSTICK1_X, INPUT);
  pinMode(JOYSTICK1_Y, INPUT);
  pinMode(JOYSTICK2_X, INPUT);
  pinMode(JOYSTICK2_Y, INPUT);
}

void loop() {
  int joystick_value1X = analogRead(JOYSTICK1_X);
  int joystick_value1Y = analogRead(JOYSTICK1_Y);

  int joystick_value2X = analogRead(JOYSTICK2_X);
  int joystick_value2Y = analogRead(JOYSTICK2_Y);

  int dead_zone = 50;

  if (abs(joystick_value1X - 512) < dead_zone) joystick_value1X = 512;
  if (abs(joystick_value1Y - 512) < dead_zone) joystick_value1Y = 512;
  if (abs(joystick_value2X - 512) < dead_zone) joystick_value2X = 512;
  if (abs(joystick_value2Y - 512) < dead_zone) joystick_value2Y = 512;

  int motor1Steps = map(joystick_value1X, 0, 1023, -10, 10);
  int motor2Steps = map(joystick_value1Y, 0, 1023, -50, 50);
  int motor3Steps = map(joystick_value2X, 0, 1023, -50, 50);

  motor1.step(motor1Steps);
  motor2.step(motor2Steps);
  motor3.step(motor3Steps);

  int servoAngle = map(joystick_value2Y, 0, 1023, 0, 180);
  servo.write(servoAngle);

  delay(20); 
}
