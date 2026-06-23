// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>

#define DEBUG_WIFI    0
#define DEBUG_WS      0
#define DEBUG_CAM     0
#define DEBUG_SERVER  DEBUG_WIFI|DEBUG_WS|DEBUG_CAM

//WIFI
int Wifi_init();

//WS
int WebServer_init();
void Connection_handler();

//CAM
int Camera_init();

#endif
