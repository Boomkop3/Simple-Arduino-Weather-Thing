#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>

extern WiFiMulti wifi;

void connectToWifi(){
  Serial.println("connecting to wifi...");
  Serial.flush();
  wifi.addAP("Grasmaaier", "staatdaar");
  if((wifi.run() == WL_CONNECTED)){
    delay(100);
    Serial.println("connecting to wifi...");
    Serial.flush();
  }
  Serial.println("connected to wifi...");
  Serial.flush();
}
