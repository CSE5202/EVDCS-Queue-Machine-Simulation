void displayHomescreen(){
  
    String str[4] = {"   ", ".  ", ".. ", "..."};
    lcd.clear();
    lcd.println("  Welcome To EVDC");
    lcd.setCursor(0,1);
    lcd.print( station_name);
    lcd.println(" Station");
    lcd.setCursor(1,2);
    lcd.print(GetDate());
    lcd.print(" ");
    lcd.print(GetTime());
    delay(100);  
    for(int i=0;i<12;i++){
      
        lcd.setCursor(10,3);
        lcd.print("Loading");
        lcd.print(str[i%4]);
        delay(200);  
    }        
    GSMSerial.println();
    GSMSerial.println("                               ***********************");
    GSMSerial.println("                               * GSM MESSAGE To EVDC *");
    GSMSerial.println("                               ***********************");
    GSMSerial.println("");
    GSMSerial.println("  MachineID       Station Name        Destination        Time            Date");
    GSMSerial.println("  =========       ============        ===========        ====            ====");
}

int getInput(){
    
    String input = "";
    char key;
    int z = 0; 
    int i = 3;  
    
    while((key = keypad.getKey()) != 'A'){  
        if((key == '*') || (key == 'B') || (z == 0)){
            z = 0;
            input = "";
        }  
        if(key == 'C'){
            z /= 10;
            input = String(z);
        }      
        if (isDigit(key)) {
            input += (char)key;  
            z = input.toInt();
        }   
        lcd.clear();
        lcd.setCursor(15,1);
        lcd.println("Input"); 
        lcd.setCursor(15,2);
        lcd.println("-----");    
        lcd.setCursor(15,3);
        lcd.println("     "); 
        lcd.setCursor(15,3);
        lcd.println(input);
                
        destination_list(i);
        i++;
        if(i > total_destination_no)
            i = 3;                           
        delay(10);  
    } 
    return z;
}
boolean checkInput(int ch){
  
    lcd.clear();  
    lcd.setCursor(1,0);    
    lcd.println("   EVDC Service");               
    lcd.setCursor(1,1);
    lcd.print("You have choosen ");
    
    if((ch > 0)&&(ch <=total_destination_no))
        return true;
    else if(ch > total_destination_no){
        lcd.setCursor(1,2);
        lcd.println("Invalid Destination");
        return false;
    } 
    lcd.setCursor(1,1);
    lcd.println("Invalid Input!");
    lcd.setCursor(1,2);
    lcd.println("You Must Enter ");
    lcd.setCursor(1,3);
    lcd.println("a Destination First");
    return false;      
}

void printing(int ch){            
                           
    lcd.setCursor(5,2);
    lcd.println(destinations[ch-1]);
    lcd.setCursor(8,3);
     
    printer();
    
    lcd.setCursor(1,1);
    lcd.println("    Thank you!!     ");
    lcd.setCursor(1,2);
    lcd.println("Have A Safe Journey");
    lcd.setCursor(5,3);
    lcd.print("To ");
    lcd.println(destinations[ch-1]);
    lcd.println("       ");

    writeChoice(ch);
    delay(500);    
}

void printer(){
  
    String str[4] = {"   ", ".  ", ".. ", "..."};
    digitalWrite(prt, HIGH);
      
    for(int i=0;i<12;i++){
      
        lcd.setCursor(9,3);
        lcd.print("Printing");
        lcd.print(str[i%4]);
        delay(200);  
    }           
    digitalWrite(prt, LOW); 
}

void writeChoice(int ch){
  
    GSMSerial.print("  ");
    GSMSerial.print(machine_ID);
    GSMSerial.print("            ");
    GSMSerial.print(station_name);
    GSMSerial.print("         ");
    GSMSerial.print(destinations[ch-1]);
    GSMSerial.print("             ");
    GSMSerial.print(GetTime());
    GSMSerial.print("        ");
    GSMSerial.println(GetDate());  
}

void destination_list(int i){
  
    lcd.setCursor(0,0);
    lcd.println(" Choose Destination");
    lcd.setCursor(0,1);
    destination_display(i-2);
    lcd.setCursor(0,2);
    destination_display(i-1);
    lcd.setCursor(0,3);         
    destination_display(i);
    delay(200);
}

String GetTime(){
    DateTime now = rtc.now();
    char current[50];
    sprintf(current, "%02d:%02d:%02d",now.hour(), now.minute(), now.second());
    return current;
}

String GetDate(){
    DateTime now = rtc.now();
    char current[50];
    sprintf(current, "%04d-%02d-%02d", now.year(), now.month(), now.day());
    return current;
}

void destination_display(int x){
  
    lcd.print(" [");
    lcd.print(x);
    lcd.print("] ");      
    lcd.println(destinations[x-1]);
}

void success_status(boolean success){
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("Status");
    lcd.setCursor(6,1);
    lcd.print("======");
    lcd.setCursor(1,2);  
    if(success)
        lcd.print("Data Sent to Server");
    else
        lcd.print("Didnt Send Data");
}
