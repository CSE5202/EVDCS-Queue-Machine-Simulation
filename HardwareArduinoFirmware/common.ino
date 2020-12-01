void displayHomescreen(){
  
    String str[4] = {"   ", ".  ", ".. ", "..."};
    lcd.print("Initializing"); 
    digitalWrite(Pon, HIGH);       
    delay(500);    
    lcd.setCursor(0,1);
    displayCurrentTime();
    delay(1000);
    digitalWrite(Pon, LOW); 
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.println("EVDCS");
    lcd.setCursor(0,1);
    lcd.println("Welcome To EVDC ");
    delay(1000); 
    for(int i=0;i<12;i++){
      
        lcd.setCursor(0,1);
        lcd.print("      Loading");
        lcd.print(str[i%4]);
        delay(300);  
    }        
}

int getInput(){
    
    String input = "";
    char key;
    int z = 0, i = 3;  
    
    while((key = keypad.getKey()) != 'E'){  
        if((key == 'X') || (z == 0)){
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
        lcd.setCursor(0,0);
        lcd.println(" Choose Destination");
        lcd.setCursor(0,1);
        lcd.print("Input: ");
        lcd.println(input);
        lcd.clear();                     
        delay(10);  
    } 
    return z;
}
boolean checkInput(int ch){
  
    lcd.clear();                 
    lcd.setCursor(0,0);
    lcd.print("You have choosen");
    
    if((ch > 0)&&(ch <=total_destination_no))
        return true;
    else if(ch > total_destination_no){
        lcd.setCursor(0,1);
        lcd.println("Invalid Choice  ");
        delay(500);
        return false;
    } 
    lcd.setCursor(0,1);
    lcd.println(" Invalid Input!!");
    delay(500);
    lcd.setCursor(0,0);
    lcd.println("You Must Enter a");
    lcd.setCursor(0,1);
    lcd.println("Destination Frst");
    delay(500);
    return false;      
}

void printing(int ch){            
    String msgToVirtual = "";                       
    lcd.setCursor(0,1);
    lcd.println(destinations[ch-1]);
    delay(500);
     
    printer();    
    lcd.setCursor(0,0);
    lcd.println("Thank you!! Have");
    lcd.setCursor(0,1);
    lcd.println(" A Safe Journey ");  
    msgToVirtual = "  " + machineID + "            " + destinations[ch-1];
    Serial.print(msgToVirtual);
    delay(500);    
}

void printer(){
  
    String str[4] = {"   ", ".  ", ".. ", "..."};
    lcd.clear();  
    lcd.setCursor(0,0);
    lcd.println("Queue No Printer");     
    delay(300);     
    
    for (int pos = -60; pos <= 60; pos += 20) { 
        Printer.write(abs(pos));
        lcd.setCursor(0,1);
        lcd.print("     Printing");
        lcd.print(str[abs(pos)/20]);
        digitalWrite(Pon, HIGH); 
        delay(300);
        digitalWrite(Pon, LOW);     
        delay(300);               
    }        
}

void destination_list(int i){
        
    lcd.setCursor(0,0);
    lcd.println(" Choose Destination");
    lcd.setCursor(0,0);
    destination_display(i-1);
    lcd.setCursor(0,1);
    destination_display(i-2);
    delay(200);
}

void displayCurrentTime(){
    String currentTime = Serial.readString();
    if(currentTime.length()>0){
        char Date[10], Time[9];
        for(int i = 2; i < 10; i++)
            Date[i] = currentTime[i];
        for(int i = 0; i < 8; i++)
            Time[i] = currentTime[i+11];
        return String(Date) + "  " + String(Time);
    }
    else
        lcd.print("0000-00-00 00:00:00");
}

void destination_display(int x){
  
    lcd.print(" [");
    lcd.print(x);
    lcd.print("] ");      
    lcd.println(destinations[x-1]);
}

void success_status(){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Status");
    lcd.setCursor(0,1); 
    lcd.print(" Sent to Server ");
}
