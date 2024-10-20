#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

bool tt = true;
bool look = true;

void handle_OnConnect() {
  look = true;
  server.send(200, "text/html", SendHTML(look)); 
}

void handle_unlock() {
  look = false;
  server.send(200, "text/html", SendHTML(look)); 
}



void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
//animation: blink-animation 1s infinite;} @keyframes blink-animation { 0% { background-color: red; }50% { background-color: yellow; }100% { background-color: red; }}
String SendHTML(bool l){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Security System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 0px;background: hsla(205, 46%, 10%, 1);} h1 {color: white;margin: 20px auto 20px;background-color: #e21b6e;padding: 20px;border-radius: 10px;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +=".war{color: white;margin: 20px auto 20px;background-color: #e21b6e;padding: 20px;border-radius: 10px;transition: background-color 1s, transform 0.3s; animation: colorChange 0.5s infinite alternate;}\n";
  ptr +="@keyframes colorChange {0% {background-color: #ff0000;}100% {background-color: #ff000000;}}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Security System</h1>\n";

  if(l){
    ptr +="\n";
    ptr +="<h3 style=\"color: green;\">Security System Status : Locked</h3>\n";
    if(!tt){
      ptr +="<h1 class=\"war\">WARNING!</h1>\n";
    }
    ptr +="<hr/>\n";
    ptr +="<p id=\"tt\" style=\"font-size: 18px;text-align: center;margin: 30px;color: #666;\">You want to Unlock Security System, Enter password</p>\n";
    ptr +="<input type=\"text\" id=\"username\" placeholder=\"Enter Username\" required style=\" width: 80%;padding: 12px;margin: 8px 0;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box; font-size: 16px;\">\n";
    ptr +="<input type=\"password\" id=\"password\" placeholder=\"Enter Password\" required style=\" width: 80%;padding: 12px;margin: 8px 0;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box; font-size: 16px;\">\n";
    
    ptr +="<p id=\"error-message\" style=\"font-size: 18px;text-align: center;margin: 30px;color: red;\">Invalid Username or Password</p>\n";
    
    ptr +="<button onclick=\"validateLogin()\" style=\"width: 80%;background-color: #4a90e2;color: white;padding: 14px;border: none;border-radius: 4px;font-size: 18px;cursor: pointer;margin-top: 10px;\">Unlock</button>\n";
    
    ptr +="<br/><br/><hr/>\n";
    ptr +="<script>\n";
    ptr +="document.getElementById(\"error-message\").hidden = true;\n";
    ptr +="function validateLogin() {\n";
    ptr +="var username = document.getElementById(\"username\").value;var password = document.getElementById(\"password\").value;\n";
    ptr +="if (username === \"admin\" && password === \"123\") {\n";
    ptr +="window.location.href = \"/unlock\";\n";
    ptr +="}else{\n";
    ptr +="document.getElementById(\"error-message\").hidden = false;\n\n";
    ptr +="}}</script>\n";
    ptr +="\n";
    ptr +="\n";
  }
  else{
    ptr +="<h3 style=\"color: red;\">Security System Status : Unlocked</h3>\n";
    ptr +="<p id=\"tt\" style=\"font-size: 18px;text-align: center;margin: 30px;color: #666;\">Please Lock Your Security System</p>\n";
    ptr +="<button onclick=\"validateLogin()\" style=\"width: 80%;background-color: #4a90e2;color: white;padding: 14px;border: none;border-radius: 4px;font-size: 18px;cursor: pointer;margin-top: 10px;\">Lock</button>\n";
    ptr +="<script>\n";
    ptr +="function validateLogin() {\n";
    ptr +="window.location.href = \"/\";\n";
    ptr +="}</script>\n";
    ptr +="<br/><br/><hr/>\n";
  }


  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void setup() {
  Serial.begin(115200);
  pinMode(18, OUTPUT);//BUZZER
  pinMode(5, INPUT); // tilt
  lcd.init();
  lcd.clear();         
  lcd.backlight();      


  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/unlock", handle_unlock);

  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  lcd.setCursor(1,0);  
  lcd.print("Security System");
  lcd.setCursor(0,1);  
  lcd.print("   Loadind...");
  delay(4000);
  lcd.setCursor(0,1);  
  lcd.print(" IP:192.168.1.1");
  delay(4000);
  lcd.setCursor(0,1);  
  lcd.print("    Locked     ");
  
  
}
void loop() {
  server.handleClient();
  while(look){
    server.handleClient();
    while(tt){
      server.handleClient();
      lcd.setCursor(0,1);  
      lcd.print("    Locked     ");
      if(digitalRead(5)){

        digitalWrite(18, LOW);
        
      }
      else{

        tt = false;
        digitalWrite(18, LOW);
        digitalWrite(18, HIGH);
        lcd.setCursor(0,1);  
        lcd.print("   Warning   ");
        break;
      }
    }
    delay(300);
    digitalWrite(18, HIGH);
    lcd.setCursor(0,1);  
    lcd.print("   Warning   ");
    delay(300);
    digitalWrite(18, LOW);
    lcd.setCursor(0,1);  
    lcd.print("             ");
  }

  digitalWrite(18, LOW);
  lcd.setCursor(0,1);  
  lcd.print("   UnLocked    ");
  tt = true;

}
