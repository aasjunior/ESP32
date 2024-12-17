#include "WebServerManager.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define BUTTON1_PIN 12
#define BUTTON2_PIN 14

WebServerManager::WebServerManager() : server(80) {}

void WebServerManager::begin() {
    if (!SPIFFS.begin()) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    // Serve arquivos estáticos (HTML, CSS, JS)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });
    server.on("/assets/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/css/styles.css", "text/css");
    });
    server.on("/assets/js/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/js/jquery-3.6.0.min.js", "application/javascript");
    });
    server.on("/assets/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/js/main.js", "application/javascript");
    });

    // Rota para fornecer o status dos botões em JSON
    server.on("/button/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        StaticJsonDocument<256> json;
        json["button1"] = digitalRead(BUTTON1_PIN) == LOW ? "pressed" : "released";
        json["button2"] = digitalRead(BUTTON2_PIN) == LOW ? "pressed" : "released";
        String jsonResponse;
        serializeJson(json, jsonResponse);
        request->send(200, "application/json", jsonResponse);
    });

    server.begin();
    Serial.println("Servidor iniciado!");
}
