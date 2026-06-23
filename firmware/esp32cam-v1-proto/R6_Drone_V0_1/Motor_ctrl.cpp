// Recon Ground Drone - adapted file
// Original code (c) 2022-2023 Martin RYS, released under the MIT License.
// Adapted from: un0038998 / CameraCarWithPanTiltControl (MIT)
//   https://github.com/un0038998/CameraCarWithPanTiltControl
// PWM helpers from electroniqueamateur.blogspot.com and benpeoples gist (see THIRD_PARTY.md).

//L298N ON ESP32 CAM
//https://www.youtube.com/watch?v=tyY7AN132Xs
//https://github.com/un0038998/CameraCarWithPanTiltControl

//PWM
//https://electroniqueamateur.blogspot.com/2019/08/modulation-par-largeur-dimpulsion-pwm.html
//https://gist.github.com/benpeoples/3aa57bffc0f26ede6623ca520f26628c

#include "Motor_ctrl.h"

#define PWM_FRQ 40000 //40kHz
#define PWM_RES 10 //MAX 11 for 40kHz  for RES = 10 : 0<= DC <= 1023

#define MTR_L_CH 10
#define MTR_L_POW_PIN  12
#define MTR_L_DIR_PIN  13

#define MTR_R_CH 11
#define MTR_R_POW_PIN  14
#define MTR_R_DIR_PIN  15

#define PWM_MIN 50


void motor_run(bool right_motor , int power) {
  if (power > 1000) power = 1000;
  if (power < -1000) power = -1000;

  int dir_pin = right_motor ? MTR_R_DIR_PIN : MTR_L_DIR_PIN;
  int channel = right_motor ? MTR_R_CH : MTR_L_CH;
  int dc = power < 0 ?  1023 + power : power;

  digitalWrite(dir_pin, power < 0);
  ledcWrite(channel, dc);
}



void Motor_init() {
  pinMode(MTR_L_POW_PIN, OUTPUT);
  pinMode(MTR_L_DIR_PIN, OUTPUT);
  pinMode(MTR_R_POW_PIN, OUTPUT);
  pinMode(MTR_R_DIR_PIN, OUTPUT);

  pinMode(4, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(4, 0);
  digitalWrite(33, 0);

  ledcSetup(MTR_L_CH, PWM_FRQ, PWM_RES);  // canal, frequence, resolution
  ledcWrite(MTR_L_CH, 0);                 //  canal, rapport cyclique
  ledcAttachPin(MTR_L_POW_PIN, MTR_L_CH); // broche, canal

  ledcSetup(MTR_R_CH, PWM_FRQ, PWM_RES);  // canal, frequence, resolution
  ledcWrite(MTR_R_CH, 0);                 //  canal, rapport cyclique
  ledcAttachPin(MTR_R_POW_PIN, MTR_R_CH); // broche, canal
}

void Motor_setCommand(float x, float y) {
  x /= 100;
  y /= 100;

  x = -x;
  float cmd_speed = sqrt(x * x + y * y);
  float cmd_angle = atan2(y , x) + 3.14;

  if (cmd_speed > 1) cmd_speed = 1;

  float powerL = 0, powerR = 0;
  float angle = cmd_angle / 3.14;
  int pwmL, pwmR;

  if (cmd_speed > 0) {
    if (angle >= 0 && angle < 0.5) {
      powerL = cmd_speed;
      powerR = cmd_speed * (-1 + 4 * angle);
    }
    else if (angle >= 0.5 && angle < 1 ) {
      powerL = cmd_speed * (1 - 4 * (angle - 0.5));
      powerR = cmd_speed;
    }
    else if (angle >= 1 && angle < 1.5 ) {
      powerL = -cmd_speed;
      powerR = cmd_speed * (1 - 4 * (angle - 1));
    }
    else  if (angle >= 1.5  && angle <= 2) {
      powerL = cmd_speed * (-1 + 4 * (angle - 1.5));
      powerR = -cmd_speed;
    }
    /*
        if (powerL > 0) pwmL =   PWM_MIN + DELTA_PWM * (float)powerL / 100.0;
        else            pwmL = -(PWM_MIN + DELTA_PWM * -(float)powerL / 100.0);

        if (powerR > 0) pwmR =   PWM_MIN + DELTA_PWM * (float)powerR / 100.0;
        else            pwmR = -(PWM_MIN + DELTA_PWM * -(float)powerR / 100.0);
    */

    pwmL = 1000 * powerL;
    pwmR = 1000 * powerR;
  }

  else {
    pwmL = 0;
    pwmR = 0;
  }

  motor_run(0, pwmL);
  motor_run(1, pwmR);

  if (DEBUG_MTR) {
    Serial.print("Speed, angle : ");
    Serial.print(cmd_speed);
    Serial.print("  ,  ");
    Serial.print(cmd_angle);
    Serial.print("  ,  ");
    Serial.print(pwmL);
    Serial.print("  ,  ");
    Serial.println(pwmR);
  }
}
