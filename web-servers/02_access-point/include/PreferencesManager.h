#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>

class PreferencesManager {
public:
    static void begin();
    static void saveCredentials(const String& ssid, const String& password);
    static void clearCredentials();
    static String getSSID();
    static String getPassword();
};

#endif