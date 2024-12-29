#include "AccessPoint.h"
#include "FileSystem.h"
#include "PreferencesManager.h"
#include "WebServerManager.h"

AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);

  // Inicializar o SPIFFS
  if(!FileSystem::init()) return;

  // Inicializar preferências
  PreferencesManager::begin();

  // Recuperar credenciais salvas
  String ssid = PreferencesManager::getSSID();
  String password = PreferencesManager::getPassword();

  if(!ssid.isEmpty()){
    AccessPoint::connectToWiFi(ssid, password);
    if(AccessPoint::isConnected()){
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

  // Exibir o endereço IP do Access Point 
  Serial.println("Modo Access Point iniciado."); 
  Serial.print("Endereço IP do AP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Por hora, vaziozio ;)
}