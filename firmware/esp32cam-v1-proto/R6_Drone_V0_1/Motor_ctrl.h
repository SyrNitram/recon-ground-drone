// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H


#include <Arduino.h>

#define DEBUG_MTR 1


void Motor_init();

void Motor_setCommand(float x, float y);

#endif
