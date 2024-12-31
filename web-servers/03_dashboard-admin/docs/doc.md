## Docs by Copilot

Detalhamaneto dos conceitos aplicados do desenvolvimento da classe para servir os arquivos estáticos da aplicação (`StaticFileRoutes`)

### Arquivo de Cabeçalho (`.h`)

#### Guarda de Inclusão
```cpp
#ifndef STATIC_FILE_ROUTES_H
#define STATIC_FILE_ROUTES_H
```
- **O que é**: Isso é conhecido como "guarda de inclusão". Serve para evitar múltiplas inclusões do mesmo arquivo de cabeçalho, o que poderia causar erros de compilação.
- **Por que usar**: Garante que o código seja incluído apenas uma vez durante a compilação, prevenindo redefinições.

#### Inclusão de Bibliotecas
```cpp
#include <ESPAsyncWebServer.h>
#include <unordered_map>
```
- **ESPAsyncWebServer.h**: Esta biblioteca permite a criação de um servidor web assíncrono no ESP32.
- **unordered_map**: Biblioteca da STL (Standard Template Library) do C++ que fornece a estrutura de dados `unordered_map`, que é um mapa hash.

#### Especialização de `std::hash` para `String`
```cpp
namespace std {
    template <>
    struct hash<String> {
        std::size_t operator()(const String& s) const noexcept {
            return hash<string>()(string(s.c_str()));
        }
    };
}
```
- **O que é**: `std::unordered_map` requer uma função de hash para calcular os índices das chaves. O tipo `String` do Arduino não tem um `std::hash` definido, então essa especialização é necessária.
- **Por que usar**: Permite que `String` seja usado como chave em `unordered_map` definindo como calcular o hash a partir de `String`.

#### Declaração da Classe `StaticFileRoutes`
```cpp
class StaticFileRoutes {
public:
    static void serverFileRoutes(AsyncWebServer &server); // & -> referência ao servidor
    static String getContentType(const String& filename);

private:
    static const std::unordered_map<String, String> mimeTypes;
};
```
- **Métodos Públicos**: 
  - **`serverFileRoutes`**: Configura as rotas no servidor web para servir arquivos estáticos.
  - **`getContentType`**: Retorna o tipo MIME baseado na extensão do arquivo.

- **Membro Privado**: 
  - **`mimeTypes`**: Mapa estático que associa extensões de arquivo aos tipos MIME correspondentes.

#### Finalização da Guarda de Inclusão
```cpp
#endif // STATIC_FILE_ROUTES_H
```
- **O que é**: Fecha a guarda de inclusão iniciada no topo do arquivo.

### Arquivo de Implementação (`.cpp`)

#### Inclusão de Bibliotecas e Arquivo de Cabeçalho
```cpp
#include "StaticFileRoutes.h"
#include <SPIFFS.h>
```
- **StaticFileRoutes.h**: Inclui o arquivo de cabeçalho da classe para definir suas implementações.
- **SPIFFS.h**: Biblioteca para manipulação do sistema de arquivos SPIFFS no ESP32.

#### Inicialização do Mapa de Tipos MIME
```cpp
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
```
- **O que é**: Inicializa o mapa associando extensões de arquivos aos seus tipos MIME.
- **Por que usar**: Facilita a associação entre as extensões de arquivos e os tipos MIME correspondentes de maneira eficiente.

#### Implementação do Método `serverFileRoutes`
```cpp
void StaticFileRoutes::serverFileRoutes(AsyncWebServer &server) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });
    server.on("/assets/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/css/styles.css", "text/css");
    });
    server.on("/assets/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/assets/js/main.js", "application/javascript");
    });

    server.on("/assets/imgs/*", HTTP_GET, [](AsyncWebServerRequest *request) {
        String path = request->url();
        String contentType = StaticFileRoutes::getContentType(path);
        request->send(SPIFFS, path, contentType);
    });
}
```
- **O que é**: Define as rotas no servidor web para servir arquivos estáticos. 
  - **`server.on`**: Configura rotas no servidor para diferentes URLs.
  - **Lambda Functions**: Funções anônimas utilizadas para manipular as requisições HTTP.

#### Implementação do Método `getContentType`
```cpp
String StaticFileRoutes::getContentType(const String& filename) {
    auto it = mimeTypes.find(filename.substring(filename.lastIndexOf('.')));
    if (it != mimeTypes.end()) {
        return it->second;
    }
    return "text/plain"; // Tipo MIME padrão
}
```
- **O que é**: Retorna o tipo MIME baseado na extensão do arquivo.
  - **`filename.substring`**: Extrai a extensão do arquivo.
  - **`mimeTypes.find`**: Procura a extensão no mapa `mimeTypes`.
  - **`it != mimeTypes.end()`**: Verifica se a extensão foi encontrada no mapa.
  - **`it->second`**: Retorna o tipo MIME correspondente.
  - **Tipo MIME Padrão**: Retorna `text/plain` se a extensão não for encontrada no mapa.

### Conceitos Trabalhados

1. **Guarda de Inclusão**: Previne múltiplas inclusões do mesmo arquivo.
2. **Especialização de `std::hash`**: Permite usar `String` do Arduino em `unordered_map`.
3. **Listas de Inicialização de Membros**: Inicializam membros de classe antes da execução do corpo do construtor.
4. **Lambda Functions**: Funções anônimas para manipulação de eventos.
5. **Mapa Hash (`unordered_map`)**: Estrutura de dados eficiente para mapeamento de chaves para valores.

### Conclusão

Essa implementação cria uma estrutura eficiente e robusta para servir arquivos estáticos usando um servidor web no ESP32. Utiliza conceitos avançados de C++ para garantir desempenho, manutenção e extensibilidade.