#include <Arduino.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <Preferences.h>

#define WRITE_MODE false
#define READ_MODE true

Preferences prefs;

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

  // Inicializa a NVS
  nvs_flash_init();

  prefs.begin("prefs", READ_MODE);
  bool testPrefs = prefs.isKey("teste");

  if (!testPrefs) {
    prefs.end();
    prefs.begin("prefs", WRITE_MODE);

    prefs.putUChar("testChar", 10);
    prefs.putString("testString", "teste");
    prefs.putLong("testLong", -220226);
    prefs.putBool("testBool", true);
    prefs.putFloat("testFloat", 3.14);

    prefs.end();
  }

  // Reabre em modo de leitura
  prefs.begin("prefs", READ_MODE);

  // Visualizar valores armazenados
  Serial.print("testChar: ");
  Serial.println(prefs.getUChar("testChar", 0));

  Serial.print("testString: ");
  Serial.println(prefs.getString("testString", "default"));

  Serial.print("testLong: ");
  Serial.println(prefs.getLong("testLong", 0));

  Serial.print("testBool: ");
  Serial.println(prefs.getBool("testBool", false));

  Serial.print("testFloat: ");
  Serial.println(prefs.getFloat("testFloat", 0.0));

  // Listar todas as chaves e contar a quantidade de valores
  Serial.println("Listing all keys and counting values:");
  listPreferences();

  // Verificar o uso de memória
  Serial.println("Checking memory usage:");
  checkMemoryUsage();

  // Editar valores armazenados
  prefs.end();
  prefs.begin("prefs", WRITE_MODE);

  prefs.putUChar("testChar", 20);
  prefs.putString("testString", "modified");
  prefs.putLong("testLong", -12345);
  prefs.putBool("testBool", false);
  prefs.putFloat("testFloat", 6.28);

  prefs.end();

  // Reabre em modo de leitura
  prefs.begin("prefs", READ_MODE);

  // Visualizar valores editados
  Serial.print("Modified testChar: ");
  Serial.println(prefs.getUChar("testChar", 0));

  Serial.print("Modified testString: ");
  Serial.println(prefs.getString("testString", "default"));

  Serial.print("Modified testLong: ");
  Serial.println(prefs.getLong("testLong", 0));

  Serial.print("Modified testBool: ");
  Serial.println(prefs.getBool("testBool", false));

  Serial.print("Modified testFloat: ");
  Serial.println(prefs.getFloat("testFloat", 0.0));

  // Excluir valores armazenados
  prefs.end();
  prefs.begin("prefs", WRITE_MODE);

  prefs.remove("testChar");
  prefs.remove("testString");
  prefs.remove("testLong");
  prefs.remove("testBool");
  prefs.remove("testFloat");

  prefs.end();

  // Reabre em modo de leitura para verificar exclusões
  prefs.begin("prefs", READ_MODE);

  Serial.print("Deleted testChar: ");
  Serial.println(prefs.isKey("testChar") ? "exists" : "deleted");

  Serial.print("Deleted testString: ");
  Serial.println(prefs.isKey("testString") ? "exists" : "deleted");

  Serial.print("Deleted testLong: ");
  Serial.println(prefs.isKey("testLong") ? "exists" : "deleted");

  Serial.print("Deleted testBool: ");
  Serial.println(prefs.isKey("testBool") ? "exists" : "deleted");

  Serial.print("Deleted testFloat: ");
  Serial.println(prefs.isKey("testFloat") ? "exists" : "deleted");

  Serial.println("Final listing of keys and count of values:");
  listPreferences();

  // Verificar o uso de memória novamente após as exclusões
  Serial.println("Checking memory usage after deletions:");
  checkMemoryUsage();

  prefs.end();
}

void loop() {
  // nada a ser feito no loop
}
