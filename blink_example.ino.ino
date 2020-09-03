#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>
#include "gpio.h"

WiFiMulti wifi;
int h3clouds[128];
int ledCount;
long lastMillisPoll;
String city;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); // Dit is uit de example code
  initGPIO();
  testGPIO();
  initSerialConnection();
  for(int i = 0; i < 4; i++) {// Wait for wifi module
      Serial.printf("waiting for wifi module... %d\n", (4-i));
      Serial.flush();
      delay(1000);
  }
  connectToWifi(); // Connect to the guest wifi
  pollWeatherInfo();
  lastMillisPoll = millis();
}

void loop() {
  // Display overhead as a timelapse
  for (int i = 0; true; i++){ // print cloud cover to console for debugging
    int cloud = h3clouds[i];
    if (cloud == -1){
      break;
    }
    double ratio = cloud/100.0;
    int enabledLeds = (int)(ratio * ledCount);
    int pins[] = gpioPins;
    for (int i = 0; i < (ledCount + enabledLeds); i++) {
      if (i < ledCount){
        int led = pins[i];
        digitalWrite(led, LOW); 
      }
      if (i >= enabledLeds){
        int led = pins[i - enabledLeds];
        digitalWrite(led, HIGH);
      }
      delay(100);
    }
  }
  // update weather info every 3 hours
  long x3hours = 1000*60*60*3;
  if ((millis() - lastMillisPoll) > x3hours){
    pollWeatherInfo();
  }
}

void pollWeatherInfo(){
  Serial.println("Polling weather info");
  city = getCurrentCity();
  Serial.println("Using city: " + city);
  getCloudsInfo(city, (int*)&h3clouds); // Get weather info
  for (int i = 0; true; i++){ // print cloud cover to console for debugging
    int cloud = h3clouds[i];
    if (cloud == -1){
      break;
    }
    Serial.print(cloud);
    Serial.print(",");
  }
}

void initSerialConnection(){
  Serial.begin(115200); // connect to serial monitor
  for(int i = 0; i < 100; i++) { // Clear the screen (sorta)
    Serial.println();
  }
}
