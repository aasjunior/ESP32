#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(const char* ns, bool isReadOnly) : namespaceName(ns){
    nvs_flash_init();
    preferences.begin(namespaceName, isReadOnly);
}

PreferencesManager::~PreferencesManager(){
    preferences.end();
}

template <>
void PreferencesManager::saveData<int>(const char* key, const int& value){
    if(!preferences.isKey(key)){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putInt(key, value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(preferences.getInt(key, 0));
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