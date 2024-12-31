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

  // ChipInfo chipInfo = espInfo.getChipInfo();
  // SPIFFSInfo spiffsInfo =  espInfo.getSPIFFSInfo();
  // HeapInfo heapInfo = espInfo.getHeapInfo();
  // float internalTemp = espInfo.getInternalTemp();

  if(wifi.connect() == WIFI_CONNECTED) {
    webServer.begin();
  }else {
    Serial.println("Falha ao conectar no WiFi");
  }
}

void loop() {
  // Por enquanto, vaziozio ;)
}