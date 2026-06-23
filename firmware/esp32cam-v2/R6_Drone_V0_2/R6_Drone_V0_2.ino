// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "Server.h"
#include "GPIO.h"
#include "Motor_ctrl.h"
#include "Leds.h"

#define DEBUG DEBUG_SERVER | DEBUG_MTR | DEBUG_LED

void setup() {

  delay(3000);
  pinMode(4, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(4, 0);
  digitalWrite(33, 1);

 // if (DEBUG)  
  Serial.begin(115200);

  GPIO_init();

  Motor_init();

  Camera_init();
  Wifi_init();
  WebServer_init();
}

void loop() {
  Connection_handler();
}
