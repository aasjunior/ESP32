#include "EspInfoAPI.h"
#include <ArduinoJson.h>

EspInfo EspInfoAPI::espInfo;

void EspInfoAPI::serverAPIRoutes(AsyncWebServer &server) {
    server.on("/api/chipinfo", HTTP_GET, [](AsyncWebServerRequest *request){
        ChipInfo chipInfo = espInfo.getChipInfo();
        JsonDocument doc;
        doc["model"] = chipInfo.chipInfo.model;
        doc["macId"] = chipInfo.macId;
        doc["sdkVersion"] = chipInfo.sdkVersion;
        doc["cpuFreq"] = chipInfo.cpuFreq;
        doc["flashSize"] = chipInfo.flashSize;
        doc["flashSpeed"] = chipInfo.flashSpeed;
        doc["sketchSize"] = chipInfo.sketchSize;

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    server.on("/api/littlefsinfo", HTTP_GET, [](AsyncWebServerRequest *request){
        LittleFSInfo littleFSInfo = espInfo.getLittleFSInfo();
        JsonDocument doc;
        doc["totalBytes"] = littleFSInfo.totalBytes;
        doc["usedBytes"] = littleFSInfo.usedBytes;

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });
    
    server.on("/api/heapinfo", HTTP_GET, [](AsyncWebServerRequest *request){
        HeapInfo heapInfo = espInfo.getHeapInfo();
        JsonDocument doc;
        doc["heapSize"] = heapInfo.heapSize;
        doc["freeHeapSize"] = heapInfo.freeHeapSize;

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });
    
    server.on("/api/internaltemp", HTTP_GET, [](AsyncWebServerRequest *request){
        float internalTemp = espInfo.getInternalTemp();
        JsonDocument doc;
        doc["internalTemp"] = internalTemp;

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });
}