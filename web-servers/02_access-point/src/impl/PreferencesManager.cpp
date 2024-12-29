#include "PreferencesManager.h"

static Preferences preferences;

void PreferencesManager::begin() {
    preferences.begin("WiFi-config", false);
}

void PreferencesManager::saveCredentials(const String& ssid, const String& password){
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    Serial.println("Credenciais salvas.");
}

void PreferencesManager::clearCredentials(){
    preferences.clear();
    Serial.println("Credenciais removidas.");
}

String PreferencesManager::getSSID(){
    return preferences.getString("ssid", "");
}

String PreferencesManager::getPassword(){
    return preferences.getString("password", "");
}
