#include <WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>

// ==========================
// Configurações Wi-Fi
// ==========================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==========================
// Configurações MQTT
// ==========================
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic_pub = "chuveiro/consumo";
const char* mqtt_topic_sub = "chuveiro/comando";
const char* mqtt_topic_alerta = "chuveiro/alerta";

// ==========================
// Pinos
// ==========================
const int ledPin = 2;  // LED interno do ESP32 (GPIO2 no Wokwi)

// ==========================
// Variáveis de controle
// ==========================
float consumo = 0.0;
bool valvulaAberta = true;
unsigned long tempoLigado = 0; // em segundos

// ==========================
// Instâncias
// ==========================
WiFiClient espClient;
PubSubClient client(espClient);
Ticker timer;

// ==========================
// Conectar Wi-Fi
// ==========================
void conectaWiFi() {
  Serial.print("Conectando no Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    int tentativas = 0;
    while (WiFi.status() != WL_CONNECTED && tentativas < 10) {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
      Serial.print(".");
      tentativas++;
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("\n❌ Falha na conexão. Tentando novamente...");
    }
  }

  Serial.println("\n✅ Wi-Fi conectado!");
  Serial.println(WiFi.localIP());
  // Acende LED fixo por 2 segundos
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
}

// ==========================
// Callback MQTT
// ==========================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📩 Mensagem recebida no tópico: ");
  Serial.println(topic);

  String comando = "";

  for (unsigned int i = 0; i < length; i++) {
    comando += (char)payload[i];
  }

  Serial.print("👉 Comando: ");
  Serial.println(comando);

  if (comando == "FECHAR") {
    valvulaAberta = false;
    tempoLigado = 0;
    digitalWrite(ledPin, LOW);
    Serial.println("✅ Válvula FECHADA manualmente.");
  } else if (comando == "ABRIR") {
    valvulaAberta = true;
    tempoLigado = 0;
    digitalWrite(ledPin, LOW);
    Serial.println("✅ Válvula ABERTA manualmente.");
  } else {
    Serial.println("⚠️ Comando desconhecido.");
  }
}

// ==========================
// Reconectar MQTT
// ==========================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Chuveiro")) {
      Serial.println("✅ Conectado!");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("❌ Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

// ==========================
// Função chamada pelo Timer
// ==========================
void enviaConsumo() {
  if (valvulaAberta) {
    tempoLigado += 10;

    consumo += 0.5;
    String mensagem = String(consumo);
    client.publish(mqtt_topic_pub, mensagem.c_str());
    Serial.print("💧 Consumo publicado: ");
    Serial.println(mensagem);

    // Pisca LED rapidamente uma vez (simulando envio)
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);

    // ALERTA aos 5 minutos (300s)
    if (tempoLigado == 300) {
      Serial.println("⚠️ ALERTA: 5 minutos de uso!");
      client.publish(mqtt_topic_alerta, "ALERTA: 5 minutos de uso do chuveiro!");
      digitalWrite(ledPin, HIGH); // LED aceso fixo no alerta
    }

    // DESLIGAR aos 10 minutos (600s)
    if (tempoLigado >= 600) {
      valvulaAberta = false;
      Serial.println("🚫 Chuveiro desligado automaticamente após 10 minutos.");
      client.publish(mqtt_topic_alerta, "Chuveiro desligado automaticamente após 10 minutos.");
      piscarLedRapido();
      digitalWrite(ledPin, LOW);
    }
  } else {
    Serial.println("🚫 Válvula fechada. Sem consumo.");
  }
}

// ==========================
// Função piscar rápido ao desligar
// ==========================
void piscarLedRapido() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(150);
  }
}

// ==========================
// Setup
// ==========================
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  conectaWiFi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Inicia timer a cada 10 segundos
  timer.attach(10, enviaConsumo);
}

// ==========================
// Loop principal
// ==========================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
