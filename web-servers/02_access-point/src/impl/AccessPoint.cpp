#include "AccessPoint.h"

void AccessPoint::startAP(const char* ssid, const char* password){
    WiFi.softAP(ssid, password);
    Serial.println("Access Point iniciado. SSID: " + String(ssid));
}

void AccessPoint::connectToWiFi(const String& ssid, const String& password){
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Conectando à rede WiFi: " + ssid);
}

bool AccessPoint::isConnected(){
    return WiFi.status() == WL_CONNECTED;
}