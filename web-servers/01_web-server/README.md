# Estado de botões em tempo real

Servindo pagina web que atualiza estados de dois botões conectados ao ESP32

###

Crie um arquivo `Credentials.h` dentro de `/include` e insira o nome e a senha da sua rede WiFi:

```cpp
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
```

## Testando a Aplicação

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

3. A página `HTML` usa `AJAX/jQuery` para buscar o estado dos botões a cada 1 segundo.

4. O estado dos botões (`pressionado/solto`) será exibido dinamicamente na página.
