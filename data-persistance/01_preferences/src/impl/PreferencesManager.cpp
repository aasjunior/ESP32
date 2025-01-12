#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(const char* ns, bool isReadOnly) : namespaceName(ns){
    nvs_flash_init();
    preferences.begin(namespaceName, isReadOnly);
}

PreferencesManager::~PreferencesManager(){
    preferences.end();
}

template <>
void PreferencesManager::saveData<int>(const std::string& key, const int& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putInt(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getInt(key.c_str(), 0));
}

template <>
void PreferencesManager::saveData<float>(const std::string& key, const float& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putFloat(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getFloat(key.c_str(), 0.0));
}

template <>
void PreferencesManager::saveData<double>(const std::string& key, const double& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putDouble(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getDouble(key.c_str(), 0.0));
}

template <>
void PreferencesManager::saveData<std::string>(const std::string& key, const std::string& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putString(key.c_str(), value.c_str());
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getString(key.c_str(), "null"));
}

template <>
void PreferencesManager::saveData<const char*>(const std::string& key, const char* const& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putString(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getString(key.c_str(), "null"));
}

template <>
void PreferencesManager::saveData<char[6]>(const std::string& key, const char (&value)[6]) {
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putString(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getString(key.c_str(), "null"));
}

template <>
void PreferencesManager::saveData<bool>(const std::string& key, const bool& value){
    if(!preferences.isKey(key.c_str())){
        preferences.end();
        preferences.begin(namespaceName, false);
        preferences.putBool(key.c_str(), value);
        preferences.end();
    }

    preferences.begin(namespaceName, true);
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getBool(key.c_str(), false));
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