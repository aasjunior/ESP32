#include <Arduino.h>
#include "PreferencesManager.h"

#define WRITE_MODE false
#define READ_MODE true

PreferencesManager prefs("teste", READ_MODE);

void setup() {
  Serial.begin(115200);

  prefs.saveData("testInt", 46);

  prefs.teste();
}

void loop() {
  // nada a ser feito no loop
}
