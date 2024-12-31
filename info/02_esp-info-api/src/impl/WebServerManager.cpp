#include "WebServerManager.h"
#include "EspInfoAPI.h"
#include <LittleFS.h>

WebServerManager::WebServerManager() : server(80){
    // Construtor vaziozio ;)
}

WebServerManager::~WebServerManager(){
    // Destrutor vaziozio ;)
}


void WebServerManager::begin() {
    if(!LittleFS.begin()) { 
        Serial.println("An error has occurred while mounting LittleFS :("); 
        return;
    }

    EspInfoAPI::serverAPIRoutes(server);
    server.begin();
    Serial.println("HTTP server started");
}
