#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WifiClient.h>
#include <ArduinoJson.h>
#include "base64.h"

#ifndef SSID
#define SSID "khalid"
#define PASSKEY  "0987654321"
#endif

#define ServerIP "10.240.73.14"
#define Port 80

const char username[255] = "shems1";
const char password[255] = "Jemal@12";
String message;
bool messageReady;

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSKEY);
  
    while (WiFi.status() != WL_CONNECTED) 
        delay(500);
    messageReady = false;
    message = "";
}

void loop() {
      // Monitor serial communication
      while(Serial.available()) {
        message = Serial.readString();
        messageReady = true;
      }
      // Only process message if there's one
      if(messageReady)     
           httpSend(message);    
      messageReady = false;
}

void httpSend(String msg) {
    // Use WiFiClient class to create TCP connections    
    WiFiClient client;
    HTTPClient httpClient;
    if(WiFi.status() == WL_CONNECTED){       
        if (!client.connect(ServerIP, Port)) {
            delay(3000);
            return;
        }
        // This will send a string to the server
        if (client.connected()) {    
            // configure traged server and url
//            httpClient.begin(client, "http://" ServerIP "/api/Machine-data");
            httpClient.begin(client, "http://" ServerIP "/post");
            httpClient.addHeader("Content-Type", "application/json; charset=UTF-8");
            httpClient.setAuthorization(username, password);
                                
            int httpCode = httpClient.POST(msg);
            // httpCode will be negative on error
            if (httpCode > 0) // HTTP header has been send and Server response header has been handled                     
                  if (httpCode == HTTP_CODE_OK) 
                      const String& payload = httpClient.getString();            
        }
        delay(2000);
    }
        httpClient.end();
        client.stop();
}
