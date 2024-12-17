#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

WiFiStatus WiFiManager::connect() {
    WiFi.begin(ssid, password);
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
        delay(500);
        Serial.print(".");
        retry++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.println("IP Address: " + WiFi.localIP().toString());
        return WIFI_CONNECTED;
    }
    Serial.println("\nWiFi Connection Failed!");
    return WIFI_FAILED;
}

IPAddress WiFiManager::getIP() {
    return WiFi.localIP();
}
