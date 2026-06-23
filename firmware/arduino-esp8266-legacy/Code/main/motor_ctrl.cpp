// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "motor_ctrl.h"

void motor_init() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  motor_free(LEFT_MOTOR);
  motor_free(RIGHT_MOTOR);

  analogWrite(ENA , 0);
  analogWrite(ENB , 0);
}

void motor_control(int command) {
  switch (command) {
    case 0 :
      break;
    case 1 :
      break;
    case 2 :
      break;
    case 3 :
      break;
    case 4 :
      break;
    case 5 :
      break;
  }
}

void motor_run(bool right_motor , int power) {
  if (right_motor) {
    digitalWrite(IN1 , (power > 0));
    digitalWrite(IN2 , (power < 0));
    analogWrite(ENA , int( float(abs(power)) * 255.0 / 100.0));
  } else {
    digitalWrite(IN3 , (power > 0));
    digitalWrite(IN4 , (power < 0));
    analogWrite(ENB , int( float(abs(power)) * 255.0 / 100.0));
  }
}


void motor_forward(bool right_motor , int power) {
  if (right_motor) {
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , LOW);
    analogWrite(ENA , power * 255 / 100);
  } else {
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , LOW);
    analogWrite(ENB , power * 255 / 100);
  }
}

void motor_backward(bool right_motor, int power) {
  if (right_motor) {
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , HIGH);
    analogWrite(ENA , power * 255 / 100);
  } else {
    digitalWrite(IN3 , LOW);
    digitalWrite(IN4 , HIGH);
    analogWrite(ENB , power * 255 / 100);
  }
}

void motor_free(bool right_motor) {
  if (right_motor) {
    digitalWrite(IN1 , LOW);
    digitalWrite(IN2 , LOW);
    analogWrite(ENA , 0);
  } else {
    digitalWrite(IN3 , LOW);
    digitalWrite(IN4 , LOW);
    analogWrite(ENB , 0);
  }
}

void motor_brake(bool right_motor, int power) {
  if (right_motor) {
    digitalWrite(IN1 , HIGH);
    digitalWrite(IN2 , HIGH);
    analogWrite(ENA , power * 255 / 100);
  } else {
    digitalWrite(IN3 , HIGH);
    digitalWrite(IN4 , HIGH);
    analogWrite(ENB , power * 255 / 100);
  }
}
