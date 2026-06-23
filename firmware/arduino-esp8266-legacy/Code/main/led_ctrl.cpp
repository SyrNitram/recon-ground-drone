// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "led_ctrl.h"

#define LED1 9
#define LED2 10
#define LED3 8
#define LED4 12
#define LED5 11
#define LED6 7
#define TIME 25

void led_init() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);

  digitalWrite(LED1, LOW);   
  digitalWrite(LED2, LOW);   
  digitalWrite(LED3, LOW);   
  digitalWrite(LED4, LOW);  
  digitalWrite(LED5, LOW);   
  digitalWrite(LED6, LOW);  
}

void led_off() {
  digitalWrite(LED1, LOW);   
  digitalWrite(LED2, LOW);   
  digitalWrite(LED3, LOW);   
  digitalWrite(LED4, LOW);   
  digitalWrite(LED5, LOW);   
  digitalWrite(LED6, LOW);   
}

void led_blink() {
  digitalWrite(LED1, HIGH);   
  digitalWrite(LED2, HIGH);   
  digitalWrite(LED3, HIGH);   
  digitalWrite(LED4, HIGH);   
  digitalWrite(LED5, HIGH);   
  digitalWrite(LED6, HIGH);   
  delay(TIME);                       
  digitalWrite(LED1, LOW);    
  digitalWrite(LED6, LOW);    
  delay(TIME);                      
  digitalWrite(LED2, LOW);    
  digitalWrite(LED5, LOW);    
  delay(TIME);                       
  digitalWrite(LED3, LOW);    
  digitalWrite(LED4, LOW);    
  delay(TIME);                       
  digitalWrite(LED3, HIGH);    
  digitalWrite(LED4, HIGH);    
  delay(TIME);                       
  digitalWrite(LED2, HIGH);    
  digitalWrite(LED5, HIGH);    
  delay(TIME);                       
  digitalWrite(LED1, HIGH);    
  digitalWrite(LED6, HIGH);    
}
