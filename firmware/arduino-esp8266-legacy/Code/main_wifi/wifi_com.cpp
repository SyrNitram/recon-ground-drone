// SPDX-License-Identifier: MIT
// Copyright (c) 2022-2023 Martin RYS - Recon Ground Drone
// Released under the MIT License. See LICENSE and THIRD_PARTY.md.

#include "wifi_com.h"
#include <SoftwareSerial.h>
#define DEBUG false

SoftwareSerial esp8266(2, 3);

String sendData(String command, const int timeout, boolean debug);

void wifi_init() {

  esp8266.begin(9600); // your esp's baud rate might be different
  /*
    sendData("AT+RST\r\n",2000,DEBUG); // reset module
    sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
    sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
    sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
    sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  */
  sendData("AT+RST\r\n", 3000, DEBUG); // reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // configure as wifi client
  sendData("AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"\r\n", 10000, DEBUG); // configure as wifi client
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80
}

int get_cmd() {
  if(esp8266.available()) // check if the esp is sending a message 
  {
 
    if(esp8266.find("+IPD,"))
    {
     delay(100); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     esp8266.find("cmd="); // advance cursor to "pin="
     int cmd = (esp8266.read()-48)*10;
     cmd +=  (esp8266.read()-48);

     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,10,DEBUG); // close connection

     return cmd;

    }
    return 100;
  }
  return 100;
}


/*
  Name: sendData
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  esp8266.print(command); // send the read character to the esp8266

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}
