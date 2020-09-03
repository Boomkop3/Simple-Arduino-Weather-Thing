#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>
#include "gpio.h"

#define LOCATION_API_URL "http://ip-api.com/json/"

void decodeLocationJson(String json, DynamicJsonDocument* jsonDoc){\
  Serial.println("Parsing json");
  Serial.flush();
  StaticJsonDocument<265> filter;
  filter // Without this it'd run out of ram
    ["city"] = true;
  auto jsonError = 
    deserializeJson(
      *jsonDoc, 
      json, 
      DeserializationOption::Filter(filter)
    );
  if (jsonError){
    Serial.println("Failed to parse Json");
    Serial.println(jsonError.c_str());
    Serial.flush();
  }
}

String getCurrentCity(){
  Serial.println("getting device location by ip"); // Because the huzzah32 doesn't have gps
  Serial.flush();
  String json = makeWebRequest(LOCATION_API_URL);
  json.trim();
  int bufferSize = 2048;
  DynamicJsonDocument jsonObj(bufferSize);
  decodeLocationJson(json, &jsonObj);
  String city = jsonObj["city"];
  return city;
}
