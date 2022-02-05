#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "wood1"
#define STAPSK  "f!rm!n0w00d"
#endif

void setup() {
  Serial.begin(9600);
  delay(5000);

  WiFi.mode(WIFI_STA);
  
  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);

  scanNetworks();
  connectToWifi();
}
void scanNetworks(){
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* mac;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0) {
    Serial.println(F("No networks found"));
  } else if (scanResult > 0) {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);

    for (int8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, mac, channel, hidden);

      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
                    rssi,
                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                    hidden ? 'Hidden' : 'Visible',
                    ssid.c_str());
    }
  } else {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
}
void connectToWifi(){
  Serial.print("Connecting to ");
  Serial.println(STASSID);

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}