// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "Leds.h"
#include "GPIO.h"

void Leds_update() {
  static unsigned long i = 0;
  i++;

  if (i == 7 ) {
    GPIO_WritePin(LED_OUT_PIN, 1);
    GPIO_WritePin(LED_MID_PIN, 1);
    GPIO_WritePin(LED_IN_PIN, 1);
  } else  if (6 <= i && i <= 8 ) {
    GPIO_WritePin(LED_OUT_PIN, 1);
    GPIO_WritePin(LED_MID_PIN, 1);
    GPIO_WritePin(LED_IN_PIN, 0);
  } else  if (5 <= i && i <= 9 ) {
    GPIO_WritePin(LED_OUT_PIN, 1);
    GPIO_WritePin(LED_MID_PIN, 0);
    GPIO_WritePin(LED_IN_PIN, 0);
  } else {
    GPIO_WritePin(LED_OUT_PIN, 0);
    GPIO_WritePin(LED_MID_PIN, 0);
    GPIO_WritePin(LED_IN_PIN, 0);
  }


  if (DEBUG_LED) {
    Serial.print("LED   ");
    Serial.print((i < 3));
    Serial.print("   ");
    Serial.print((i < 2));
    Serial.print("   ");
    Serial.print((i < 1));
    Serial.print("   ");
    Serial.println(i);
  }

  if (i >= 9) i = 0;
}
