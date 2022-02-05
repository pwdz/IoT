#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>

#define RST_PIN         D3          
#define SS_PIN          D4 
#define LED             D1
#define BUZZER          D2
#define SERVO           D8

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

const char *ssid     = "wood1";
const char *password = "f!rm!n0w00d";

String permitted_card_id = "AC 4B 46 22";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


struct _time{
  int hour;
  int minute;  
};
_time validEntranceTimes[2] = {
  {9, 0}, {23, 50}
};
void setup() 
{
  myservo.attach(SERVO);  // attaches the servo on pin 9 to the servo object
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(BUZZER, OUTPUT);
  
  Serial.begin(9600);   // Initiate a serial communication
  Serial.println("----");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

    // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(12600);
}
_time getTime(){
  timeClient.update();
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();

  _time t; 
  t.hour = currentHour;
  t.minute = currentMinute;

  return t;
}
String checkCard(){
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    return "";
    
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    return "";
    
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  return content;
}
bool checkID(String content){
  
  if (content.substring(1) == permitted_card_id) //change UID of the card that you want to give access
    return true;
  else   
    return false;
    
}
bool checkTime(_time t){

  if(t.hour > validEntranceTimes[0].hour || (t.hour == validEntranceTimes[0].hour && t.minute >= validEntranceTimes[0].minute)){
    if(t.hour < validEntranceTimes[1].hour || (t.hour == validEntranceTimes[1].hour && t.minute <= validEntranceTimes[1].minute)){
       Serial.print("now: ");
       Serial.print(t.hour);
       Serial.print(":");
       Serial.println(t.minute);

       Serial.print("Start: ");
       Serial.print(validEntranceTimes[0].hour);
       Serial.print(":");
       Serial.println(validEntranceTimes[0].minute);

       Serial.print("End: ");
       Serial.print(validEntranceTimes[1].hour);
       Serial.print(":");
       Serial.println(validEntranceTimes[1].minute);
       return true;
    }
  }
  return false;
}
void grantAccess(){
  Serial.println(" Access Granted ");  
  digitalWrite(LED, HIGH);
  if(pos <= 180){
    pos = 180;
    myservo.write(pos);
  }
  
  delay(3000);
  digitalWrite(LED, LOW);
  pos = 0;
  myservo.write(pos);
  
}
void denyAccess(){
  Serial.println(" Access Denied ");
  digitalWrite(BUZZER, HIGH);  
  delay(3000);
  digitalWrite(BUZZER, LOW);
}
void loop() 
{
//  Serial.println("WTF");
//  return;
  String content = checkCard();
  if(content != ""){
    _time t = getTime();
    if(checkID(content) && checkTime(t)){
      grantAccess();
    }else{
      denyAccess();
    }
  }
  
    
  
} 
