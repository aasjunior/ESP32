#include "WiFiManager.h"

// : -> lista de inicialização de membros
// especialmente importante para membros constantes (const) e referências, 
// que devem ser inicializados no momento da construção do objeto
WiFiManager::WiFiManager(
    const char* ssid, 
    const char* password
) : ssid(ssid), password(password) {
    // Construtor vaziozio ;)
}

WiFiStatus WiFiManager::connect() {
    WiFi.begin(ssid, password);
    int retry = 0;

    while(WiFi.status() != WL_CONNECTED && retry < 20){
        delay(500);
        Serial.print(".");
        retry++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.println("IP Address: " + this->getIP().toString());
        return WIFI_CONNECTED;
    }
    Serial.println("\nWiFi Connection Failed!");
    return WIFI_FAILED;
}

IPAddress WiFiManager::getIP() {
    return WiFi.localIP();
}