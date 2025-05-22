
// Inclui bibliotecas necessárias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Define os pinos
#define FLOW_SENSOR_PIN D5
#define RELAY_PIN D4

// Configurações da rede Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do broker MQTT
const char* mqtt_server = "broker.hivemq.com";

// Tópicos MQTT
const char* topic_fluxo = "agua/fluxo";
const char* topic_litros = "agua/litros";
const char* topic_comando = "agua/comando";

// Objetos Wi-Fi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis do sensor de fluxo e controle de tempo
volatile int pulseCount = 0;
float flowRate = 0.0;
float totalLiters = 0.0;
unsigned long startTime = 0;
bool showerRunning = false;

// Função chamada a cada pulso do sensor
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

// Conecta ao Wi-Fi
void setup_wifi() {
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conectando Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  lcd.clear();
  lcd.print("Wi-Fi conectado");
  delay(1000);
  lcd.clear();
}

// Reconecta ao broker MQTT se cair a conexão
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Conectado!");
      client.subscribe(topic_comando);
    } else {
      Serial.print("Falhou. rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente...");
      delay(5000);
    }
  }
}

// Callback: recebe mensagens MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Comando recebido: ");
  Serial.println(message);

  if (message == "desligar") {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Água desligada via MQTT.");
  } else if (message == "ligar") {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Água ligada via MQTT.");
  }
}

// Configurações iniciais
void setup() {
  Serial.begin(115200);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);

  lcd.init();
  lcd.backlight();

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  reconnect();
}

// Loop principal
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static unsigned long lastMillis = 0;
  if (millis() - lastMillis >= 1000) {
    lastMillis = millis();

    flowRate = pulseCount / 7.5;
    float litersPerSecond = flowRate / 60.0;
    totalLiters += litersPerSecond;
    pulseCount = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fluxo: ");
    lcd.print(flowRate, 1);
    lcd.print(" L/m");

    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalLiters, 1);
    lcd.print(" L");

    client.publish(topic_fluxo, String(flowRate, 1).c_str());
    client.publish(topic_litros, String(totalLiters, 1).c_str());

    if (flowRate > 0 && !showerRunning) {
      startTime = millis();
      showerRunning = true;
    }

    if (flowRate == 0 && showerRunning) {
      showerRunning = false;
      Serial.println("Banho encerrado.");
      totalLiters = 0.0;
    }

    if (showerRunning && millis() - startTime >= 10 * 60 * 1000) {
      digitalWrite(RELAY_PIN, HIGH);
      client.publish(topic_comando, "desligado");
      Serial.println("Tempo limite! Água desligada.");
      delay(5000);
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}
