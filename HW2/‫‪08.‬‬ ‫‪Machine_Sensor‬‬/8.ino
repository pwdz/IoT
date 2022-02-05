#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <Servo.h>


#ifndef APSSID
#define APSSID "wood1"
#define APPSK  "f!rm!n0w00d"
#endif
#define echoPin D7 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D6 //attach pin D3 Arduino to pin Trig of HC-SR04
#define BUZZER          D2

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

double duration; // variable for the duration of sound wave travel
double distance; // variable for the distance measurement

int previousDis = 0;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void notifyClients(int distance) {
  ws.textAll(String(distance));
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        // handleWebSocketMessage(arg, data, len);
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

double calculateDistance(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}
void setup(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  initWebSocket();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", MAIN_PAGE);
  });

  server.begin();
}
int m;
void loop() {
  ws.cleanupClients();
  if(millis() - m >= 200){
    m = millis();
    int dis = calculateDistance();
    if(dis != previousDis){
      // Serial.println(dis);
      notifyClients(dis);
      previousDis = dis;
      if(dis < 10){
        digitalWrite(BUZZER, HIGH);  
        digitalWrite(LED_BUILTIN, LOW);  
      }
      else{
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_BUILTIN, HIGH);
      }

    }
  }
}

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
//   AwsFrameInfo *info = (AwsFrameInfo*)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//     data[len] = 0;
//     Serial.print("$$$$$: ");
//     Serial.println((char*)data);
//   }
// }