#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>
#include <nvs.h>
#include <nvs_flash.h>

class PreferencesManager{
public:
    PreferencesManager(const char* ns, bool isReadOnly = false);
    ~PreferencesManager();

    template <typename T>
    void saveData(const std::string& key, const T& value);

    template <typename T>
    void readData(const std::string& key, T& value);

    void removeData(const std::string& key);

    void teste();

private:
    Preferences preferences;
    const char* namespaceName;
};

#endif // PREFERENCES_MANAGER_H