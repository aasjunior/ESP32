#include <Arduino.h>
#include "PreferencesManager.h"

#define WRITE_MODE false
#define READ_MODE true

PreferencesManager prefs("teste", READ_MODE);

void setup() {
  Serial.begin(115200);

  prefs.saveData("testInt", 46);
  prefs.saveData("testFloat", 3.14);
  prefs.saveData("testString", std::string("teste"));
  prefs.saveData("testBool", true);
  prefs.saveData("testLong", -220226);

  prefs.saveData("testInt", 49);
  prefs.saveData("testFloat", 4.13);
  prefs.saveData("testString", std::string("modified"));
  prefs.saveData("testBool", false);
  prefs.saveData("testLong", -12454124);

  //prefs.teste();
}

void loop() {
  // nada a ser feito no loop
}
