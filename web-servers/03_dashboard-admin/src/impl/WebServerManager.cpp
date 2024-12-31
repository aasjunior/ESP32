#include "WebServerManager.h"
#include "StaticFileRoutes.h"
#include <SPIFFS.h>

WebServerManager::WebServerManager() : server(80){
    // Construtor vaziozio ;)
}

WebServerManager::~WebServerManager(){
    // Destrutor vaziozio ;)
}


void WebServerManager::begin() {
    if(!SPIFFS.begin()) { 
        Serial.println("An error has occurred while mounting SPIFFS"); 
        return;
    }

    StaticFileRoutes::serverFileRoutes(server);
    server.begin();
    Serial.println("HTTP server started");
}