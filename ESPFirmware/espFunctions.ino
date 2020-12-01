//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WifiClient.h>
//#include <ArduinoJson.h>
//#include "base64.h"
//
//#ifndef SSID
//#define SSID "khalid"
//#define PASSKEY  "0987654321"
//#endif
//
//#define ServerIP "10.240.73.14"
//#define Port 80
//
////#define ServerIP "10.240.73.25"
////#define Port 8000
////        String basicAuth = "Basic " + base64::encode(username + ":" + password);
////        httpClient.addHeader("authorization", basicAuth);
////String username = "shems1";
////String password = "Jemal@12";
//
//const char username[255] = "shems1";
//const char password[255] = "Jemal@12";
//String message;
//bool messageReady;
// 
//void setup() {
//    Serial.begin(9600);
//  
//    // We start by connecting to a WiFi network
//    Serial.println();
//    Serial.print("Connecting to ");
//    Serial.println(SSID);
//  
//    WiFi.mode(WIFI_STA);
//    WiFi.begin(SSID, PASSKEY);
//  
//    while (WiFi.status() != WL_CONNECTED) {
//      delay(500);
//      Serial.print(".");
//    }
//  
//    Serial.println("");
//    Serial.println("WiFi connected");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());
//    
//    messageReady = false;
//    message = "";
//}
//
//void loop() {
//      // Monitor serial communication
//      while(Serial.available()) {
//        message = Serial.readString();
//        messageReady = true;
//      }
//      // Only process message if there's one
//      if(messageReady)     
//           httpSend(message);    
//      messageReady = false;
//}
//
//void httpSend(String msg) {
//    // Use WiFiClient class to create TCP connections    
//    WiFiClient client;
//    HTTPClient httpClient;
//    if(WiFi.status() == WL_CONNECTED){
//        Serial.print("connecting to ");
//        Serial.print(ServerIP);
//        Serial.print(':');
//        Serial.println(Port);  
//       
//        if (!client.connect(ServerIP, Port)) {
//            Serial.println("connection failed");
//            delay(3000);
//            return;
//        }
//        // This will send a string to the server
//        Serial.println("sending data to server");
//        if (client.connected()) {    
//            // configure traged server and url
//            httpClient.begin(client, "http://" ServerIP "/post");
//            httpClient.addHeader("Content-Type", "application/json; charset=UTF-8");
//            httpClient.setAuthorization(username, password);
//                                
//            int httpCode = httpClient.POST(msg);
//            // httpCode will be negative on error
//            if (httpCode > 0){ // HTTP header has been send and Server response header has been handled      
//                  
//                  Serial.println("[HTTP] POST success");// file found at server
//                  
//                  if (httpCode == HTTP_CODE_OK) 
//                      Serial.println("Successfull. Server responded with HTTP status 200.");
//                  
//                  else {
//                      Serial.printf("Got HTTP status: %d", httpCode);
//                      String payload = httpClient.getString();
//                      Serial.println(payload);
//                  }
//            }
//            else 
//                Serial.println("[HTTP] POST failed");            
//        }  
//        delay(2000);
//    }
//        // Close the connection
//        Serial.println();
//        Serial.println("closing connection");
//        httpClient.end();
//        client.stop();
//}
