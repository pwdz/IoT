#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "pwdzAP"
#define APPSK  "question5"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);
IPAddress    apIP(10, 30, 30, 1);  
void setup() {
  Serial.begin(9600);
  Serial.println("Configuring access point...");
  Serial.println(WiFi.softAPIP());

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  IPAddress APIP(80, 10, 50, 10);
  IPAddress subnet(255, 255, 255, 0);

  Serial.print("Set permanent AP IP address");
  WiFi.softAPConfig(APIP, APIP, subnet);
  IPAddress myIP = WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  server.handleClient();
}