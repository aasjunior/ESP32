# Informações do Esp32

Obtendo informações do **Esp32** via codigo.

#### Refatorado 😉

```cpp
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
    uint64_t macId;
    const char* sdkVersion;
    int cpuFreq;
    uint32_t flashSize;
    uint32_t flashSpeed;
    size_t sketchSize;

    // SPIFFS
    uint32_t totalBytes;
    uint32_t usedBytes;

    // Heap
    size_t heapSize;
    size_t freeHeapSize;
};


#endif // ESP_INFO_H
```