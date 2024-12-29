#include "FileSystem.h"

bool FileSystem::init(){
    if(!SPIFFS.begin(true)){
        Serial.println("Falha ao inicializar SPIFFS");
        return false;
    }
    Serial.println("SPIFFS inicializado com sucesso!");
    return true;
}