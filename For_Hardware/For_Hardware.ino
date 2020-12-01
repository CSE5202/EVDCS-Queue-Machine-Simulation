#include <Wire.h>
#include <RTClib.h> //Time Module
#include <SoftwareSerial.h> // serial software library for interfacing COMPIM Module

RTC_DS1307 rtc;
SoftwareSerial VSerial(2,3);
void setup() {
    // put your setup code here, to run once:         
    Serial.begin(9600); // init serial for COMPIM Module
    VSerial.begin(9600); // init serial for COMPIM Module
    while(!rtc.begin());
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
    displayHomescreen();         
    delay(500);
}  

void loop() {
    DateTime now = rtc.now();
    char currentTime[50];
    sprintf(currentTime, "%04d-%02d-%02dT%02d:%02d:%02dZ", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    Serial.println(currentTime);
    if(Serial.available())
        VSerial.println(Serial.readString()); 
    delay(1000);
}

void displayHomescreen(){ 
       
    VSerial.println();
    VSerial.println("                     ***********************");
    VSerial.println("                     * GSM MESSAGE To EVDC *");
    VSerial.println("                     ***********************");
    VSerial.println("");
    VSerial.println("  MachineID       Destination        Time            Date");
    VSerial.println("  =========       ===========        ====            ====");
}  
