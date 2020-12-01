#include <Wire.h>
#include <RTClib.h> //Time Module
#include <Keypad.h> // keypad library 
#include <ArduinoJson.h> // Arduino Json Library
#include <LiquidCrystal.h> // LCD library 
#include <SoftwareSerial.h> // serial software library for interfacing GSM and ESP Module

#define Erx A3
#define Etx A2
#define prt A1    //Printer
#define Gtx A0
#define Grx 15

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
    {'7','8','9','A'},
    {'4','5','6','B'},
    {'1','2','3','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

  // strings and variables
int counter, total_destination_no = 9;
String machineID = "0001";
String destinations [20]= {"dest_1", "dest_2", "dest_3", 
                           "dest_4", "dest_5", "dest_6", 
                           "dest_7", "dest_8", "dest_9"};

// initialize the library with the numbers of the interface pins
RTC_DS1307 rtc;
SoftwareSerial ESPSerial(Erx, Etx); // RX, TX
SoftwareSerial GSMSerial(Grx, Gtx);// RX, TX 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);// connect rs,en,d4,d5,d6,d7 respectevely
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

void setup() {
  
    // put your setup code here, to run once: 
    pinMode(prt, OUTPUT);    
        
    lcd.begin(20,4); // init LCD  
    GSMSerial.begin(9600); // init serial for GSM
    ESPSerial.begin(9600); // init serial for ESP8266 WIFI MODULE
    digitalWrite(prt, LOW); 
    counter = 0;
       
    while(!rtc.begin());
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   
    displayHomescreen(); 
    lcd.clear(); 
}  

void loop() {
  
    int ch = getInput();
    if(checkInput(ch)){
        printing(ch);
        sendToESP(ch);
    }
    delay(1000);   
    lcd.clear(); 
}
