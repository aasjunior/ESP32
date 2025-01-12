#include <Arduino.h>
#include "PreferencesManager.h"

#define WRITE_MODE false
#define READ_MODE true

PreferencesManager prefs("teste", READ_MODE);

void setup() {
  Serial.begin(115200);

  prefs.saveData("testInt", 46);
  prefs.saveData("testFloat", 3.14f);
  prefs.saveData("testString", std::string("teste"));
  prefs.saveData("testBool", true);
  prefs.saveData("testLong", -220226);

  prefs.getInfo();

  prefs.saveData("testInt", 49);
  prefs.saveData("testFloat", 4.13f);
  prefs.saveData("testString", std::string("modified"));
  prefs.saveData("testBool", false);
  prefs.saveData("testLong", -12454124);

  prefs.getInfo();

  auto testInt = prefs.readData<int>("testInt");
  auto testFloat = prefs.readData<float>("testFloat");
  auto testBool = prefs.readData<bool>("testBool");
  auto testString = prefs.readData<std::string>("testString");
  auto testLong = prefs.readData<long>("testLong");

  Serial.println(testInt);
  Serial.println(testFloat);
  Serial.println(testBool);
  Serial.println(testString.c_str());
  Serial.println(testLong);

  prefs.removeData("testInt");
  prefs.removeData("testFloat");
  Serial.println(prefs.readData<int>("testInt"));
  prefs.getInfo();
}

void loop() {
  // nada a ser feito no loop
}
