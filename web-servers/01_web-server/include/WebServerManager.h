#ifndef WEB_SERVER_MANAGER_H
#define WEB_SERVER_MANAGER_H

#include <ESPAsyncWebServer.h>

class WebServerManager{
public:
    WebServerManager();
    void begin();

private:
    AsyncWebServer server;
};

#endif