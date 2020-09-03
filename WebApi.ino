#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <string.h>
#include <stdio.h>

#include <ArduinoJson.h>
#include "gpio.h"

String makeWebRequest(String address) {
  Serial.print("getting http text from: ");
  Serial.println(address);
  Serial.flush();
  HTTPClient client;
  client.begin(address);
  int responseCode = client.GET();
  if (responseCode > 0) {
    if (responseCode == 200){
      Serial.println("Got http data");
      Serial.flush();
      String payload = client.getString(); // f 't werkgeheugen
      return payload;
    }
    else {
      Serial.print("HTTP Error: '");
      Serial.print(responseCode);
      Serial.println("'");
      Serial.flush();
    }
  }
  else {
    Serial.print("HTTP Failed: '");
    Serial.print(responseCode);
    Serial.println("'");
    Serial.flush();
  }
  client.end();
}
