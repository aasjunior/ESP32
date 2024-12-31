#include "LittleFSManager.h"

bool LittleFSManager::mount(){
    if (!LittleFS.begin()) {
        Serial.println("Mount failed :(");
        return false;
    }
    Serial.println("LittleFS mounted successfully");
    return true;
}

bool LittleFSManager::format() {
    LittleFS.format();
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount after formatting");
        return false;
    }
    Serial.println("LittleFS mounted successfully");
    return true;
}