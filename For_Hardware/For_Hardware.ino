#include <Wire.h>
#include <RTClib.h> //Time Module
#include <SoftwareSerial.h> // serial software library for interfacing COMPIM Module

#define Crx 9
#define Ctx 10

RTC_DS1307 rtc;
SoftwareSerial ComSerial(Crx, Ctx); // RX, TX

void setup() {
    // put your setup code here, to run once:         
    Serial.begin(9600); // init serial for VIRTUAL TERMINAL
    ComSerial.begin(9600); // init serial for COMPIM Module    
    while(!rtc.begin());
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   

    displayHomescreen();         
    delay(500);
}  

void loop() {
    while(ComSerial.available()){
          Serial.println(Serial.readString());  
    }
    DateTime now = rtc.now();
    char currentTime[50], currentDate[50];
    sprintf(currentTime, "%04d-%02d-%02dT%02d:%02d:%02dZ", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    ComSerial.println(currentTime);
    Serial.println(currentTime);
}

void displayHomescreen(){ 
       
    Serial.println();
    Serial.println("                               ***********************");
    Serial.println("                               * GSM MESSAGE To EVDC *");
    Serial.println("                               ***********************");
    Serial.println("");
    Serial.println("  MachineID       Station Name        Destination        Time            Date");
    Serial.println("  =========       ============        ===========        ====            ====");
}

  
