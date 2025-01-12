#include <Arduino.h>
#include "PreferencesManager.h"

#define WRITE_MODE false
#define READ_MODE true

PreferencesManager prefs("teste");

void listPreferences() {
  nvs_handle my_handle;
  esp_err_t err = nvs_open("prefs", NVS_READWRITE, &my_handle);
  if (err != ESP_OK) {
    Serial.printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    return;
  }

  nvs_iterator_t it = nvs_entry_find(NVS_DEFAULT_PART_NAME, "prefs", NVS_TYPE_ANY);
  size_t count = 0;

  while (it != NULL) {
    nvs_entry_info_t info;
    nvs_entry_info(it, &info);
    Serial.printf("Namespace: %s, Key: %s, Type: %d\n", info.namespace_name, info.key, info.type);
    it = nvs_entry_next(it);
    count++;
  }

  Serial.printf("Total keys stored: %d\n", count);
  nvs_close(my_handle);
}

void checkMemoryUsage() {
  nvs_stats_t nvs_stats;
  esp_err_t err = nvs_get_stats(NVS_DEFAULT_PART_NAME, &nvs_stats);
  if (err != ESP_OK) {
    Serial.printf("Error (%s) getting NVS stats!\n", esp_err_to_name(err));
    return;
  }

  Serial.printf("Count: UsedEntries = (%d), FreeEntries = (%d), AllEntries = (%d)\n",
                nvs_stats.used_entries, nvs_stats.free_entries, nvs_stats.total_entries);
  Serial.printf("Namespace Count: (%d)\n", nvs_stats.namespace_count);
}

void setup() {
  Serial.begin(115200);

  prefs.teste();
}

void loop() {
  // nada a ser feito no loop
}
