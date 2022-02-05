#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "index.h"

#ifndef APSSID
#define APSSID "pwdz"
#define APPSK  "question6"
#endif

#define SERVO          D8

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);
Servo myservo;  // create servo object to control a servo

void landingPage() {
  server.send(200, "text/html", MAIN_PAGE);
}
void changeDegree(){
  String body = server.arg("plain");
  Serial.println(body);
  myservo.write(body.toInt());
}


void setup() {
  myservo.attach(SERVO);  // attaches the servo on pin 9 to the servo object
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", landingPage);
  server.on("/degree", changeDegree);
  server.begin();
  Serial.println("HTTP server started");
  myservo.write(0);
}

void loop() {
  server.handleClient();
}
