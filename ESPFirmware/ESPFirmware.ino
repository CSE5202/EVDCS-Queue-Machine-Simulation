#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WifiClient.h>
#include <ArduinoJson.h>
#include "base64.h"

#define SSID "ESP8266"
#define PASSKEY  "0987654321"
#define ServerIP "10.240.73.14"
#define Port 8000

const char username[10] = "shems1";
const char password[10] = "Jemal@12";

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSKEY);
  
    while (WiFi.status() != WL_CONNECTED)
        delay(500);  
}

void loop() {
      DynamicJsonDocument jDoc(256);  
      String message = "";      
      while(!Serial.available());// Only process message if there's one
      message = Serial.readString(); 
      if(message.length()){       
          deserializeJson(jDoc, message);
          if(!jDoc.isNull()){
              message = ""; 
              serializeJson(jDoc,message);
              httpSend(message);
          } 
      } 
}

void httpSend(String msg) {
  
    // Use WiFiClient class to create TCP connections    
    WiFiClient client;
    HTTPClient httpClient;
    if(WiFi.status() == WL_CONNECTED){    
         
        if (!client.connect(ServerIP, Port)) {           
            delay(2000);
            return;
        }
        
        // This will send a string to the server
        if (client.connected()) {    
            // configure traged server and url
            httpClient.begin(client, "http://" ServerIP "/api/Machine-data");
            httpClient.addHeader("Content-Type", "application/json; charset=UTF-8");
            httpClient.setAuthorization(username, password);
                                
            int httpCode = httpClient.POST(msg);
            // httpCode will be negative on error
            if (httpCode > 0) // HTTP header has been send and Server response header has been handled                     
                  if (httpCode == HTTP_CODE_OK) 
                      const String& payload = httpClient.getString(); 
        }         
    }           
        httpClient.end();
        client.stop();
}

//            httpClient.begin(client, "http://" ServerIP "/post");
