# uso_consciente_da_agua_iOT
# 💧 Uso Consciente da Água: Monitoramento e Controle Inteligente do Consumo no Chuveiro

Projeto desenvolvido com foco em sustentabilidade e economia de água, utilizando Arduino e IoT. O sistema monitora o tempo e vazão da água durante o banho e desliga automaticamente após 10 minutos, enviando dados para um broker MQTT via Wi-Fi.

---

## 🎯 Objetivo

Reduzir o desperdício de água em banhos por meio de um sistema inteligente de controle de tempo e consumo, promovendo hábitos sustentáveis e automatizando o corte do fluxo.

---

## 🧠 Funcionamento

- O sensor de fluxo mede a vazão da água.
- O Arduino calcula o tempo e o volume total consumido.
- Após 10 minutos de banho, o sistema corta a água automaticamente via eletroválvula.
- Todos os dados são enviados via MQTT para um broker.
- É possível ligar/desligar remotamente via comandos MQTT.

---

## 🔌 Componentes Utilizados

| Componente               | Função                            | Fabricante         |
|--------------------------|-----------------------------------|--------------------|
| Arduino Uno              | Microcontrolador                  | Arduino.cc         |
| Sensor de Fluxo YF-S201  | Mede a vazão da água              | Seed Studio        |
| Módulo Relé 5V           | Aciona a eletroválvula            | Keyestudio         |
| Eletroválvula 12V        | Interrompe o fluxo de água        | JP Fluid Control   |
| Módulo Wi-Fi ESP8266     | Comunicação MQTT via Wi-Fi        | Espressif          |
| Display LCD 16x2         | Exibição local dos dados (opcional) | SparkFun/Hitachi |

---

## 📡 Comunicação MQTT

- **Broker:** Eclipse Mosquitto (na nuvem)
- **Tópicos publicados:**
  - `agua/fluxo`: vazão em L/min
  - `agua/litros`: volume total
- **Tópico assinado:**
  - `agua/comando`: comandos "ligar" ou "desligar"

---

## 💻 Estrutura do Projeto

```bash
.
├── README.md
├── codigo/
│   └── sistema_agua.ino
├── docs/
│   ├── hardware.md
│   ├── comunicacao_mqtt.md
│   └── instrucoes_execucao.md
├── imagens/
│   ├── esquema_fritzing.png
│   └── fluxograma_funcionamento.png

🛠️ Ferramentas Utilizadas
Arduino IDE (linguagem C++)

Simulador Wokwi

Broker Eclipse Mosquitto

Cliente MQTT.fx

Fritzing (diagrama)

📚 Referências
Atzori et al. (2010). The Internet of Things: A Survey

Dornelas & Campello (2015). Monitoramento de Consumo de Água com IoT

Parquet (2015). Controle do tempo de banho

Torres et al. (2016). Desempenho de brokers MQTT

Pinheiro (2019). Gerenciamento de Dispositivos MQTT
