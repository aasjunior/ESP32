#ifndef ESP_INFO_H
#define ESP_INFO_H

#include <driver/adc.h>
#include <esp_adc_cal.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <esp_heap_caps.h>
#include <SPIFFS.h>

class EspInfo{
public:
    EspInfo(); // Construtor
    ~EspInfo(); // Destrutor
    void getChipInfo();
    void getSPIFFSInfo();
    void getHeapInfo();

private:
    // Chip
    esp_chip_info_t chipInfo;
    uint8_t macId;
    int cpuFreq;
    uint32_t flashSize;
    uint32_t flashSpeed;

    // SPIFFS
    uint32_t totalBytes;
    uint32_t usedBytes;

    // Heap
    size_t heapSize;
    size_t freeHeapSize;
};


#endif // ESP_INFO_H