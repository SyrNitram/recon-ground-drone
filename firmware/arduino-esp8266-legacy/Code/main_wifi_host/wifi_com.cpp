// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "wifi_com.h"
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>

#define DEBUG false

SoftwareSerial esp8266(2, 3);

bool sendData(String command, const int timeout, boolean debug);
bool sendAT(String command, const int timeout, boolean debug);
void SendWebPage(int connectionId);

char AP_IP[15] = "";
char ST_IP[15] = "";

void wifi_init() {
  delay(500);
  esp8266.begin(9600);
  delay(500);
  sendAT("RST", 3000, DEBUG); // reset module
  delay(2000);
  sendAT("CWMODE=3", 1000, DEBUG); // configure as station + ap
  sendAT("CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"", 10000, DEBUG); // configure as wifi client
  sendAT("CIFSR", 1000, DEBUG); // get ip address
  sendAT("CIPMUX=1", 1000, DEBUG); // configure for multiple connections
  sendAT("CIPSERVER=1,80", 1000, DEBUG); // turn on server on port 80
}

void get_cmd(int *cmd_angle, int *cmd_speed) {
  delay(100);
  *cmd_angle = -1;
  *cmd_speed = -1;

  if (esp8266.available()) // check if the esp is sending a message
  { /*
      String resp = "";
      while (esp8266.available()) {
       resp += (char)esp8266.read();
      }
      Serial.print(resp);

    */
    if (esp8266.find("+IPD,"))
    {
      while (esp8266.available() < 20);

      int connectionId = esp8266.read() - 48; // get the connection id so that we can then disconnect

      if (esp8266.find("GET /")) {
        char c = esp8266.read();
        if (c == '?') {
          if (esp8266.find("an=")) {
            cmd_angle = (esp8266.read() - 48) * 10;
            if (esp8266.read() == '.') cmd_angle += (esp8266.read() - 48);

            if (esp8266.find("sp=")) {
              cmd_speed = (esp8266.read() - 48) * 10;
              if (*cmd_speed != 0) cmd_speed += (esp8266.read() - 48);
            } else *cmd_angle = -1;
          }

          String closeCommand = "CIPCLOSE=";
          closeCommand += connectionId;
          sendAT(closeCommand, 500, DEBUG); // close connection
          delay(50);


        } else if (c == ' ') {
          SendWebPage(connectionId);

          String closeCommand = "CIPCLOSE=";
          closeCommand += connectionId;
          sendAT(closeCommand, 500, DEBUG); // close connection
          delay(50);
        }
      }
    }
  }
}

bool sendAT(String command, const int timeout, boolean debug) {
  String response = "AT+";
  unsigned long t_start = millis();

  esp8266.print("AT+" + command + "\r\n" );                         // Send AT command

  while (!(esp8266.find("AT+")));                                   //flush incoming buffer

  while (millis() - t_start < timeout ) {                           //Read and store the answer until the end or until timemout
    if (esp8266.available()) response += (char)esp8266.read();
    else if (response.indexOf("OK") + response.indexOf("ERROR") >= -1 )  break;
  }

  if (debug) Serial.println(response + "\r\n-------");

  return  !(response.indexOf("OK") >= 0);                           //return 0 if OK, else 1
}


bool sendData(String command, const int timeout, boolean debug) {
  String response = "";
  unsigned long t_start = millis();

  if (debug) Serial.println("  DATA:");

  esp8266.print(command + "\r\n");                                          // Send Data

  while (millis() - t_start < timeout ) {                           //Read and store the answer until the end or until timemout
    if (esp8266.available()) response += (char)esp8266.read();
    else if (response.indexOf("SEND OK") + response.indexOf("FAIL") >= -1 )  break;
  }

  if (debug) Serial.println(response);

  return  !(response.indexOf("SEND OK") >= 0);                      //return 0 if OK, else 1
}

/*
  void sendData(String command, const int timeout, boolean debug) {

  esp8266.print(command); // send the read character to the esp8266

  if (debug) {
    String response = ">";
    String result = "TimeOut : Data";

    long int time = millis();

    while ( (time + timeout) > millis()) {
      if (esp8266.find(">")) break;
    }

    while ( (time + timeout) > millis()) {
      while (esp8266.available()) {
        // The esp has data so display its output to the serial window
        char c = esp8266.read(); // read the next character.
        response += c;
      }
      if (response.indexOf("OK") >= 0) {
        result = response;
        break;
      }
    }
    Serial.println("----------");
    Serial.println(result);
  }
  }
*/
void SendWebPage(int connectionId) {
#define TRAME_SIZE 400

  char cipSend[20] = "";
  char trame[TRAME_SIZE];
  int i_code = 0, i_trame = 0;

  do {
    trame[i_trame] = (char)pgm_read_byte_near(&webpage[i_code]);                  //Ajouter le caractere à la suite

    i_code ++;
    i_trame ++;

    if (i_trame == TRAME_SIZE) {                                                  //Si la trame est complete
      Serial.println(i_trame);
      sprintf(cipSend, "CIPSEND=%d,%d", connectionId, i_trame);                   //Envoyer la trame
      sendAT(cipSend, 500, DEBUG);  //envoyer la commande
      delay(200);
      sendData(trame, 2000, DEBUG); //envoyer le buffer
      delay(300);

      memset( trame, 0, sizeof(char) * TRAME_SIZE);                               //Réinitialiser la trame
      i_trame = 0;
    }


  } while ((char)pgm_read_byte_near(&webpage[i_code]) != '\0');


  sprintf(cipSend, "CIPSEND=%d,%d", connectionId, i_trame);                       //Envoyer la derniere trame
  sendAT(cipSend, 500, DEBUG);  //envoyer la commande
  delay(500);
  sendData(trame, 2000, DEBUG); //envoyer le buffer
  delay(500);
}
