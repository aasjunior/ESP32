#include <Arduino.h>
#include "EspInfo.h"
#include "WebServerManager.h"
#include "WiFiManager.h"
#include "Credentials.h"

EspInfo espInfo;
WiFiManager wifi(ssid, password);
WebServerManager webServer;

void setup() {
  Serial.begin(115200);

  if(wifi.connect() == WIFI_CONNECTED) {
    webServer.begin();
  }else {
    Serial.println("Falha ao conectar no WiFi");
  }
}

void loop() {
  // Por enquanto, vaziozio ;)
}