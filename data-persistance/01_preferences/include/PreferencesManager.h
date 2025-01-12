#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>
#include <nvs.h>
#include <nvs_flash.h>

class PreferencesManager{
public:
    PreferencesManager(const char* ns, bool isReadOnly = false);
    ~PreferencesManager();

    void teste();

private:
    Preferences preferences;
    const char* namespaceName;
};

#endif // PREFERENCES_MANAGER_H