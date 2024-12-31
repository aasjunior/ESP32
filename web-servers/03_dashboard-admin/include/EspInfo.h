#ifndef ESP_INFO_H
#define ESP_INFO_H

#include <driver/adc.h>
#include <esp_adc_cal.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <esp_heap_caps.h>
#include <LittleFS.h>

struct ChipInfo {
    esp_chip_info_t chipInfo;
    uint64_t macId;
    const char* sdkVersion;
    int cpuFreq;
    uint32_t flashSize;
    uint32_t flashSpeed;
    size_t sketchSize;
};

struct LittleFSInfo {
    uint32_t totalBytes;
    uint32_t usedBytes;
};

struct HeapInfo {
    size_t heapSize;
    size_t freeHeapSize;
};

class EspInfo{
public:
    EspInfo(); // Construtor
    ~EspInfo(); // Destrutor
    ChipInfo getChipInfo();
    LittleFSInfo getLittleFSInfo();
    HeapInfo getHeapInfo();
    float getInternalTemp();

private:
    ChipInfo chipInfo;
    LittleFSInfo littleFSInfo;
    HeapInfo heapInfo;
    float internalTemp;   
};


#endif // ESP_INFO_H