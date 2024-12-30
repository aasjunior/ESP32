#include "EspInfo.h"

EspInfo::EspInfo(){
    // Inicialização, por enquanto vaziozio ;)
}

EspInfo::~EspInfo(){
    // Limpeza, por enquanto vaziozio ;)
}

void EspInfo::getChipInfo(){
    esp_chip_info(&chipInfo);
    macId = ESP.getEfuseMac();
    sdkVersion = ESP.getSdkVersion();
    flashSize = ESP.getFlashChipSize() / (1024 * 1024);
    flashSpeed = ESP.getFlashChipSpeed() / 1000000;
    cpuFreq = ESP.getCpuFreqMHz();
    sketchSize = ESP.getSketchSize();

    Serial.printf("Chip ID: %u\n", macId);
    Serial.printf("SDK Version: %s", sdkVersion);
    Serial.printf("Model: %d\n", chipInfo.model);
    Serial.printf("Cores: %d\n", chipInfo.cores);
    Serial.printf("Features: %d\n", chipInfo.features);
    Serial.printf("Revision: %d\n", chipInfo.revision);
    Serial.printf("CPU Frequency: %d MHz\n", cpuFreq);
    Serial.printf("Flash: %dMB %s\n", flashSize,
                (chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    Serial.printf("Flash Speed: %u MHz\n", flashSpeed);
    Serial.printf("Sketch Size: %u KB\n", sketchSize / 1024);
}

void EspInfo::getSPIFFSInfo(){
    if(!SPIFFS.begin(true)){
        Serial.println("An error has occurred while mounting SPIFFS :( .");
        return;
    }

    totalBytes = SPIFFS.totalBytes();
    usedBytes = SPIFFS.usedBytes();

    Serial.printf("Total SPIFFS Space: %u bytes\n", totalBytes); 
    Serial.printf("Used SPIFFS Space: %u bytes\n", usedBytes);
}

void EspInfo::getHeapInfo(){
    heapSize = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    freeHeapSize = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);

    Serial.printf("Total Heap Size: %u bytes\n", heapSize); 
    Serial.printf("Free Heap Size: %u bytes\n", freeHeapSize);
}