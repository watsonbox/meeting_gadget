#include "Secrets.h" // Not under source control
#include <WiFi.h>
#include "HTTPClient.h"
#include <StreamString.h>
#include <Wire.h>
#include "SSD1306.h" 
 
SSD1306  display(0x3c, 26, 27);
 
const char* ssid = SECRET_WIFI_SSID;
const char* password = SECRET_WIFI_PASSWORD;
const char* ws_url = SECRET_WS_URL;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Starting loop");
  
  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.println("Making Google Script request");
    String response = getGoogleScriptResponse();
    
    Serial.println(response);
    displayText(response);
  }

  delay(5000);
}

void displayText(String text) {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, text);
  display.display();
}

String getGoogleScriptResponse() {
  HTTPClient http;
  String payload;
  const char * headerKeys[] = {"Location"} ;
  const size_t numberOfHeaders = 1;
 
  http.begin(ws_url);
    
  http.collectHeaders(headerKeys, numberOfHeaders);
    
  int httpCode = http.GET();
 
  if (httpCode > 0) {
    if (httpCode == 302) {
      http.end();
      http.begin(http.header("Location"));
        
      httpCode = http.GET();
    }

    payload = http.getString();
  }
  else {
    Serial.println("Error on HTTP request");
  }
 
  http.end();

  return payload;
}

