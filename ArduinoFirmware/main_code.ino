//#include <Wire.h>
//#include <RTClib.h> //Time Module
//#include <Keypad.h> // keypad library for interfacing keypad
//#include <LiquidCrystal.h> // LCD library for interfacing LCD
//#include <SoftwareSerial.h> // serial software library for interfacing gsm Module
//
//
////SoftwareSerial WIFISerial(6, 7); // RX, TX
//
//#define Grx 15
//#define Gtx A0
//#define prt A2
//
//const byte ROWS = 4; 
//const byte COLS = 4; 
//char hexaKeys[ROWS][COLS] = {
//    {'7','8','9','A'},
//    {'4','5','6','B'},
//    {'1','2','3','C'},
//    {'*','0','#','D'}
//};
//
//byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad
//
//  // strings and variables
//int i, total_destination_no = 9;
//String msg = "", url = "", svr = "";
//String station_name = "St_One", machine_ID = "0001";
//String destinations [20]= {"dest_1", "dest_2", "dest_3", 
//                           "dest_4", "dest_5", "dest_6", 
//                           "dest_7", "dest_8", "dest_9"};
//
//  //Server informations
//int port = 80; //  server port
//String serverIP = "127.0.0.1"; // server ip or url
//String SendCmd = "AT+CIPSEND="; // sending number of byte command
//String StartTCPIP = "AT+CIPSTART=\"TCP\""; // TCPIP start command
//
//// initialize the library with the numbers of the interface pins
//RTC_DS1307 rtc;
//SoftwareSerial GSMSerial(Grx, Gtx);// RX, TX // connect gsm Tx at D2 and Rx at D3
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);// connect rs,en,d4,d5,d6,d7 respectevely
//Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );
//
//void setup() {
//    // put your setup code here, to run once:  
//    pinMode(prt, OUTPUT);
//        
//    lcd.begin(20,4); // init LCD  
//    GSMSerial.begin(9600); // init serial1 for GSM
//    
//    while(!rtc.begin());
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//        
//    lcd.clear();
//    lcd.println("  Welcome To EVDC");
//    lcd.setCursor(0,1);
//    lcd.print( station_name);
//    lcd.println(" Station");
//    lcd.setCursor(1,2);
//    LCDdisplayTime(lcd);
//    delay(100);  
//    //GSMsetup(); 
//    for(i=0;i<3;i++){
//      
//        lcd.setCursor(9,3);
//        lcd.println("Loading   ");
//        delay(300);  
//        lcd.setCursor(9,3);
//        lcd.println("Loading.  ");
//        delay(300);  
//        lcd.setCursor(9,3);
//        lcd.println("Loading.. ");
//        delay(300);  
//        lcd.setCursor(9,3);
//        lcd.println("Loading...");
//        delay(300); 
//    }  
//        
//    GSMSerial.println();
//    GSMSerial.println("                   GSM Message To EVDC");
//    GSMSerial.println("                   ===================");
//    GSMSerial.println("  MachineID   Station Name    Destination    Time      Date");
//    GSMSerial.println("  =========   ============    ===========    ====      ====");    
//         
//    delay(500);
//    lcd.clear(); 
//}  
//
//void loop() {
//  
//    String input = "";
//    char key;
//    int z = 0; 
//    i = 3;
//    lcd.clear();                 
//    delay(10); 
//
//    while((key = keypad.getKey()) != 'A'){ 
//        if((key == '*') || (key == 'B') || (z == 0)){
//            z = 0;
//            input = "";
//        }  
//        if(key == 'C'){
//            z /= 10;
//            input = String(z);
//        }      
//        if (isDigit(key)) {
//            input += (char)key;  
//            z = input.toInt();
//        }   
//        
//        lcd.setCursor(15,1);
//        lcd.println("Input"); 
//        lcd.setCursor(15,2);
//        lcd.println("-----");    
//        lcd.setCursor(15,3);
//        lcd.println("     "); 
//        lcd.setCursor(15,3);
//        lcd.println(input);
//                
//        main_menu();
//        i++;
//        if(i > total_destination_no)
//            i = 3;  
//    }  
//    lcd.clear();  
//    lcd.setCursor(1,0);    
//    lcd.println("   EVDC Service");               
//    lcd.setCursor(1,1);
//    lcd.print("You have choosen ");
//    
//    if((z > 0)&&(z <=total_destination_no)){
//           
//          digitalWrite(prt, HIGH);
//                           
//          lcd.setCursor(5,2);
//          lcd.println(destinations[z-1]);
//          lcd.setCursor(8,3);    
//          
//          for(i=0;i<3;i++){
//            
//              lcd.setCursor(8,3);
//              lcd.println("Printing   ");
//              delay(200);  
//              lcd.setCursor(8,3);
//              lcd.println("Printing.  ");
//              delay(200);  
//              lcd.setCursor(8,3);
//              lcd.println("Printing.. ");
//              delay(200);  
//              lcd.setCursor(8,3);
//              lcd.println("Printing...");
//              delay(200); 
//           }  
//           
//          digitalWrite(prt, LOW); 
//          
//          lcd.setCursor(1,1);
//          lcd.println("    Thank you!!     ");
//          lcd.setCursor(1,2);
//          lcd.println("Have A Safe Journey");
//          lcd.setCursor(5,3);
//          lcd.print("To ");
//          lcd.println(destinations[z-1]);
//          lcd.println("       ");
//          
//          GSMSerial.print("  ");
//          GSMSerial.print(machine_ID);
//          GSMSerial.print("        ");
//          GSMSerial.print(station_name);
//          GSMSerial.print("          ");
//          GSMSerial.print(destinations[z-1]);
//          GSMSerial.print("         ");
//          GSMdisplayTime(GSMSerial);
//          
//          DateTime now = rtc.now();
//          msg = "{ machine_ID : " + machine_ID + ", station_name : " + station_name + ", destinations : " 
//                + destinations[z-1] + ", time : " + "{ hour : " + (now.hour(), DEC) + ", minute : " 
//                + (now.minute(), DEC) + ", second : " + (now.second(), DEC) + ", day : " + (now.day(), DEC) 
//                + ", month : " + (now.month(), DEC) + ", year : + " + (now.year(), DEC) + "}" + "}";
//          sendToServerGSM(msg);
//      }   
//      else {
//        lcd.setCursor(1,2);
//        lcd.println("Invalid Destination");
//      }       
//    delay(2000);
//}
