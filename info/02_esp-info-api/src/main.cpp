#include <Arduino.h>
#include "EspInfo.h"
#include "WebServerManager.h"
#include "WiFiManager.h"
#include "Credentials.h"

EspInfo espInfo;
WiFiManager wifi(ssid, password);
WebServerManager webServer;

void formatLittleFS() {
  if (!LittleFS.begin()) {
    Serial.println("Mount failed, formatting...");
    LittleFS.format();
    if (!LittleFS.begin()) {
      Serial.println("Failed to mount after formatting");
      return;
    }
  }
  Serial.println("LittleFS mounted successfully");
}

void setup() {
  Serial.begin(115200);

  formatLittleFS();
  
  if(wifi.connect() == WIFI_CONNECTED) {
    webServer.begin();
  }else {
    Serial.println("Falha ao conectar no WiFi");
  }
}

void loop() {
  // Por enquanto, vaziozio ;)
}