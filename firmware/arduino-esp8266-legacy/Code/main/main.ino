// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "motor_ctrl.h"
#include "led_ctrl.h"
#include "battery_lvl.h"
//#include "servo_ctrl.h"
#include <Servo.h>
#include <SoftwareSerial.h>


#define freq_led_ctrl_task 10000
#define freq_bt_ctrl_task 50
#define freq_motor_ctrl_task 50
#define freq_battery_lvl_task 2000

Servo myservo;

SoftwareSerial BTSerial(8, 9); // RX | TX

void setup() {
  //led_init();
  Serial.begin(9600);
  wifi_init()
  delay(1000);
  Serial.println("Starting");
  motor_init();
  delay(2000);
  Serial.println("Started");
}

void loop() {

  char command;
  int power = 70;
  static unsigned long time1;

  if (BTSerial.available()) {
    command = BTSerial.read();

    switch (command) {
      case 'z' :
        motor_run(LEFT_MOTOR  , power);
        motor_run(RIGHT_MOTOR , power);
        time1 = millis();
        break;
      case 's' :
        motor_run(LEFT_MOTOR  , -power);
        motor_run(RIGHT_MOTOR , -power);
        time1 = millis();
        break;
      case 'a' :
        motor_free(LEFT_MOTOR);
        motor_run(RIGHT_MOTOR , power);
        time1 = millis();
        break;
      case 'e' :
        motor_run(LEFT_MOTOR  , power);
        motor_free(RIGHT_MOTOR);
        time1 = millis();
        break;
      case 'q' :
        motor_run(LEFT_MOTOR  , -power);
        motor_run(RIGHT_MOTOR , power);
        time1 = millis();
        break;
      case 'd' :
        motor_run(LEFT_MOTOR  , power);
        motor_run(RIGHT_MOTOR , -power);
        time1 = millis();
        break;
      case ' ' :
        motor_free(LEFT_MOTOR  );
        motor_free(RIGHT_MOTOR );
        break;
      default :
        motor_free(LEFT_MOTOR  );
        motor_free(RIGHT_MOTOR );
        break;
    }
    BTSerial.println(command);
    Serial.println(command);
  }

  if((millis() - time1)> 5000){
        motor_free(LEFT_MOTOR  );
        motor_free(RIGHT_MOTOR );
  }
  /**  static int command = 0;
    static int battery_lvl = 50;

    static unsigned long t = 0;
    t++;

      if ((t%freq_led_ctrl_task) == 0) {
        /*if (battery_low())
          led_off();
        else*/
  /**       led_blink();
     }

    /* if ( t > freq_bt_ctrl_task) {
      command = get_bt_command();
     }


     if (t >= freq_motor_ctrl_task) {
      motor_control(command);
     }


     /*  if (t > freq_battery_lvl_task)
        battery_lvl = battery_perc();
  */
}
