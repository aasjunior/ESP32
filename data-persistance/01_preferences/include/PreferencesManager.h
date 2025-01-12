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
    void saveData(const char* key, const T& value);

    template <typename T>
    void readData(const char* key, T& value);

    void removeData(const char* key);

    void teste();

private:
    Preferences preferences;
    const char* namespaceName;
};

#endif // PREFERENCES_MANAGER_H