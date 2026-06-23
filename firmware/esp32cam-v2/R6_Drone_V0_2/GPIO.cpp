// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "GPIO.h"
#include <Wire.h>

#define I2C_SDA 13 // SDA Connected to GPIO 13
#define I2C_SCL 15 // SCL Connected to GPIO 15

TwoWire Expander = TwoWire(0); //I2C1 bus

void GPIO_init() {
  Expander.begin(I2C_SDA, I2C_SCL, 100000);
  delay(1000);
  GPIO_WritePin(GPIO_ALL_PIN, 0);
}

void GPIO_WritePin(int pin, bool state) {

  static char GPIO_state = B11111111;

  if (pin < LED_ALL_PIN && ((GPIO_state & (1<<pin))>>pin == !state) ) {
    if (state) GPIO_state |= 1 << pin;
    else GPIO_state &= ~(1 << pin);

    Expander.beginTransmission(0x20);
    Expander.write(GPIO_state);
    Expander.endTransmission();
    delay(1);

    if (DEBUG_GPIO)Serial.println ( GPIO_state, BIN);
  }

  if (pin == LED_ALL_PIN) {
    GPIO_WritePin(LED_OUT_PIN, state);
    GPIO_WritePin(LED_MID_PIN, state);
    GPIO_WritePin(LED_IN_PIN, state);
  }

  if (pin == MTR_ALL_PIN) {
    GPIO_WritePin(MTR_IN1_PIN, state);
    GPIO_WritePin(MTR_IN2_PIN, state);
    GPIO_WritePin(MTR_IN3_PIN, state);
    GPIO_WritePin(MTR_IN4_PIN, state);
  }

  if (pin == GPIO_ALL_PIN) {
    GPIO_WritePin(LED_ALL_PIN, state);
    GPIO_WritePin(MTR_ALL_PIN, state);
  }

}
