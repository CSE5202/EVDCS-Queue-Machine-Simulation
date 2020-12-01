//void initGSM();
//void initGPRS();
//void GSMsetup();
//void main_menu();
//void WIFIsetup();
//void lcd_status();
//void sendToESP();
//Sring GetDate();
//Sring GetTime();
//void sendToServerWifi();
//void toServer(String str);
//void sendToServer(String str);
//void destination_display(int x);
//void connectGSM (String cmd, char *res);


//void initGSM(){
//    connectGSM("AT","OK");
//    connectGSM("ATE1","OK");
//    connectGSM("AT+CPIN?","READY");
//}
//
//void initGPRS(){
//    connectGSM("AT+CIPSHUT","OK");
//    connectGSM("AT+CGATT=1","OK");
//    connectGSM("AT+CSTT=\"etc.com\",\"\",\"\"","OK");
//    connectGSM("AT+CIICR","OK");
//    delay(1000);
//    GSMSerial.println("AT+CIFSR");
//    delay(1000);
//}
//
//void connectGSM (String cmd, char *res){
//    while(1){
//      GSMSerial.println(cmd);
//      delay(500);
//      while(GSMSerial.available()>0){
//        if(GSMSerial.find(res)){
//          delay(1000);
//          return;
//        }
//      }
//      delay(1000);
//    }
//}
//
//void GSMsetup() {  
//        
//    lcd.clear();  
//    lcd.print("Initializing GSM");
//    initGSM(); // init GSM module
//    lcd.clear();
//    lcd.print("Initializing GPRS");
//    initGPRS(); // init GPRS in GSM Module
//    lcd.clear();
//    lcd.print("System Ready");
//    delay(2000);
//}
//
//void sendToServerGSM(String msg){
//    lcd.clear();
//    lcd.noCursor();
//    lcd.noBlink();
//    lcd.print("Status");
//    lcd.setCursor(0,1);
//    lcd.print("Sending Data To Server");
//    
//    toServer(msg);
//    GSMSerial.print("url: ");
//    GSMSerial.print(url);
//    delay(500);
//    lcd.clear();
//    lcd_status();
//    msg="";
//}
//
//void toServer(String msg){
//    url = "GET /input/" + msg;
//    url += " HTTP/1.0\r\n\r\n";
//    svr = StartTCPIP + "," + serverIP + "," + port;
//    connectGSM(svr,"CONNECT");
//    delay(500);
//    GSMSerial.println(SendCmd + url.length());
//    delay(500);
//}
