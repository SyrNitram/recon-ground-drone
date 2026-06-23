// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "motor_ctrl.h"
#include "wifi_com.h"


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  Serial.println("Starting");
  wifi_init();
  motor_init();

  for (int i = 0; i < 5; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

  Serial.println("Started");
}

void loop() {

  static unsigned long time1;
  static int cmd_an = 0;
  static int cmd_sp = 0;

  get_cmd(&cmd_an,  &cmd_sp);
  motor_control(cmd_an, cmd_sp);
  if (cmd_sp > 0) time1 = millis();

  if ((millis() - time1) > 3000) {
    motor_free(LEFT_MOTOR  );
    motor_free(RIGHT_MOTOR );
    cmd_an = -1;
    cmd_sp = -1;
  }
}
