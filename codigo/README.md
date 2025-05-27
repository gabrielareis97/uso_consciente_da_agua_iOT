# 💧 Código do Sistema - Controle Inteligente de Consumo de Água

Este arquivo contém o código-fonte do sistema desenvolvido em C++ utilizando a IDE Arduino para o microcontrolador **ESP32** (adaptado do NodeMCU ESP8266).

## ▶️ Funcionalidades:

- Simulação do consumo de água em litros (incremento a cada 10 segundos).
- Monitoramento do tempo de banho em segundos.
- Desligamento automático da válvula após 10 minutos de uso contínuo.
- Emissão de alerta aos 5 minutos de uso.
- Comunicação MQTT:
  - Publicação do volume total consumido no tópico `chuveiro/consumo`.
  - Publicação de alertas no tópico `chuveiro/alerta`.
  - Recebimento de comandos no tópico `chuveiro/comando` para abrir ou fechar a válvula.

## 📚 Bibliotecas utilizadas:

- `WiFi.h` – conexão Wi-Fi (ESP32)
- `PubSubClient.h` – comunicação MQTT
- `Ticker.h` – temporizador para envio periódico dos dados

## 📡 Tópicos MQTT:

| Tópico               | Descrição                                      |
|----------------------|------------------------------------------------|
| `chuveiro/consumo`   | Publica o volume total consumido (litros)      |
| `chuveiro/alerta`    | Publica alertas de tempo de uso do chuveiro    |
| `chuveiro/comando`   | Recebe comandos para abrir (`ABRIR`) ou fechar (`FECHAR`) a válvula |

---
