# 💧 Código do Sistema - Controle Inteligente de Consumo de Água

Este arquivo contém o código-fonte do sistema desenvolvido em C++ utilizando a IDE Arduino para o microcontrolador NodeMCU ESP8266.

## ▶️ Funcionalidades:

- Leitura do fluxo de água em L/min.
- Contagem do volume total em litros.
- Monitoramento do tempo de banho.
- Desligamento automático da válvula após 10 minutos de banho.
- Comunicação MQTT:
  - Publicação dos dados (`agua/fluxo`, `agua/litros`).
  - Recebimento de comandos (`agua/comando` → `ligar` ou `desligar`).

## 📚 Bibliotecas utilizadas:

- `Wire.h` – comunicação I2C
- `LiquidCrystal_I2C.h` – controle do display LCD
- `ESP8266WiFi.h` – conexão Wi-Fi
- `PubSubClient.h` – comunicação MQTT

## 📡 Tópicos MQTT:

- `agua/fluxo` → publica vazão em L/min
- `agua/litros` → publica volume total acumulado
- `agua/comando` → recebe comandos: `ligar` ou `desligar`

---

Para executar este código, configure seu `ssid`, `password` e `mqtt_server` nas variáveis do código.


