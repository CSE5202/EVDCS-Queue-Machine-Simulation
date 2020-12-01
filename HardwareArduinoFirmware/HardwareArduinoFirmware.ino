#include <Wire.h>  //Servo Motor Library
#include <Servo.h>  //Servo Motor Library
#include <Keypad.h> // keypad library
#include <ArduinoJson.h> // Arduino Json Library
#include <LiquidCrystal.h> // LCD library 
#include <SoftwareSerial.h> // serial software library for interfacing GSM and ESP Module

#define Erx A5
#define Etx A4
#define Prt A3    //Printer
#define Pon A2    //Printer Led

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
    {'1','2','3','E'},
    {'4','5','6','C'},
    {'7','8','9','X'},
    {'*','0','#','D'}
};

  // strings and variables
byte rowPins[ROWS] = {A0, A1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

  // strings and variables
int counter, total_destination_no = 9;
String machineID = "0001";
String destinations [20]= {"dest_1", "dest_2", "dest_3", 
                           "dest_4", "dest_5", "dest_6", 
                           "dest_7", "dest_8", "dest_9"};

// initialize the library with the numbers of the interface pins
Servo Printer;
SoftwareSerial ESPSerial(Erx, Etx); // RX, TX
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);// connect rs,en,d4,d5,d6,d7 respectevely
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

void setup() {
  
    // put your setup code here, to run once:
    lcd.begin(16,2); // init LCD
    Printer.attach(Prt);  //init Servo 
    Serial.begin(9600); // init serial for GSM
    ESPSerial.begin(9600); // init serial for ESP8266 WIFI MODULE 
    counter = 0;  
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
