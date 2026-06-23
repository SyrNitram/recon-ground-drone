// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "battery_lvl.h"

#define BATTERY_C1  A0
#define BATTERY_C2  A1
#define BATTERY_C3  A2

#define VMIN_CELL 3.6
#define VLOW_CELL 3.7 
#define VMAX_CELL 4.2 

#define VMIN_BATT VMIN_CELL * 3
#define VLOW_BATT VLOW_CELL * 3
#define VMAX_BATT VMAX_CELL * 3

float cell_voltage(uint8_t  PIN) {
  return (float)analogRead(PIN) * 5.0 / 1023.0;
}

float battery_voltage() {
  return cell_voltage(BATTERY_C1) + cell_voltage(BATTERY_C2) + cell_voltage(BATTERY_C3);
}

int battery_perc() {
  return ( (battery_voltage() - VMIN_BATT) / (VMIN_BATT - VMAX_BATT) ) * 100.0;
}


bool battery_low() {
  return (cell_voltage(BATTERY_C1) < VLOW_CELL) || (cell_voltage(BATTERY_C2) < VLOW_CELL) || (cell_voltage(BATTERY_C3) < VLOW_CELL);
}
