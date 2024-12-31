# Esp32 Info API

Obtendo informações do ESP32 atráves de uma API pelo servidor web.

- 📁 **LittleFS**: Sistema de arquivos para microcontroladores, suporte a ddiretórios, mais estabilidade e desempenho do que o **SPIFFS**. 
- 🛜 **EspAsyncWebServer**


Necessário criar um arquivo `Credentials.h` dentro de `/include` e inserir os dados do Wi-Fi para conexão.

```cpp
// include/Credentials.h

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
```

### Endpoints da API

<table>
   <thead>
        <th>Type</th>
        <th>Path</th>
        <th>Obs.</th>
   </thead>
   <tbody>
        <tr>
            <td>GET</td>
            <td>/api/chipinfo</td>
            <td>Informações sobre o chip (MAC ID, SDK, CPU, Memória Flash, Sketch)</td>
        </tr>
        <tr>
            <td>GET</td>
            <td>/api/littlefs</td>
            <td>Informações sobre o LittleFS (espaço total e usado)</td>
        </tr>
        <tr>
            <td>GET</td>
            <td>/api/heapinfo</td>
            <td>Informações sobre a memória Heap (espaço total e usado)</td>
        </tr>
        <tr>
            <td>GET</td>
            <td>/api/internaltemp</td>
            <td>Temperatura interna do chip (Necessário Esp32 com sensor embutido)</td>
        </tr>
   </tbody>
</table>