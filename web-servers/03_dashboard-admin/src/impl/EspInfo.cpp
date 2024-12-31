#include "EspInfo.h"

EspInfo::EspInfo(){
    // Inicialização, por enquanto vaziozio ;)
}

EspInfo::~EspInfo(){
    // Limpeza, por enquanto vaziozio ;)
}

ChipInfo EspInfo::getChipInfo(){
    esp_chip_info(&chipInfo.chipInfo);
    chipInfo.macId = ESP.getEfuseMac();
    chipInfo.sdkVersion = ESP.getSdkVersion();
    chipInfo.flashSize = ESP.getFlashChipSize() / (1024 * 1024);
    chipInfo.flashSpeed = ESP.getFlashChipSpeed() / 1000000;
    chipInfo.cpuFreq = ESP.getCpuFreqMHz();
    chipInfo.sketchSize = ESP.getSketchSize();

    return chipInfo;
}

LittleFSInfo EspInfo::getLittleFSInfo(){
    if(!LittleFS.begin()){
        Serial.println("An error has occurred while mounting LittleFS :( .");
        //return;
    }

    littleFSInfo.totalBytes = LittleFS.totalBytes();
    littleFSInfo.usedBytes = LittleFS.usedBytes();

    return littleFSInfo;
}

HeapInfo EspInfo::getHeapInfo(){
    heapInfo.heapSize = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    heapInfo.freeHeapSize = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);

    return heapInfo;
}

// Não da pra ser implementado em esp32 convencionais (esp-wroom) - Sem sensor embutido :(
// https://www.espboards.dev/blog/esp32-inbuilt-temperature-sensor/
float EspInfo::getInternalTemp(){
    return 47.5;
}