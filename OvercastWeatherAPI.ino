#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>
#include "gpio.h"

#define WEATHER_API "http://weather.boomkop.com/?location="

void decodeWeatherJson(String json, DynamicJsonDocument* jsonDoc){
  Serial.println("Parsing json");
  Serial.flush();
  StaticJsonDocument<265> filter;
  filter // Without this it'd run out of ram
    ["list"]
    [0]
    ["clouds"]
    ["all"] = true;
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

String getWeatherUrlFor(String city){
  String url = "";
  return url + WEATHER_API + city;
}

int *getCloudsInfo(String city, int *h3clouds) {
  Serial.println("getting weather info");
  Serial.flush();
  String url = getWeatherUrlFor(city);
  String json = makeWebRequest(url);
  json.trim();
  int bufferSize = 8192; // yup, a lot of json coming in
  DynamicJsonDocument jsonObj(bufferSize);
  decodeWeatherJson(json, &jsonObj);
  int length = jsonObj["list"].size();
  for (int i = 0; i < length; i++){
    h3clouds[i] = jsonObj["list"][i]["clouds"]["all"];
  }
  h3clouds[length] = -1;
}
