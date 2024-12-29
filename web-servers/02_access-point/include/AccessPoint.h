#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <WiFi.h>

class AccessPoint {
public:
    static void startAP(const char* ssid, const char* password);
    static void connectToWiFi(const String& ssid, const String& password);
    static bool isConnected();
};

#endif