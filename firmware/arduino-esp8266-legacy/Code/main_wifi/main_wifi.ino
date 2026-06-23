// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "motor_ctrl.h"
#include "wifi_com.h"


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  wifi_init();
  delay(100);
  Serial.println("Starting");
  digitalWrite(13, HIGH);

  motor_init();
  delay(200);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  Serial.println("Started");
}

void loop() {

  static int power = 60;
  static unsigned long time1;
  int cmd = get_cmd();

  switch (cmd) {
    case 10 :// Toggle LED
      digitalWrite(13, !digitalRead(13));
      break;
    case 17 : //NW
      motor_free(LEFT_MOTOR  );
      motor_run(RIGHT_MOTOR , power);
      break;
    case 18 ://Forward
      motor_run(LEFT_MOTOR  , power);
      motor_run(RIGHT_MOTOR , power);
      break;
    case 19 ://NE
      motor_run(LEFT_MOTOR  , power);
      motor_free(RIGHT_MOTOR );
      break;
    case 14 ://Left
      motor_run(LEFT_MOTOR  , -power);
      motor_run(RIGHT_MOTOR , power);
      break;
    case 15 ://STOP
      motor_free(LEFT_MOTOR  );
      motor_free(RIGHT_MOTOR );
      break;
    case 16 ://Right
      motor_run(LEFT_MOTOR  , power);
      motor_run(RIGHT_MOTOR , -power);
      break;
    case 11 ://SW
      motor_free(LEFT_MOTOR  );
      motor_run(RIGHT_MOTOR , -power);
      break;
    case 12 ://Backward
      motor_run(LEFT_MOTOR  , -power);
      motor_run(RIGHT_MOTOR , -power);
      break;
    case 13 ://SE
      motor_run(LEFT_MOTOR  , -power);
      motor_free(RIGHT_MOTOR );
      break;
    default :
      if (cmd >= 20 && cmd < 30){
        power = 60 + 4 * (cmd - 20);
      Serial.println(power);
      }
      break;
  }
  if ((cmd > 10) && (cmd < 20)) {
    time1 = millis();
  }

  if (cmd != 100)
    Serial.println(cmd);


  if ((millis() - time1) > 3000) {
    motor_free(LEFT_MOTOR  );
    motor_free(RIGHT_MOTOR );
  }
  //delay(100);


}
