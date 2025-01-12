Claro! Vou apresentar um passo a passo completo, robusto e didático para a implementação e utilização da biblioteca `Preferences` no ESP32 utilizando o PlatformIO com o framework Arduino, seguindo as melhores práticas.

### Passo 1: Configuração do Ambiente de Desenvolvimento

1. **Instalar o PlatformIO**:
   Se você ainda não tem o PlatformIO instalado, siga as instruções no site oficial [PlatformIO](https://platformio.org/install) para instalar a extensão no Visual Studio Code (VS Code).

2. **Criar um Novo Projeto**:
   Abra o VS Code, clique em `PlatformIO` no painel esquerdo, selecione `New Project`, e configure:
   - **Nome do Projeto**: `esp32_preferences`
   - **Plataforma**: Espressif 32
   - **Placa**: ESP32 Dev Module
   - **Framework**: Arduino

3. **Estrutura do Projeto**:
   O PlatformIO criará a estrutura do projeto com a seguinte hierarquia:
   ```
   esp32_preferences
   ├── include
   ├── lib
   ├── src
   │   └── main.cpp
   ├── platformio.ini
   └── test
   ```

### Passo 2: Configurar o Arquivo `platformio.ini`

Edite o arquivo `platformio.ini` para incluir as bibliotecas necessárias e configurações adicionais:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

### Passo 3: Implementação do Código

Vamos implementar o código para usar a biblioteca `Preferences` para ler e escrever dados na memória não volátil (NVS).

**`src/main.cpp`**:
```cpp
#include <Arduino.h>
#include <Preferences.h>

// Instância da classe Preferences
Preferences preferences;

void saveData(const char* key, int value) {
    // Iniciar a NVS com o namespace "my-app"
    preferences.begin("my-app", false);
    // Salvar o valor associado à chave
    preferences.putInt(key, value);
    // Encerrar a NVS
    preferences.end();
}

int readData(const char* key) {
    // Iniciar a NVS com o namespace "my-app"
    preferences.begin("my-app", true);
    // Ler o valor associado à chave, retornando 0 se não existir
    int value = preferences.getInt(key, 0);
    // Encerrar a NVS
    preferences.end();
    return value;
}

void setup() {
    Serial.begin(115200);

    // Salvar um valor na NVS
    saveData("contador", 42);
    Serial.println("Valor salvo na NVS");

    // Ler o valor da NVS
    int contador = readData("contador");
    Serial.print("Valor do contador lido da NVS: ");
    Serial.println(contador);
}

void loop() {
    // Seu código aqui
}
```

### Passo 4: Compilar e Carregar o Código

1. **Compilar o Código**:
   No VS Code, clique no ícone de `PlatformIO` no painel esquerdo e depois em `Build` para compilar o código.

2. **Carregar o Código no ESP32**:
   Conecte o ESP32 ao computador, selecione a porta correta e clique em `Upload` para carregar o código no dispositivo.

### Passo 5: Testar e Verificar a Saída

1. **Abrir o Monitor Serial**:
   Após carregar o código, clique em `Serial Monitor` para abrir o monitor serial no VS Code.

2. **Verificar a Saída**:
   No monitor serial, você deve ver a saída que confirma a gravação e leitura dos dados na NVS:
   ```
   Valor salvo na NVS
   Valor do contador lido da NVS: 42
   ```

### Melhores Práticas

1. **Namespace**:
   Use namespaces exclusivos para diferentes conjuntos de dados para evitar conflitos.

2. **Tratamento de Erros**:
   Adicione tratamento de erros apropriado para lidar com falhas na leitura/escrita dos dados.

3. **Encerramento da NVS**:
   Sempre chame `preferences.end()` após terminar as operações de leitura/escrita para liberar os recursos.

4. **Persistência de Dados**:
   Utilize a NVS para armazenar dados críticos que precisam ser preservados entre reinicializações.

### Exemplo de Projeto Completo

**`src/main.cpp`**:
```cpp
#include <Arduino.h>
#include <Preferences.h>

// Instância da classe Preferences
Preferences preferences;

void saveData(const char* key, int value) {
    preferences.begin("my-app", false);
    preferences.putInt(key, value);
    preferences.end();
}

int readData(const char* key) {
    preferences.begin("my-app", true);
    int value = preferences.getInt(key, 0);
    preferences.end();
    return value;
}

void setup() {
    Serial.begin(115200);

    saveData("contador", 42);
    Serial.println("Valor salvo na NVS");

    int contador = readData("contador");
    Serial.print("Valor do contador lido da NVS: ");
    Serial.println(contador);
}

void loop() {
    // Seu código aqui
}
```

Isso conclui o passo a passo completo e didático para implementar e utilizar a biblioteca `Preferences` no ESP32 com PlatformIO e framework Arduino, seguindo as melhores práticas. 

#

Sim, usar enums para retornar status de sucesso ou erro é uma abordagem adequada no contexto de desenvolvimento para ESP32, especialmente porque o ESP32, utilizando o framework Arduino, não possui suporte a exceções (exceptions) como em linguagens de alto nível. O uso de enums oferece uma maneira clara e eficiente de comunicar o resultado de funções.

### Justificativa do Uso de Enums

1. **Clareza e Legibilidade**: Enums tornam o código mais legível e autodescritivo. Usar enums para representar diferentes estados de retorno ajuda a evitar erros de interpretação e melhora a clareza do código.

2. **Eficiência**: Enums são eficientes em termos de desempenho. Eles são essencialmente representados por inteiros, o que significa que a verificação do estado de retorno é rápida e direta.

3. **Tipo Seguro**: Enums são tipos seguros e ajudam a evitar valores inválidos, limitando os possíveis estados de retorno às opções definidas.

### Exemplo de Uso

Vamos ver um exemplo de como usar enums para retornar o status de funções no ESP32:

**Definindo o Enum para Status de Erro/Sucesso**:
```cpp
enum Status {
    SUCCESS,
    ERROR_INIT,
    ERROR_READ,
    ERROR_WRITE
};
```

**Usando o Enum em Funções**:
```cpp
#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

Status saveData(const char* key, int value) {
    if (!preferences.begin("my-app", false)) {
        return ERROR_INIT;
    }
    preferences.putInt(key, value);
    preferences.end();
    return SUCCESS;
}

Status readData(const char* key, int &value) {
    if (!preferences.begin("my-app", true)) {
        return ERROR_INIT;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        return ERROR_READ;
    }
    value = preferences.getInt(key, 0);
    preferences.end();
    return SUCCESS;
}

void setup() {
    Serial.begin(115200);

    Status status;
    int value;

    status = saveData("counter", 42);
    if (status == SUCCESS) {
        Serial.println("Data saved successfully.");
    } else {
        Serial.println("Error saving data.");
    }

    status = readData("counter", value);
    if (status == SUCCESS) {
        Serial.print("Data read successfully: ");
        Serial.println(value);
    } else {
        Serial.println("Error reading data.");
    }
}

void loop() {
    // Seu código aqui
}
```

### Outras Abordagens

Além de enums, aqui estão algumas outras abordagens que você pode considerar:

1. **Códigos de Retorno (Return Codes)**:
   - Usar inteiros simples para indicar sucesso ou erro, com diferentes valores para diferentes erros. No entanto, isso pode ser menos claro do que usar enums.

2. **Structs**:
   - Usar structs para retornar um estado mais detalhado, incluindo códigos de erro, mensagens de erro e outros dados relevantes.

3. **Flags e Bits**:
   - Usar flags e bits para representar diferentes estados ou erros, especialmente em sistemas de tempo real onde a eficiência é crucial.

**Exemplo de Uso de Structs**:
```cpp
struct Result {
    Status status;
    int value;
};

Result readData(const char* key) {
    Result result;
    if (!preferences.begin("my-app", true)) {
        result.status = ERROR_INIT;
        return result;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        result.status = ERROR_READ;
        return result;
    }
    result.value = preferences.getInt(key, 0);
    result.status = SUCCESS;
    preferences.end();
    return result;
}

void setup() {
    Serial.begin(115200);

    Result result = readData("counter");
    if (result.status == SUCCESS) {
        Serial.print("Data read successfully: ");
        Serial.println(result.value);
    } else {
        Serial.println("Error reading data.");
    }
}
```

Em resumo, usar enums para retornar status é uma prática adequada e recomendada no desenvolvimento para ESP32. Eles melhoram a legibilidade, eficiência e segurança do tipo do seu código.

#

### Flags e Bits: Conceito e Aplicação

**Flags e Bits** são usados para representar múltiplos estados ou erros em um único valor numérico, onde cada bit no valor representa um estado ou erro específico. Isso é especialmente útil em sistemas de tempo real, onde a eficiência é crucial, porque permite armazenar e manipular vários estados usando operações bitwise rápidas.

### Passo a Passo para Usar Flags e Bits

Vamos detalhar o conceito e mostrar como implementá-lo de forma didática.

#### Passo 1: Entender Flags e Bits

1. **Flag**: Uma flag é um bit em um valor que indica um estado específico ou a presença de um erro. 
2. **Bitwise Operations**: Operações bitwise permitem manipular bits individuais em um valor.

#### Passo 2: Definir Flags Usando Enums

Defina suas flags usando enums para facilitar a leitura e manutenção do código. Cada flag será um bit diferente no valor.

```cpp
enum ErrorFlags {
    FLAG_NONE      = 0b0000,  // Nenhum erro (0000)
    FLAG_ERROR1    = 0b0001,  // Erro 1 (0001)
    FLAG_ERROR2    = 0b0010,  // Erro 2 (0010)
    FLAG_ERROR3    = 0b0100,  // Erro 3 (0100)
    FLAG_ERROR4    = 0b1000   // Erro 4 (1000)
};
```

#### Passo 3: Configurar e Manipular Flags

1. **Definir uma variável para armazenar as flags**:
   ```cpp
   uint8_t errorFlags = FLAG_NONE;
   ```

2. **Configurar uma flag**:
   Use a operação bitwise OR (`|`) para configurar uma flag.

   ```cpp
   errorFlags |= FLAG_ERROR1;  // Configurar o erro 1
   ```

3. **Limpar uma flag**:
   Use a operação bitwise AND com NOT (`& ~`) para limpar uma flag.

   ```cpp
   errorFlags &= ~FLAG_ERROR1;  // Limpar o erro 1
   ```

4. **Verificar uma flag**:
   Use a operação bitwise AND (`&`) para verificar se uma flag está configurada.

   ```cpp
   if (errorFlags & FLAG_ERROR1) {
       Serial.println("Erro 1 está configurado");
   }
   ```

#### Passo 4: Implementar Funções de Manipulação de Flags

Vamos implementar funções para configurar, limpar e verificar flags.

```cpp
#include <Arduino.h>

enum ErrorFlags {
    FLAG_NONE      = 0b0000,
    FLAG_ERROR1    = 0b0001,
    FLAG_ERROR2    = 0b0010,
    FLAG_ERROR3    = 0b0100,
    FLAG_ERROR4    = 0b1000
};

uint8_t errorFlags = FLAG_NONE;

// Função para configurar uma flag
void setFlag(ErrorFlags flag) {
    errorFlags |= flag;
}

// Função para limpar uma flag
void clearFlag(ErrorFlags flag) {
    errorFlags &= ~flag;
}

// Função para verificar uma flag
bool checkFlag(ErrorFlags flag) {
    return errorFlags & flag;
}

void setup() {
    Serial.begin(115200);

    // Configurar FLAG_ERROR1
    setFlag(FLAG_ERROR1);
    Serial.print("FLAGS: ");
    Serial.println(errorFlags, BIN);

    // Verificar FLAG_ERROR1
    if (checkFlag(FLAG_ERROR1)) {
        Serial.println("Erro 1 está configurado");
    }

    // Limpar FLAG_ERROR1
    clearFlag(FLAG_ERROR1);
    Serial.print("FLAGS: ");
    Serial.println(errorFlags, BIN);

    // Verificar FLAG_ERROR1 novamente
    if (!checkFlag(FLAG_ERROR1)) {
        Serial.println("Erro 1 não está configurado");
    }
}

void loop() {
    // Seu código aqui
}
```

#### Passo 5: Testar no ESP32

1. **Compilar e Carregar o Código**:
   Compile e carregue o código no ESP32 usando o PlatformIO.
   
2. **Abrir o Monitor Serial**:
   Verifique a saída no monitor serial para ver as operações com flags sendo realizadas.

### Conclusão

Usar flags e bits é uma maneira eficiente de representar múltiplos estados ou erros em sistemas de tempo real, como no ESP32. As operações bitwise são rápidas e permitem gerenciar estados de forma compacta e eficiente. Usar enums para definir flags melhora a clareza e a manutenção do código.

#

Vamos fazer um comparativo entre os três métodos: structs, enums e flags e bits, considerando vários fatores como armazenamento, desempenho, eficiência e outros impactos no uso do ESP32.

### 1. Structs

**Armazenamento**: 
- As structs ocupam mais espaço na memória, pois cada campo dentro da struct é armazenado como uma unidade separada.
- O tamanho da struct é a soma dos tamanhos de todos os seus campos.

**Desempenho**:
- Acesso direto aos campos da struct é rápido.
- As structs são eficientes para armazenar e acessar grupos de dados heterogêneos relacionados.

**Eficiência**:
- Excelente para organizar dados complexos e garantir que todos os dados relacionados estejam agrupados.
- Menos eficiente em termos de uso de memória comparado a enums e flags e bits.

**Aplicação**:
- Útil para representações de dados mais complexas, como as informações detalhadas sobre um sensor ou dispositivo.
- Boa legibilidade e manutenção do código.

**Exemplo de uso**:
```cpp
struct DeviceStatus {
    bool isConnected;
    int signalStrength;
    float temperature;
};
```

### 2. Enums

**Armazenamento**:
- Ocupam menos espaço que structs, geralmente sendo representados por inteiros (4 bytes).
- Cada valor do enum é uma constante inteira.

**Desempenho**:
- Acesso muito rápido e eficiente.
- As operações com enums são quase instantâneas devido à sua representação simples como inteiros.

**Eficiência**:
- Alta eficiência em termos de memória e velocidade de acesso.
- Fácil de usar para estados e erros claramente definidos.

**Aplicação**:
- Ideal para representar estados discretos ou constantes nomeadas.
- Facilita a leitura e a manutenção do código, prevenindo valores inválidos.

**Exemplo de uso**:
```cpp
enum ConnectionState {
    DISCONNECTED,
    CONNECTED,
    CONNECTING,
    DISCONNECTING
};
```

### 3. Flags e Bits

**Armazenamento**:
- Extremamente eficiente em termos de uso de memória.
- Vários estados podem ser armazenados em um único byte ou inteiro, com cada bit representando uma flag.

**Desempenho**:
- Operações bitwise são extremamente rápidas.
- Verificação, definição e limpeza de flags são operações eficientes.

**Eficiência**:
- Alta eficiência em sistemas de tempo real onde múltiplos estados precisam ser rastreados compactamente.
- Complexidade na leitura e manutenção do código pode aumentar, especialmente para aqueles menos familiarizados com operações bitwise.

**Aplicação**:
- Ideal para sistemas de tempo real e situações onde múltiplos estados booleanos precisam ser gerenciados.
- Utilizado em sistemas embarcados para manter o código compacto e rápido.

**Exemplo de uso**:
```cpp
enum ErrorFlags {
    FLAG_NONE   = 0b0000,
    FLAG_ERROR1 = 0b0001,
    FLAG_ERROR2 = 0b0010,
    FLAG_ERROR3 = 0b0100,
    FLAG_ERROR4 = 0b1000
};

uint8_t errorFlags = FLAG_NONE;

void setFlag(ErrorFlags flag) {
    errorFlags |= flag;
}

void clearFlag(ErrorFlags flag) {
    errorFlags &= ~flag;
}

bool checkFlag(ErrorFlags flag) {
    return errorFlags & flag;
}
```

### Comparativo Resumido

| Critério       | Structs                                    | Enums                                    | Flags e Bits                              |
|----------------|--------------------------------------------|------------------------------------------|-------------------------------------------|
| **Armazenamento** | Ocupa mais espaço                      | Mais compacto que structs               | Extremamente compacto                     |
| **Desempenho**   | Acesso rápido a campos                  | Acesso rápido a valores inteiros        | Operações bitwise extremamente rápidas    |
| **Eficiência**   | Boa para dados complexos                 | Alta eficiência para estados discretos  | Alta eficiência para múltiplos estados    |
| **Aplicação**    | Dados relacionados e complexos           | Estados ou erros definidos              | Múltiplos estados booleanos               |
| **Legibilidade** | Alta legibilidade e manutenção           | Fácil leitura e manutenção              | Complexidade maior na leitura e manutenção|

### Conclusão

A escolha entre structs, enums e flags e bits deve ser baseada nas necessidades específicas do seu projeto:

- **Structs**: Use quando precisar agrupar diferentes tipos de dados relacionados. Boa legibilidade e manutenção do código.
- **Enums**: Use para representar estados discretos ou constantes. Alta eficiência e legibilidade.
- **Flags e Bits**: Use em sistemas de tempo real para múltiplos estados booleanos. Alta eficiência em termos de armazenamento e desempenho, mas pode aumentar a complexidade do código.

Cada abordagem tem suas vantagens e desvantagens, e a escolha certa dependerá do contexto do seu uso no ESP32.

#

Você levantou um ponto excelente. Para garantir a flexibilidade e permitir a manipulação de diferentes tipos de dados (int, float, string, etc.), a melhor abordagem é criar funções sobrecarregadas (overloaded) para cada tipo de dado. Isso permite que você mantenha a organização e a legibilidade do código enquanto lida com diferentes tipos de dados.

Vamos atualizar a classe `PreferencesManager` para incluir funções para diferentes tipos de dados: `int`, `float`, `const char*` (para strings) e `bool`.

### Atualizando a Classe `PreferencesManager`

#### `PreferencesManager.h`

Defina a classe para incluir funções para diferentes tipos de dados:

```cpp
#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Preferences.h>
#include "PreferencesStatus.h"

struct ReadResultInt {
    PreferencesStatus status;
    int value;
};

struct ReadResultFloat {
    PreferencesStatus status;
    float value;
};

struct ReadResultString {
    PreferencesStatus status;
    String value;
};

class PreferencesManager {
public:
    PreferencesManager(const char* ns);
    ~PreferencesManager();

    // Funções para int
    PreferencesStatus saveData(const char* key, int value);
    ReadResultInt readDataInt(const char* key);

    // Funções para float
    PreferencesStatus saveData(const char* key, float value);
    ReadResultFloat readDataFloat(const char* key);

    // Funções para string
    PreferencesStatus saveData(const char* key, const char* value);
    ReadResultString readDataString(const char* key);

    // Funções para bool
    PreferencesStatus saveData(const char* key, bool value);
    ReadResultInt readDataBool(const char* key);

    PreferencesStatus removeData(const char* key);

private:
    Preferences preferences;
    const char* namespaceName;
};

#endif // PREFERENCES_MANAGER_H
```

#### `PreferencesManager.cpp`

Implemente as funções para cada tipo de dado:

```cpp
#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(const char* ns) : namespaceName(ns) {
    // Construtor
}

PreferencesManager::~PreferencesManager() {
    // Destrutor
}

// Funções para int
PreferencesStatus PreferencesManager::saveData(const char* key, int value) {
    if (!preferences.begin(namespaceName, false)) {
        return ERROR_INIT;
    }
    preferences.putInt(key, value);
    int savedValue = preferences.getInt(key, -1);
    preferences.end();
    return (savedValue == value) ? SUCCESS : ERROR_WRITE;
}

ReadResultInt PreferencesManager::readDataInt(const char* key) {
    ReadResultInt result;
    if (!preferences.begin(namespaceName, true)) {
        result.status = ERROR_INIT;
        result.value = 0;
        return result;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        result.status = ERROR_READ;
        result.value = 0;
        return result;
    }
    result.value = preferences.getInt(key, 0);
    preferences.end();
    result.status = SUCCESS;
    return result;
}

// Funções para float
PreferencesStatus PreferencesManager::saveData(const char* key, float value) {
    if (!preferences.begin(namespaceName, false)) {
        return ERROR_INIT;
    }
    preferences.putFloat(key, value);
    float savedValue = preferences.getFloat(key, -1.0);
    preferences.end();
    return (savedValue == value) ? SUCCESS : ERROR_WRITE;
}

ReadResultFloat PreferencesManager::readDataFloat(const char* key) {
    ReadResultFloat result;
    if (!preferences.begin(namespaceName, true)) {
        result.status = ERROR_INIT;
        result.value = 0.0;
        return result;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        result.status = ERROR_READ;
        result.value = 0.0;
        return result;
    }
    result.value = preferences.getFloat(key, 0.0);
    preferences.end();
    result.status = SUCCESS;
    return result;
}

// Funções para string
PreferencesStatus PreferencesManager::saveData(const char* key, const char* value) {
    if (!preferences.begin(namespaceName, false)) {
        return ERROR_INIT;
    }
    preferences.putString(key, value);
    String savedValue = preferences.getString(key, "");
    preferences.end();
    return (savedValue == String(value)) ? SUCCESS : ERROR_WRITE;
}

ReadResultString PreferencesManager::readDataString(const char* key) {
    ReadResultString result;
    if (!preferences.begin(namespaceName, true)) {
        result.status = ERROR_INIT;
        result.value = "";
        return result;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        result.status = ERROR_READ;
        result.value = "";
        return result;
    }
    result.value = preferences.getString(key, "");
    preferences.end();
    result.status = SUCCESS;
    return result;
}

// Funções para bool
PreferencesStatus PreferencesManager::saveData(const char* key, bool value) {
    if (!preferences.begin(namespaceName, false)) {
        return ERROR_INIT;
    }
    preferences.putBool(key, value);
    bool savedValue = preferences.getBool(key, false);
    preferences.end();
    return (savedValue == value) ? SUCCESS : ERROR_WRITE;
}

ReadResultInt PreferencesManager::readDataBool(const char* key) {
    ReadResultInt result;
    if (!preferences.begin(namespaceName, true)) {
        result.status = ERROR_INIT;
        result.value = 0;
        return result;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        result.status = ERROR_READ;
        result.value = 0;
        return result;
    }
    result.value = preferences.getBool(key, false);
    preferences.end();
    result.status = SUCCESS;
    return result;
}

PreferencesStatus PreferencesManager::removeData(const char* key) {
    if (!preferences.begin(namespaceName, false)) {
        return ERROR_INIT;
    }
    if (!preferences.isKey(key)) {
        preferences.end();
        return ERROR_REMOVE;
    }
    preferences.remove(key);
    preferences.end();
    return SUCCESS;
}
```

#### `main.cpp`

Atualize o arquivo principal para testar as novas funções:

```cpp
#include <Arduino.h>
#include "PreferencesManager.h"

// Instanciar a classe com o namespace "my-app"
PreferencesManager preferencesManager("my-app");

void setup() {
    Serial.begin(115200);

    PreferencesStatus status;
    ReadResultInt readResultInt;
    ReadResultFloat readResultFloat;
    ReadResultString readResultString;

    // Testando saveData para int
    status = preferencesManager.saveData("contador", 42);
    if (status == SUCCESS) {
        Serial.println("Int salvo na NVS com sucesso.");
    } else {
        Serial.println("Erro ao salvar int na NVS.");
    }

    // Testando readData para int
    readResultInt = preferencesManager.readDataInt("contador");
    if (readResultInt.status == SUCCESS) {
        Serial.print("Int lido da NVS: ");
        Serial.println(readResultInt.value);
    } else {
        Serial.println("Erro ao ler int da NVS.");
    }

    // Testando saveData para float
    status = preferencesManager.saveData("temperatura", 36.5f);
    if (status == SUCCESS) {
        Serial.println("Float salvo na NVS com sucesso.");
    } else {
        Serial.println("Erro ao salvar float na NVS.");
    }

    // Testando readData para float
    readResultFloat = preferencesManager.readDataFloat("temperatura");
    if (readResultFloat.status == SUCCESS) {
        Serial.print("Float lido da NVS: ");
        Serial.println(readResultFloat.value);
    } else {
        Serial.println("Erro ao ler float da NVS.");
    }

    // Testando saveData para string
    status = preferencesManager.saveData("nome", "ESP32");
    if (status == SUCCESS) {
        Serial.println("String salva na NVS com sucesso.");
    } else {
        Serial.println("Erro ao salvar string na NVS.");
    }

    // Testando readData para string
    readResultString = preferencesManager.readDataString("nome");
    if (readResultString.status == SUCCESS) {
        Serial.print("String lida da NVS: ");
        Serial.println(readResultString.value);
    } else {
        Serial.println("Erro ao ler string da NVS.");
    }

    // Testando saveData para bool
    status = preferencesManager.saveData("conectado", true);
    if (status == SUCCESS) {
        Serial.println("Bool salvo na NVS com sucesso.");
    } else {
        Serial.println("Erro ao salvar bool na NVS.");
    }

    // Testando readData para bool
    ReadResultInt readResultBool = preferencesManager.readDataBool("conectado");
    if (readResultBool.status == SUCCESS) {
        Serial.print("Bool lido da NVS: ");
        Serial.println(readResultBool.value);
    } else {
        Serial.println("Erro ao ler bool da NVS.");
    }

    // Testando removeData
    status = preferencesManager.removeData("contador");
    if (status == SUCCESS) {
        Serial.println("Valor removido da NVS com sucesso.");
    } else {
        Serial.println("Erro ao remover da NVS.");
    }
}

void loop() {
    // Seu código aqui
}
```

### Conclusão

Criar funções sobrecarregadas para diferentes tipos de dados (`int`, `float`, `string`, `bool`) permite a manipulação flexível e robusta dos dados na NVS. Essa abordagem melhora a modularidade e mantém o código organizado e eficiente.

# Testes

Para implementar testes unitários no PlatformIO utilizando o framework Arduino em uma placa ESP32, você pode seguir os seguintes passos:

### 1. Instale o PlatformIO e Crie um Novo Projeto
- Primeiro, instale o PlatformIO IDE. Se você usa o Visual Studio Code, pode instalar a extensão do PlatformIO.
- Crie um novo projeto para a ESP32.

### 2. Adicione a Biblioteca de Testes
Adicione a biblioteca `Unity` ao projeto. No `platformio.ini`, adicione a dependência:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    bblanchon/ArduinoJson@^6.18.5
    jgromes/AsyncTCP@^1.1.1
    me-no-dev/ESP Async WebServer@^1.2.3
```

### 3. Estruture o Código de Teste
Crie uma pasta chamada `test` na raiz do projeto. Dentro dela, crie uma subpasta chamada `test_preferences`. Coloque um arquivo chamado `test_main.cpp`:

```cpp
#include <Arduino.h>
#include <unity.h>
#include "PreferencesManager.h"

PreferencesManager prefs("test_namespace");

void setUp(void) {
    // Configurações necessárias antes de cada teste
}

void tearDown(void) {
    // Limpeza necessária após cada teste
}

void test_save_int_data(void) {
    PersistanceStatus status = prefs.saveData("int_key", 42);
    TEST_ASSERT_EQUAL(SUCCESS, status);
}

void test_read_int_data(void) {
    ReadResultInt result = prefs.readDataInt("int_key");
    TEST_ASSERT_EQUAL(SUCCESS, result.status);
    TEST_ASSERT_EQUAL(42, result.value);
}

void test_save_float_data(void) {
    PersistanceStatus status = prefs.saveData("float_key", 3.14f);
    TEST_ASSERT_EQUAL(SUCCESS, status);
}

void test_read_float_data(void) {
    ReadResultFloat result = prefs.readDataFloat("float_key");
    TEST_ASSERT_EQUAL(SUCCESS, result.status);
    TEST_ASSERT_EQUAL_FLOAT(3.14f, result.value);
}

void setup() {
    UNITY_BEGIN(); // Inicia o Unity framework

    RUN_TEST(test_save_int_data);
    RUN_TEST(test_read_int_data);
    RUN_TEST(test_save_float_data);
    RUN_TEST(test_read_float_data);

    UNITY_END(); // Finaliza o Unity framework
}

void loop() {
    // não é usado
}
```

### 4. Execute os Testes
Abra o terminal no VS Code e rode o seguinte comando para compilar e executar os testes:

```sh
pio test
```

### Melhores Práticas
- **Organize seu código**: Separe os testes em diferentes arquivos com base na funcionalidade.
- **Automatize os testes**: Utilize CI/CD para rodar os testes automaticamente em cada commit.
- **Cubra diferentes cenários**: Inclua testes para diferentes casos de sucesso e falha.
- **Limpeza**: Certifique-se de limpar qualquer estado persistente que possa afetar outros testes.

Esses passos fornecerão uma base sólida para começar a testar seu código com o PlatformIO e Arduino na ESP32. 🚀
