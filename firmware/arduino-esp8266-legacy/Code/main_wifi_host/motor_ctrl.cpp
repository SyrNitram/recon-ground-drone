// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "motor_ctrl.h"

#define PWM_MIN 55.0
#define PWM_MAX 80.0
#define DELTA_PWM (PWM_MAX-PWM_MIN)

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
  TCCR1B = TCCR1B & 0b11111001; //Set PWM frequency of 9 and 10 to 31250 Hz/1 Cause problem with Servo.h
}

void motor_control(int cmd_angle, int cmd_speed) {
  int powerL = 0, powerR = 0;
  float angle = (float)cmd_angle / 3.14;
  float pwmL, pwmR;

  if (cmd_speed > 0) {
    if (angle >= 0 && angle < 5) {
      powerL = cmd_speed;
      powerR = -cmd_speed * (1.0 - (angle - 0.0) / 2.5);
    }
    else if (angle >= 5 && angle < 10 ) {
      powerL = cmd_speed * (1.0 - (angle - 5.0) / 2.5);
      powerR = cmd_speed;
    }
    else if (angle >= 10 && angle < 15 ) {
      powerL = -cmd_speed;
      powerR = cmd_speed * (1.0 - (angle - 10.0) / 2.5);
    }
    else  if (angle >= 15  && angle <= 20) {
      powerL = -cmd_speed * (1.0 - (angle - 15.0) / 2.5);
      powerR = -cmd_speed;
    }



    if (powerL > 0) pwmL =   PWM_MIN + DELTA_PWM * (float)powerL / 100.0;
    else            pwmL = -(PWM_MIN + DELTA_PWM * -(float)powerL / 100.0);

    if (powerR > 0) pwmR =   PWM_MIN + DELTA_PWM * (float)powerR / 100.0;
    else            pwmR = -(PWM_MIN + DELTA_PWM * -(float)powerR / 100.0);

    motor_run(LEFT_MOTOR,  (int)pwmL);
    motor_run(RIGHT_MOTOR, (int)pwmR);
  }

  else if (cmd_speed == 0) {
    motor_free(LEFT_MOTOR  );
    motor_free(RIGHT_MOTOR );
  }
  /*
    Serial.print(cmd_angle);
    Serial.print("       ");
    Serial.print(cmd_speed);
    Serial.print("       ");
    Serial.print(pwmL);
    Serial.print("       ");
    Serial.println(pwmR);*/
}

void motor_run(bool right_motor , int power) {
  if (power > 100) power = 100;
  if (power < -100) power = -100;

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
