Para listar os SSIDs disponíveis em vez de pedir ao usuário para inserir manualmente, você pode modificar o código HTML e JavaScript para buscar e exibir as redes Wi-Fi disponíveis. Vou te mostrar como você pode fazer isso.

### Passo 1: Modificar `index.html`
Primeiro, vamos modificar o formulário HTML para usar um `<select>` em vez de um `<input>` para o SSID. Além disso, vamos adicionar um botão para buscar as redes disponíveis:

```html
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./assets/css/styles.css">
    <title>Configuração Wi-Fi</title>
</head>
<body>
    <main>
        <h1>Configuração de Wi-Fi</h1>
        <form id="wifiForm">
            <label for="ssid">SSID:</label>
            <select id="ssid" name="ssid" required>
                <option value="">Selecione uma rede</option>
            </select>
            <button type="button" onclick="fetchNetworks()">Buscar Redes</button><br><br>
            <label for="password">Senha:</label>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Salvar</button>
        </form>
    </main>
    <script src="./assets/js/main.js"></script>
</body>
</html>
```

### Passo 2: Modificar `main.js`
Agora, vamos adicionar a função `fetchNetworks()` no JavaScript para buscar as redes Wi-Fi disponíveis e preencher o `<select>`:

```javascript
document.addEventListener("DOMContentLoaded", function() {
    const wifiForm = document.getElementById("wifiForm");

    wifiForm.addEventListener("submit", async function(event) {
        event.preventDefault();

        const ssid = document.getElementById("ssid").value;
        const password = document.getElementById("password").value;

        const response = await fetch("/save", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ ssid, password })
        });

        if (response.ok) {
            alert("Credenciais salvas. Reinicie o dispositivo.");
        } else {
            alert("Erro ao salvar as credenciais.");
        }
    });
});

async function fetchNetworks() {
    const response = await fetch("/scan");
    const networks = await response.json();
    
    const ssidSelect = document.getElementById("ssid");
    ssidSelect.innerHTML = '<option value="">Selecione uma rede</option>';

    networks.forEach(network => {
        const option = document.createElement("option");
        option.value = network.ssid;
        option.textContent = network.ssid;
        ssidSelect.appendChild(option);
    });
}
```

### Passo 3: Modificar `WebServerManager.cpp`
No código do servidor, adicione uma rota para lidar com a busca de redes Wi-Fi:

```cpp
#include "WebServerManager.h"
#include "PreferencesManager.h"
#include "FileSystem.h"

void WebServerManager::init(AsyncWebServer& server) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        String body;
        if (request->hasParam("plain", true)) {
            body = request->getParam("plain", true)->value();
        }
        StaticJsonDocument<200> doc;
        deserializeJson(doc, body);
        String ssid = doc["ssid"];
        String password = doc["password"];

        PreferencesManager::saveCredentials(ssid, password);
        request->send(200, "text/plain", "Credenciais salvas. Reinicie o dispositivo.");
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
        PreferencesManager::clearCredentials();
        request->send(200, "text/plain", "Configurações resetadas.");
    });

    // Nova rota para escanear redes Wi-Fi
    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
        int n = WiFi.scanNetworks();
        StaticJsonDocument<500> doc;

        for (int i = 0; i < n; i++) {
            JsonObject obj = doc.createNestedObject();
            obj["ssid"] = WiFi.SSID(i);
        }

        String json;
        serializeJson(doc, json);
        request->send(200, "application/json", json);
    });

    server.begin();
    Serial.println("Servidor iniciado.");
}
```

### Passo 4: Modificar `main.cpp`
Certifique-se de que o WiFi esteja configurado para escanear redes:

```cpp
#include "AccessPoint.h"
#include "FileSystem.h"
#include "PreferencesManager.h"
#include "WebServerManager.h"

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);

    // Inicializar SPIFFS
    if (!FileSystem::init()) return;

    // Inicializar preferências
    PreferencesManager::begin();

    // Recuperar credenciais salvas
    String ssid = PreferencesManager::getSSID();
    String password = PreferencesManager::getPassword();

    if (!ssid.isEmpty()) {
        AccessPoint::connectToWiFi(ssid, password);
        if (AccessPoint::isConnected()) {
            Serial.println("Conectado à rede Wi-Fi.");
            return;
        }
    }

    // Iniciar modo Access Point
    AccessPoint::startAP("ESP32_Config", "12345678");

    // Inicializar servidor web
    WebServerManager::init(server);
    
    // Iniciar escaneamento de redes Wi-Fi
    WiFi.scanNetworks(true);
}

void loop() {
    // Nenhuma lógica adicional necessária no loop
}
```

Agora, quando o usuário clicar em "Buscar Redes", o código fará uma solicitação ao servidor para escanear as redes Wi-Fi disponíveis e preencher a lista suspensa com os SSIDs encontrados. Essa abordagem melhora a experiência do usuário e facilita a configuração da rede. Se precisar de mais alguma coisa, estarei aqui para ajudar.