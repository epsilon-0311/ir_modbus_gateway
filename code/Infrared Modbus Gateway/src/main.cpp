#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ModbusIP_ESP8266.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include "ir_commands.h"

#define WIFI_SSID "SSID"
#define WIFI_PW "PASSWORD"

#define BAUDRATE 115200

//Modbus Registers Offsets
#define IR_REG 100
//Used Pins
#define IR_PIN 4 //GPIO D2

// #define USE_SERIAL

//ModbusIP object
ModbusIP mb;

IRsend irsend(IR_PIN);  // Set the GPIO to be used to sending the message.


uint16_t last_cmd = 0;

void setup() {
    // Setup Serial 
    Serial.begin(BAUDRATE);
    WiFi.begin(WIFI_SSID, WIFI_PW);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    // Init ModBus Server
    mb.server();
    // Set coil for Infrared Commands
    mb.addHreg(IR_REG);
    // init coil
    mb.Hreg(IR_REG, 0);

    // Init Infrared
    irsend.begin();
}

void loop() {
    //Call once inside loop() - all magic here

#ifdef USE_SERIAL
    if (Serial.available() > 0) {
      uint8_t cmd = Serial.read();
#else
    mb.task();
    uint16_t cmd = mb.Hreg(IR_REG);
    if(last_cmd != cmd)
    {
      last_cmd = cmd;
#endif
      Serial.printf("Send CMD : %c - ", cmd);
      if(cmd == '1' || cmd == 1)
      {
          Serial.println("Power On");
          irsend.sendRaw(pwr_on, pwr_on_len, ir_frequency);
      }
      else if(cmd == '2' || cmd == 2)
      {
          Serial.println("Power Off");
          irsend.sendRaw(pwr_off, pwr_off_len, ir_frequency);
      }
      else if(cmd == '3' || cmd == 3)
      {
          Serial.println("Next Source");
          irsend.sendRaw(next_src, next_src_len, ir_frequency);
      }
      else if(cmd == '4' || cmd == 4)
      {
          Serial.println("Priveous Source");
          irsend.sendRaw(priv_src, priv_src_len, ir_frequency);
      }
      else{
          Serial.println("unknown");
      }
    }
}