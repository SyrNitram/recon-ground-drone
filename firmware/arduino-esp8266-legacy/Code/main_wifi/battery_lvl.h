// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef BATTERY_LVL_H
#define BATTERY_LVL_H

#include <Arduino.h>

float cell_voltage(uint8_t  PIN);
float battery_voltage();
int battery_perc();
bool battery_low();


#endif
