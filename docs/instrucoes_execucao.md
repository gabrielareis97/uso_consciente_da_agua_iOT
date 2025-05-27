## ⚙️ Pré-requisitos

- Placa **ESP32 DevKit V4** (ou NodeMCU ESP8266, com adaptações)
- **Módulo Relé 5V**
- **Eletroválvula 12V**
- **Display LCD 16x2 com módulo I2C** (opcional, mas recomendado)
- **Fonte 12V DC** (para alimentação da válvula)
- Jumpers e Protoboard (ou placa de circuito)

---

## 🛠️ Instalação das Dependências

1. **Baixe e instale a IDE Arduino:**  
👉 [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **Adicione a placa ESP32 na IDE Arduino:**  
- Vá em **Arquivo > Preferências**  
- Em **URLs adicionais para gerenciadores de placas**, adicione:  
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

- Depois, vá em **Ferramentas > Placa > Gerenciador de Placas** e instale **esp32**.

3. **Instale as bibliotecas necessárias:**  
No menu **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**, instale:  
- `WiFi` (já vem com ESP32)  
- `PubSubClient` (para comunicação MQTT)  
- `Ticker` (para timers)  
- `LiquidCrystal_I2C` (se usar display LCD)

---

## 🌐 Configuração de Rede e MQTT

Abra o arquivo `sistema_agua.ino` e edite as seguintes linhas conforme sua rede Wi-Fi e broker MQTT:

```cpp
const char* ssid = "SEU_SSID";           // Nome da sua rede Wi-Fi
const char* password = "SUA_SENHA";      // Senha da sua rede Wi-Fi
const char* mqtt_server = "broker.hivemq.com"; // Broker público MQTT
🔗 Broker recomendado:

tcp://broker.hivemq.com:1883 (broker gratuito, sem autenticação)

🏠 Alternativas (opcional):

Local: Mosquitto (PC, Raspberry Pi)

Nuvem: HiveMQ, CloudMQTT, Mosquitto Test Server

🔌 Montagem do Hardware
Módulo Relé → GPIO2 (D4) → Aciona a Eletroválvula 12V

Display LCD I2C (opcional) → Barramento I2C do ESP32 (SDA=21, SCL=22 no padrão)

Fonte 12V DC → Alimenta a eletroválvula

O ESP32 pode ser alimentado pela porta USB

🖼️ O esquema elétrico está na pasta /docs no arquivo esquema_fritzing.png.

🚀 Execução
Faça upload do código sistema_agua.ino para seu ESP32.

Abra o Monitor Serial (baud rate: 115200) e acompanhe:

Conexão ao Wi-Fi

Conexão ao broker MQTT

Publicação dos dados de consumo e alertas

Monitore os tópicos MQTT:

chuveiro/consumo → Publica o volume total consumido (em litros)

chuveiro/alerta → Publica alertas de tempo (5 minutos e desligamento automático)

Envie comandos no tópico chuveiro/comando:

"ABRIR" → Abre a válvula (liga o chuveiro)

"FECHAR" → Fecha a válvula (desliga o chuveiro)

⏱️ O sistema desliga automaticamente após 10 minutos de uso contínuo e publica um alerta no tópico chuveiro/alerta.

🧪 Testes Recomendados
✅ Verifique se os dados de consumo estão sendo publicados corretamente a cada 10 segundos (+0.5 litros).
✅ Confira se o alerta de 5 minutos é enviado corretamente.
✅ Após 10 minutos, o sistema deve desligar automaticamente a válvula e enviar um alerta.
✅ Teste os comandos MQTT:

Envie "FECHAR" → o relé desliga a eletroválvula.

Envie "ABRIR" → o relé abre novamente a válvula.
