#include <Arduino.h>
#include "EspInfo.h"

EspInfo espInfo;

void setup() {
  Serial.begin(115200);

  espInfo.getChipInfo();
  espInfo.getSPIFFSInfo();
  espInfo.getHeapInfo();
}

void loop() {
    // Por enquanto, vaziozio ;)
}
