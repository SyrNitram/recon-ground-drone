// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>

#define DEBUG_GPIO 0

#define   MTR_IN1_PIN   0
#define   MTR_IN2_PIN   1
#define   MTR_IN3_PIN   2
#define   MTR_IN4_PIN   3

#define   LED_OUT_PIN   5
#define   LED_MID_PIN   6
#define   LED_IN_PIN    7

#define   LED_ALL_PIN   8
#define   MTR_ALL_PIN   9
#define   GPIO_ALL_PIN  10

void GPIO_WritePin(int pin, bool state);
void GPIO_init();

#endif
