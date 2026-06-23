// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "Server.h"
#include "Motor_ctrl.h"
#include "Leds.h"

#define DEBUG DEBUG_SERVER | DEBUG_MTR

void setup() {
    pinMode(4, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(4, 0);
  digitalWrite(33, 0);
  if (DEBUG)  Serial.begin(115200);

//  Motor_init();
/*  
  Camera_init();
  Wifi_init();
  WebServer_init();
*/

  Leds_init();


  
}

void loop() {
  Connection_handler();

}
