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
#include "GPIO.h"


#define MTR_L_CH 10
#define MTR_L_POW_PIN  14

#define MTR_R_CH 11
#define MTR_R_POW_PIN  12


int pwmL = 0;
int pwmR = 0;

void motor_run(bool right_motor , int power) {

#define ACC_MAX 20
#define PWM_MIN 550

  static int PWM_L = 0;
  static int PWM_R = 0;

  if (power > 1000) power = 1000;
  if (power < -1000) power = -1000;

  int dir1_pin = right_motor ? MTR_IN2_PIN : MTR_IN3_PIN;
  int dir2_pin = right_motor ? MTR_IN1_PIN : MTR_IN4_PIN;
  int channel = right_motor ? MTR_R_CH : MTR_L_CH;
  int PWM = right_motor ? PWM_R : PWM_L;
  /*
    if ((power + PWM_MIN) < (PWM - ACC_MAX) ) PWM = PWM - ACC_MAX;
    else {
      if (power > 0)
        PWM = power * (1000 - PWM_MIN) / 1000 + PWM_MIN ;

      else if (power < 0)
        PWM = power * (1000 - PWM_MIN) / 1000 - PWM_MIN ;

      else if (power == 0)
        PWM = 0;
    }

    if (abs(PWM) < PWM_MIN) PWM = 0;
  */
  //Mise à l'echelle
  int POW = 0;
  if (power > 0) POW = PWM_MIN + power * (1000 - PWM_MIN) / 1000;
  else if (power < 0) POW = -PWM_MIN + power * (1000 - PWM_MIN) / 1000;

  Serial.print(POW);
  Serial.print("    ");

  //Limitation de l'acceleration
  if (POW - PWM > -ACC_MAX) PWM = POW;
  else if ( -PWM_MIN < PWM && PWM_MIN > PWM) PWM = (POW == 0) ? 0 : -PWM_MIN;
  else PWM = PWM - ACC_MAX;

  Serial.println(PWM);
  Serial.print("    ");

  GPIO_WritePin(dir1_pin, (PWM < 0));
  GPIO_WritePin(dir2_pin, (PWM > 0));

  ledcWrite(channel, abs(PWM));

  if (right_motor) PWM_R = PWM;
  else PWM_L = PWM;
}


void Motor_init() {
#define PWM_FRQ 40000 //40kHz
#define PWM_RES 10 //MAX 11 for 40kHz  for RES = 10 : 0<= DC <= 1023

  pinMode(MTR_L_POW_PIN, OUTPUT);
  pinMode(MTR_R_POW_PIN, OUTPUT);

  ledcSetup(MTR_L_CH, PWM_FRQ, PWM_RES);  //  canal, frequence, resolution
  ledcWrite(MTR_L_CH, 0);                 //  canal, rapport cyclique
  ledcAttachPin(MTR_L_POW_PIN, MTR_L_CH); //  broche, canal

  ledcSetup(MTR_R_CH, PWM_FRQ, PWM_RES);  //  canal, frequence, resolution
  ledcWrite(MTR_R_CH, 0);                 //  canal, rapport cyclique
  ledcAttachPin(MTR_R_POW_PIN, MTR_R_CH); //  broche, canal

}



void Motor_setCommand(float x, float y) {
  x /= 100; //-1<x<1
  y /= 100; //-1<y<1

  x = -x;

  float cmd_speed = sqrt(x * x + y * y);
  float cmd_angle = atan2(y , x) + 3.14;

  if (cmd_speed > 1) cmd_speed = 1;

  float powerL = 0, powerR = 0;
  float angle = cmd_angle / 3.14;


  if (cmd_speed > 0) {
    if (angle >= 0 && angle < 0.5) {
      powerL = cmd_speed;
      powerR = cmd_speed * (-1 + 4 * angle + 0.05);
    }
    else if (angle >= 0.5 && angle < 1 ) {
      powerL = cmd_speed * (1 - 4 * (angle - 0.55));
      powerR = cmd_speed;
    }
    else if (angle >= 1 && angle < 1.5 ) {
      powerL = -cmd_speed;
      powerR = cmd_speed * (1 - 4 * (angle - 1.05));
    }
    else  if (angle >= 1.5  && angle <= 2) {
      powerL = cmd_speed * (-1 + 4 * (angle - 1.55));
      powerR = -cmd_speed;
    }
    /*
        if (powerL > 0) pwmL =  500 + 500 * powerL;
        else            pwmL = -500 + 500 * powerL;

        if (powerR > 0) pwmR =  500 + 500 * powerR;
        else            pwmR = -500 + 500 * powerR;
    */
    pwmL = 1000 * powerL;
    pwmR = 1000 * powerR;

  } else {
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
