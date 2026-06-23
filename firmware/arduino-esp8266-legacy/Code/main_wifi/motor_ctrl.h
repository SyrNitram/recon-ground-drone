// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include <Arduino.h>

#define ENA 5
#define ENB 6
#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A4

#define LEFT_MOTOR  0
#define RIGHT_MOTOR 1


void motor_init();

void motor_control(int command);

void motor_run(bool right_motor , int power);
void motor_forward(bool right_motor , int power);
void motor_backward(bool right_motor, int power);
void motor_brake(bool right_motor, int power);
void motor_free(bool right_motor);

#endif
