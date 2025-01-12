#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>
#include <nvs.h>
#include <nvs_flash.h>

template <typename T>
struct Result{
    bool status;
    T value;
};

class PreferencesManager{
public:
    PreferencesManager(const char* ns, bool isReadOnly = false);
    ~PreferencesManager();

    template <typename T>
    void saveData(const std::string& key, const T& value);

    template <typename T>
    T readData(const std::string& key);

    bool removeData(const std::string& key);

    void getInfo();

private:
    Preferences preferences;
    const char* namespaceName;

    void listPreferences();
    void checkMemoryUsage();
};

template <> 
bool PreferencesManager::readData<bool>(const std::string& key);

template <> 
int PreferencesManager::readData<int>(const std::string& key);

template <> 
long PreferencesManager::readData<long>(const std::string& key);

template <> 
float PreferencesManager::readData<float>(const std::string& key);

template <> 
double PreferencesManager::readData<double>(const std::string& key);

template <> 
std::string PreferencesManager::readData<std::string>(const std::string& key);

#endif // PREFERENCES_MANAGER_H