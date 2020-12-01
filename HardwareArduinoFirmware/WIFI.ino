void sendToESP(int ch){
      DynamicJsonDocument jDoc(128);
      boolean assign = false;
      
      if(counter == 12){
          assign = true;
          counter = 0;
      }
      else
          counter++;
      
      jDoc["machineID"] = machineID;
      jDoc["destination"] = destinations[ch-1];
      jDoc["reg_date"] = Serial.readString();
      jDoc["assign"] = assign;    
      serializeJson(jDoc,ESPSerial);       
      jDoc.clear();
      delay(500);
      success_status(); 
      delay(500);
}
