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
#define IR_PIN 14 //GPIO D5

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
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(pwr, pwr_len, ir_frequency);
#else
            irsend.sendNEC(pwr_NEC);
#endif
        }
        else if(cmd == '2' || cmd == 2)
        {
            Serial.println("Power Off");
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(pwr, pwr_len, ir_frequency);
            delay(500);
            irsend.sendRaw(pwr, pwr_len, ir_frequency);
#else
            irsend.sendNEC(pwr_NEC);
            delay(500);
            irsend.sendNEC(pwr_NEC);
#endif
        }
        else if(cmd == '3' || cmd == 3)
        {
            Serial.println("Set Source to HDMI");
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(src_hdmi, src_hdmi_len, ir_frequency);
#else
            irsend.sendNEC(src_hdmi_NEC);
#endif
        }
        else if(cmd == '4' || cmd == 4)
        {
            Serial.println("Set Source to VGA");
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(src_vga, src_vga_len, ir_frequency);
#else
            irsend.sendNEC(src_vga_NEC);
#endif
        }
        else if(cmd == '5' || cmd == 5)
        {
            Serial.println("Volume Down");
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(volume_down, volume_down_len, ir_frequency);
#else
            irsend.sendEpson(volume_down_epson);
#endif
        }
        else if(cmd == '6' || cmd == 6)
        {
            Serial.println("Volume Up");
#ifdef USE_RAW_IR_DATA
            irsend.sendRaw(volume_up, volume_up_len, ir_frequency);
#else
            irsend.sendEpson(volume_up_epson);
#endif
        }
        else if(cmd == '7' || cmd == 7)
        {
            Serial.println("Set Volume 0");
            for(uint8_t i=0; i<10;i++ )
            {
#ifdef USE_RAW_IR_DATA
                irsend.sendRaw(volume_down, volume_down_len, ir_frequency);
#else
                irsend.sendEpson(volume_down_epson);
#endif
                delay(100);
            }
        }
        else{
            Serial.println("unknown");
        }
    }
}