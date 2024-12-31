#ifndef STATIC_FILE_ROUTES_H
#define STATIC_FILE_ROUTES_H

#include <ESPAsyncWebServer.h>
#include <unordered_map>

// Definir especialização de std::hash para String
namespace std {
    template <>
    struct hash<String> {
        std::size_t operator()(const String& s) const noexcept {
            return hash<string>()(string(s.c_str()));
        }
    };
}

class StaticFileRoutes {
public:
    static void serverFileRoutes(AsyncWebServer &server); // & -> referência ao servidor
    static String getContentType(const String& filename);

private:
    static const std::unordered_map<String, String> mimeTypes;
};

#endif // STATIC_FILE_ROUTES_H
