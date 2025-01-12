#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(const char* ns) : namespaceName(ns){
    nvs_flash_init();
    preferences.begin(namespaceName, false);
}

PreferencesManager::~PreferencesManager(){
    preferences.end();
}

void PreferencesManager::teste(){
    bool testPrefs = preferences.isKey("teste");

    if (!testPrefs) {
        preferences.end();
        preferences.begin(namespaceName, false);

        preferences.putUChar("testChar", 10);
        preferences.putString("testString", "teste");
        preferences.putLong("testLong", -220226);
        preferences.putBool("testBool", true);
        preferences.putFloat("testFloat", 3.14);

        preferences.end();
    }

    preferences.begin(namespaceName, true);
    // Visualizar valores armazenados
    Serial.print("testChar: ");
    Serial.println(preferences.getUChar("testChar", 0));

    Serial.print("testString: ");
    Serial.println(preferences.getString("testString", "default"));

    Serial.print("testLong: ");
    Serial.println(preferences.getLong("testLong", 0));

    Serial.print("testBool: ");
    Serial.println(preferences.getBool("testBool", false));

    Serial.print("testFloat: ");
    Serial.println(preferences.getFloat("testFloat", 0.0));
}