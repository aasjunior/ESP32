#include "WebServerManager.h"
#include "PreferencesManager.h"
#include "FileSystem.h"
#include <ArduinoJson.h>

void WebServerManager::init(AsyncWebServer& server) {
    if (!SPIFFS.begin()) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    // Servindo arquivos estáticos (HTML, CSS, JS)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });
    server.on("/assets/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/css/styles.css", "text/css");
    });
    server.on("/assets/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/js/main.js", "application/javascript");
    });

    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        String body;
        if (request->hasParam("plain", true)) {
            body = request->getParam("plain", true)->value();
        }
        StaticJsonDocument<200> doc;
        deserializeJson(doc, body);
        String ssid = doc["ssid"];
        String password = doc["password"];

        PreferencesManager::saveCredentials(ssid, password);
        request->send(200, "text/plain", "Credenciais salvas. Reinicie o dispositivo.");
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
        PreferencesManager::clearCredentials();
        request->send(200, "text/plain", "Configurações resetadas.");
    });

    // Nova rota para escanear redes Wi-Fi
    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
        int n = WiFi.scanNetworks();
        StaticJsonDocument<500> doc;

        for (int i = 0; i < n; i++) {
            JsonObject obj = doc.createNestedObject();
            obj["ssid"] = WiFi.SSID(i);
        }

        String json;
        serializeJson(doc, json);
        request->send(200, "application/json", json);
    });

    server.begin();
    Serial.println("Servidor iniciado.");
}
