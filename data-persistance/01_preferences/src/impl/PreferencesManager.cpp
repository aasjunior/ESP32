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
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putInt(key.c_str(), value);

    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getInt(key.c_str(), 0));
    preferences.end();
}

template <>
void PreferencesManager::saveData<float>(const std::string& key, const float& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putFloat(key.c_str(), value);
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getFloat(key.c_str(), 0.0));
    preferences.end();
}

template <>
void PreferencesManager::saveData<double>(const std::string& key, const double& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putDouble(key.c_str(), value);
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getDouble(key.c_str(), 0.0));
    preferences.end();
}

template <>
void PreferencesManager::saveData<std::string>(const std::string& key, const std::string& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putString(key.c_str(), value.c_str());
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getString(key.c_str(), "null"));
    preferences.end();
}

template <>
void PreferencesManager::saveData<const char*>(const std::string& key, const char* const& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putString(key.c_str(), value);
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getString(key.c_str(), "null"));
    preferences.end();
}

template <>
void PreferencesManager::saveData<bool>(const std::string& key, const bool& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putBool(key.c_str(), value);
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getBool(key.c_str(), false));
    preferences.end();
}

template <>
void PreferencesManager::saveData<long>(const std::string& key, const long& value){
    preferences.end();
    preferences.begin(namespaceName, false);
    preferences.putLong(key.c_str(), value);
    
    Serial.println("Valor salvo com sucesso:");
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(preferences.getLong(key.c_str(), -1));
    preferences.end();
}

template <>
int PreferencesManager::readData<int>(const std::string& key) {
    preferences.begin(namespaceName, true);
    int value = preferences.getInt(key.c_str(), 0);
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value);
    return value;
}

template <>
float PreferencesManager::readData<float>(const std::string& key) {
    preferences.begin(namespaceName, true);
    float value = preferences.getFloat(key.c_str(), 0.0f);
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value);
    return value;
}

template <>
std::string PreferencesManager::readData<std::string>(const std::string& key) {
    preferences.begin(namespaceName, true);
    std::string value = preferences.getString(key.c_str(), "default").c_str();
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value.c_str());
    return value;
}

template <>
bool PreferencesManager::readData<bool>(const std::string& key) {
    preferences.begin(namespaceName, true);
    bool value = preferences.getBool(key.c_str(), false);
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value);
    return value;
}

template <>
double PreferencesManager::readData<double>(const std::string& key) {
    preferences.begin(namespaceName, true);
    double value = preferences.getDouble(key.c_str(), 0.0);
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value);
    return value;
}

template <>
long PreferencesManager::readData<long>(const std::string& key) {
    preferences.begin(namespaceName, true);
    long value = preferences.getLong(key.c_str(), 0.0);
    preferences.end();
    Serial.print(key.c_str());
    Serial.print(": ");
    Serial.println(value);
    return value;
}
