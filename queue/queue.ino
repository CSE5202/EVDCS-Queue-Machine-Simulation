#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define b1 1
#define b2 2
#define b3 3
#define b4 4
#define b5 5
#define b6 6
#define b7 7
#define etr A0
#define clr A1
#define cnl A2
#define prt A3

int i, total_destination_no;
String station_name, machine_ID;
String destinations [20]= {"dest_1", "dest_2", "dest_3", "dest_4", 
                           "dest_5", "dest_6", "dest_7"};


LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  // put your setup code here, to run once:
  
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
//  pinMode(b8, INPUT);
//  pinMode(b9, INPUT);
  pinMode(etr, INPUT);
  pinMode(clr, INPUT);
  pinMode(cnl, INPUT);
  pinMode(prt, OUTPUT);
  
  machine_ID = "0001";
  station_name = "St_One";
  total_destination_no = 7;
  
  lcd.begin(20, 4);
  Serial.begin(9600);
  
  delay(500);
  Serial.println();
  Serial.println("                   GSM Message To EVDC");
  Serial.println("                   ===================");  
       
  delay(1000);
  lcd.clear(); 
}  

void loop() {
  
    String input = "";
    int z = 0; 
    i = 3;
    lcd.clear(); 
    
    while(digitalRead(etr) == LOW){ 
           
        delay(50);
        if(digitalRead(clr) == HIGH){
          z /= 10;
          input = String(z);
        }   
        if(digitalRead(cnl) == HIGH || (z == 0)){
          z = 0;
          input = "";
        } 
        if(digitalRead(b1) == HIGH){
          z *= 10;
          z = z + 1;
          input = String(z);
        } 
        if(digitalRead(b2) == HIGH){
          z *= 10;
          z = z + 2;
          input = String(z);
        } 
        if(digitalRead(b3) == HIGH){
          z *= 10;
          z = z + 3;
          input = String(z);
        } 
        if(digitalRead(b4) == HIGH){
          z *= 10;
          z = z + 4;
          input = String(z);
        } 
        if(digitalRead(b5) == HIGH){
          z *= 10;
          z = z + 5;
          input = String(z);
        } 
        if(digitalRead(b6) == HIGH){
          z *= 10;
          z = z + 6;
          input = String(z);
        } 
        if(digitalRead(b7) == HIGH){
          z *= 10;
          z = z + 7;
          input = String(z);
        } 
//        if(digitalRead(b8) == HIGH){
//          z *= 10;
//          z = z + 8;
//          input = String(z);
//        } 
//        if(digitalRead(b9) == HIGH){
//          z *= 10;
//          z = z + 9;
//          input = String(z);
//        } 
        
//        lcd.setCursor(15,1);
//        lcd.println("Input"); 
//        lcd.setCursor(15,2);
//        lcd.println("-----");    
//        lcd.setCursor(15,3);
//        lcd.println("     "); 
//        lcd.setCursor(15,3);
//        lcd.println(input);
                
        main_menu();
        i++;
        if(i > total_destination_no)
            i = 3;            
        delay(100);
    } 
    lcd.clear();  
    lcd.setCursor(1,0);    
    lcd.println("   EVDC Service");               
    lcd.setCursor(1,1);
    lcd.print("You have choosen ");
    
    if((z > 0)&&(z <=total_destination_no)){
           
          digitalWrite(prt, HIGH);
                           
          lcd.setCursor(5,2);
          lcd.println(destinations[z-1]);
          lcd.setCursor(8,3);    
          
          for(i=0;i<3;i++){
            
              lcd.setCursor(8,3);
              lcd.println("Printing   ");
              delay(200);  
              lcd.setCursor(8,3);
              lcd.println("Printing.  ");
              delay(200);  
              lcd.setCursor(8,3);
              lcd.println("Printing.. ");
              delay(200);  
              lcd.setCursor(8,3);
              lcd.println("Printing...");
              delay(200); 
           }  
           
          digitalWrite(prt, LOW); 
          
          lcd.setCursor(1,1);
          lcd.println("    Thank you!!     ");
          lcd.setCursor(1,2);
          lcd.println("Have A Safe Journey");
          lcd.setCursor(5,3);
          lcd.print("To ");
          lcd.println(destinations[z-1]);
          lcd.println("       ");
          
          Serial.print("  ");
          Serial.print(machine_ID);
          Serial.print("        ");
          Serial.print(station_name);
          Serial.print("          ");
          Serial.print(destinations[z-1]); 
      }   
      else {
        lcd.setCursor(1,2);
        lcd.println("Invalid Destination");
      }       
    delay(2000);
}

void main_menu(){
  
    lcd.setCursor(0,0);
    lcd.println(" Choose Destination");
    lcd.setCursor(0,1);
    destination_display(i-2);
    lcd.setCursor(0,2);
    destination_display(i-1);
    lcd.setCursor(0,3);         
    destination_display(i);
    delay(300);
}
void destination_display(int x){
  
      lcd.print(" [");
      lcd.print(x);
      lcd.print("] ");      
      lcd.println(destinations[x-1]);
}
