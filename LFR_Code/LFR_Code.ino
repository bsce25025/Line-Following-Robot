#include <Arduino.h>

#include "motors.h"
#include "encoders.h"
#include "sensors.h"
#include "pid.h"

const int BASE_SPEED = 150; 

void setup() {
  Serial.begin(115200);

  initMotors();
  initEncoders();
  initSensors();

  Serial.println("NERC LFR Initialized and Ready!");
  delay(2000);
}

void loop() {

  int linePosition = readLine();

  int motorAdjustment = calculatePID(linePosition);

  int leftSpeed = BASE_SPEED + motorAdjustment;
  int rightSpeed = BASE_SPEED - motorAdjustment;

  setMotors(leftSpeed, rightSpeed);
}