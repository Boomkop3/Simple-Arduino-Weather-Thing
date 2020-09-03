#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>

void initGPIO(){
  int pins[] = gpioPins;
  for(int i = 0; true; i++) { // Set pinmodes
    int pin = pins[i];
    if (pin == -1){
      ledCount = i;
      break;
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // turn all led's off
  }
}

void testGPIO(){
  int pins[] = gpioPins;
  for(int i = 0; true; i++) { // Test all pins
    int pin = pins[i];
    if (pin == -1){
      break;
    }
    digitalWrite(pin, LOW);
    delay(50);
  }
  for(int i = 0; true; i++) {
    int pin = pins[i];
    if (pin == -1){
      break;
    }
    digitalWrite(pin, HIGH);
    delay(50);
  }
}
