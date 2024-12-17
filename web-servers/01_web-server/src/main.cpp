#include <Arduino.h>
#include "Credentials.h"
#include "WiFiManager.h"
#include "WebServerManager.h"

WiFiManager wifiManager(ssid, password);
WebServerManager webServerManager;

void setup() {
    // Configurar os botões com resistência pull-up
    pinMode(12, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
    Serial.begin(115200);
    if (wifiManager.connect() == WIFI_CONNECTED) {
        webServerManager.begin();
    } else {
        Serial.println("Falha ao conectar no WiFi");
    }
}

void loop() {
}
