#ifndef ESP_INFO_API_H
#define ESP_INFO_API_H

#include <ESPAsyncWebServer.h>
#include "EspInfo.h"

class EspInfoAPI {
public:
    static void serverAPIRoutes(AsyncWebServer &server);

private:
    static EspInfo espInfo;
};

#endif // ESP_INFO_API_H