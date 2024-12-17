# Estado de botões em tempo real

Este projeto implementa um servidor web no **ESP32** que exibe, em uma página web, os estados de dois botões conectados fisicamente ao **ESP32**. A comunicação com a página web é feita por meio de uma **API REST**, utilizando a biblioteca ESPAsyncWebServer para gerenciar as requisições.

## Configuração Inicial

Crie um arquivo `Credentials.h` dentro de `/include` e insira o nome e a senha da sua rede WiFi:

```cpp
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
```

## Configuração dos botões

Conecte os botões aos pinos `12` e `14` do **ESP32** e configure-os no modo `INPUT_PULLUP`. O resistor `pull-up` interno será ativado, eliminando a necessidade de resistores externos.

- Botão 1: GPIO 12
- Botão 2: GPIO 14

## Servindo a Página Web

O **ESP32** utiliza o sistema de arquivos **SPIFFS** para armazenar os arquivos estáticos (`index.html`, `CSS`, `JavaScript`). Antes de rodar o projeto, carregue os arquivos no **ESP32**.

1. Suba os arquivos estáticos para o SPIFFS:

```bash
pio run --target uploadfs
```

2. Compile e suba o firmware para o **ESP32**:

```bash
pio run --target upload
```

3. Abra o monitor serial para ver os logs:

```bash
pio device monitor
```

4. Acesse a página HTML pelo IP do **ESP32** (`http://<IP_DO_ESP32>`).

## Funcionamento

1. Botões físicos conectados aos pinos `GPIO` (exemplo: 12 e 14) serão lidos no ****ESP32****.

2. O **ESP32** disponibiliza o estado atual via `JSON` na rota `/button/status`.

```cpp
// Rota para fornecer o status dos botões em JSON
server.on("/button/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    StaticJsonDocument<256> json;
    json["button1"] = digitalRead(BUTTON1_PIN) == LOW ? "pressed" : "released";
    json["button2"] = digitalRead(BUTTON2_PIN) == LOW ? "pressed" : "released";
    String jsonResponse;
    serializeJson(json, jsonResponse);
    request->send(200, "application/json", jsonResponse);
});
```

3. A página `HTML` usa `AJAX/jQuery` para buscar o estado dos botões a cada 1 segundo.

4. O estado dos botões (`pressionado/solto`) será exibido dinamicamente na página.
