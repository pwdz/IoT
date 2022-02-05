#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"



#define RST_PIN         D3          
#define SS_PIN          D4         

#ifndef APSSID
#define APSSID "pwdz"
#define APPSK  "question6"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

const String key1 = "AC 4B 46 22";

ESP8266WebServer server(80);
String currentMovie = "movie1";

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void play() {
  Serial.println("play");
  Serial.println(server.header(0));
}
void pause(){
  Serial.println("pause");
}
void increaseVolume(){
  Serial.println("increase");
}
void decreaseVolume(){
  Serial.println("decrease");
}
void showName(){
  Serial.println("showname");
  server.send(200, "text/plain", currentMovie);
}
void landingPage(){
  Serial.println("landing...");
  server.send(200, "text/html", MAIN_PAGE);
}
void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  IPAddress ipAP(192,168,1,50);
  WiFi.softAPConfig(ipAP, ipAP, IPAddress(255,255,255,0));
  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  server.on("/play", play);
  server.on("/pause", pause);
  server.on("/increasevolume", increaseVolume);
  server.on("/decreasevolume", decreaseVolume);
  server.on("/showname", showName);
  server.on("/", landingPage);

  server.begin();

}

void loop() {

  server.handleClient();
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	// mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content);

  if(content.substring(1) == key1){
    currentMovie = "movie1";
  }
  else{
    currentMovie = "movie2";
  }
}
/*
String checkCard(){
  // Look for new cards
  Serial.println("=======");
  if ( ! rfid.PICC_IsNewCardPresent()) 
    return "";
    
  Serial.println(":||||||||||||");
  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) 
    return "";
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(rfid.uid.uidByte[i], HEX);
     content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content;
}
int m = millis();
void loop() {
  if(millis()-m >= 500){
    m = millis();
    String content = checkCard();
    Serial.println("gaiidiiiiii");
    if(content != ""){
      Serial.println(content);
      Serial.println(key1);
      Serial.println(content.substring(1)==key1);
      if(content.substring(1) == key1){
        Serial.println("bemola base");
        currentMovie = "movie1";
      }
      else{
        Serial.println("bemola base2");
        currentMovie = "movie2";
      }
    }
  }
  server.handleClient();
}*/