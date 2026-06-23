// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "Leds.h"
#include <Wire.h>

#define I2C_SDA 15 // SDA Connected to GPIO 15
#define I2C_SCL 14 // SCL Connected to GPIO 14



TwoWire Expander = TwoWire(0); //I2C1 bus


void Leds_init() {
  Expander.begin(I2C_SDA, I2C_SCL, 100000);
  digitalWrite(33,true);
  Expander.beginTransmission(0x20);
  Expander.write(B00000000);
  Expander.write(B00000000);
  Expander.endTransmission();
  delay(1000);
  while (1) {
    digitalWrite(33,false);
    Expander.beginTransmission(0x20);
    Expander.write(B11111111);
    Expander.write(B11111111);
    Expander.endTransmission();
    delay(1000);
    digitalWrite(33,true);
    Expander.beginTransmission(0x20);
    Expander.write(B00000000);
    Expander.write(B00000000);
    Expander.endTransmission();
    delay(1000);
  }
}





/*
  hw_timer_t *My_timer = NULL;

  void IRAM_ATTR onTimer() {
  // digitalWrite(LED, !digitalRead(LED));
  }

  void Leds_init() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  My_timer = timerBegin(0, 80, true); //Tim_nbr (0-3), Prescaler, Count_up
  timerAttachInterrupt(My_timer, &onTimer, true); //attach onTImer function to the interrupt
  timerAlarmWrite(My_timer, 1000000, true); //counter value triggering the interrupt
  timerAlarmEnable(My_timer); //Enable interrupt

  }
*/
