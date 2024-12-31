#include "StaticFileRoutes.h"
#include <LittleFS.h>

// Inicialização do mapa de tipos MIME 
const std::unordered_map<String, String> StaticFileRoutes::mimeTypes = { 
    {".htm", "text/html"}, 
    {".html", "text/html"}, 
    {".css", "text/css"}, 
    {".js", "application/javascript"}, 
    {".png", "image/png"}, 
    {".svg", "image/svg+xml"}, 
    {".gif", "image/gif"}, 
    {".jpg", "image/jpeg"}, 
    {".jpeg", "image/jpeg"}, 
    {".ico", "image/x-icon"} 
};

void StaticFileRoutes::serverFileRoutes(AsyncWebServer &server){
    // Servindo arquivos estáticos (HTML, CSS, JS)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/assets/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/assets/css/styles.css", "text/css");
    });
    server.on("/assets/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/assets/js/main.js", "application/javascript");
    });

    // Servindo arquivos de imagens (MIME -> image/svg, image/png, ...)
    // Rota genérica para servir arquivos de imagem (SVG, PNG, etc.) 
    server.on("/assets/imgs/*", HTTP_GET, [](AsyncWebServerRequest *request) { 
        String path = request->url(); 
        String contentType = StaticFileRoutes::getContentType(path); 
        request->send(LittleFS, path, contentType); 
    });
}

String StaticFileRoutes::getContentType(const String& filename) { 
    auto it = mimeTypes.find(filename.substring(filename.lastIndexOf('.')));
    if(it != mimeTypes.end()){
        return it->second;
    }
    return "text/plain"; // Tipo MIME padrão
}