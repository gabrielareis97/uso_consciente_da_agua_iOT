⚙️ Pré-requisitos
Placa NodeMCU ESP8266 (ou ESP32, se adaptado)

Sensor de fluxo de água YF-S201

Módulo Relé 5V

Eletroválvula 12V

Display LCD 16x2 com módulo I2C (opcional, mas recomendado)

Fonte 12V DC (para alimentação da válvula)

Jumpers e Protoboard (ou placa de circuito)

🛠️ Instalação das Dependências
Baixe e instale a IDE Arduino:
👉 https://www.arduino.cc/en/software

Adicione a placa NodeMCU ESP8266 na IDE Arduino:

Vá em Arquivo > Preferências

Em URLs adicionais para gerenciadores de placas, adicione:

http://arduino.esp8266.com/stable/package_esp8266com_index.json

Depois vá em Ferramentas > Placa > Gerenciador de Placas e instale esp8266.

Instale as bibliotecas necessárias:
No menu Sketch > Incluir Biblioteca > Gerenciar Bibliotecas, instale:

ESP8266WiFi (ou ESP32WiFi se estiver usando ESP32)

PubSubClient (para comunicação MQTT)

LiquidCrystal_I2C (para exibir informações no LCD)

🌐 Configuração de Rede e MQTT
Abra o arquivo sistema_agua.ino e edite as seguintes linhas:

const char* ssid = "SEU_SSID";            // Nome da sua rede Wi-Fi
const char* password = "SUA_SENHA";       // Senha da sua rede Wi-Fi
const char* mqtt_server = "BROKER_URL";   // Endereço do broker MQTT

Utilize um broker MQTT. Você pode escolher:

Local: usando Mosquitto em um PC ou Raspberry Pi.

Nuvem: serviços gratuitos como:

HiveMQ Cloud

CloudMQTT

Mosquitto Test Server

🔌 Montagem do Hardware
Sensor de fluxo YF-S201 → GPIO4 (D2)

Módulo Relé → GPIO2 (D4) → Aciona a eletroválvula de 12V

Display LCD I2C (opcional) → Barramento I2C do NodeMCU

Fonte 12V DC → Alimenta a eletroválvula (o NodeMCU pode ser alimentado por USB)

🖼️ O esquema elétrico está na pasta /docs no arquivo esquema_fritzing.png.

🚀 Execução
Faça upload do código sistema_agua.ino para o NodeMCU.

Abra o Monitor Serial (baud rate: 115200) para acompanhar:

Conexão ao Wi-Fi

Conexão ao broker MQTT

Leitura dos sensores

Monitore os tópicos MQTT:

agua/fluxo → vazão em L/min

agua/litros → volume total em litros

Envie comandos no tópico agua/comando:

"ligar" → abre a válvula

"desligar" → fecha a válvula

O sistema desliga automaticamente a água após 10 minutos de uso contínuo, publicando também um alerta via MQTT.

🧪 Testes Recomendados
✅ Gire manualmente o sensor de fluxo (ou simule no Wokwi) e confira se a vazão e o volume são atualizados corretamente.

✅ Verifique se, ao atingir 10 minutos de banho, o sistema fecha a válvula automaticamente.

✅ Teste os comandos MQTT:

Envie desligar → o relé aciona e corta a água.

Envie ligar → o relé libera novamente o fluxo.

💡 Observações
O sistema pode ser integrado a um dashboard MQTT (ex.: Node-RED, Grafana, Home Assistant) para visualização dos dados em tempo real.

