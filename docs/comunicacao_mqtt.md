## 🛰️ Protocolos Utilizados

* **TCP/IP:** Protocolo de comunicação utilizado para conexão à rede Wi-Fi, permitindo que o NodeMCU se comunique com servidores externos, como o broker MQTT na nuvem.

* **MQTT:** Protocolo leve baseado em publicador/assinante, ideal para aplicações IoT. Ele permite a troca eficiente de mensagens entre o dispositivo (NodeMCU) e o broker, tanto para envio de dados quanto para recebimento de comandos.

---

## 📡 Descrição dos Tópicos MQTT

### 🔹 Tópicos Publicados:

* `agua/fluxo`
  ➡️ Publica a vazão instantânea da água, medida em litros por minuto (L/min).

* `agua/litros`
  ➡️ Publica o volume total de água consumido, em litros (L).

### 🔸 Tópico Assinado:

* `agua/comando`
  ➡️ Recebe comandos MQTT para controle da válvula de água. Os comandos aceitos são:

  * **`ligar`** → Aciona o relé, abrindo a válvula e permitindo a passagem da água.
  * **`desligar`** → Aciona o relé para fechar a válvula, interrompendo o fluxo de água.

---

## 🔄 Funcionamento da Comunicação com o Broker MQTT

1. O NodeMCU ESP8266 conecta-se à rede Wi-Fi utilizando TCP/IP.
2. Estabelece conexão com um broker MQTT na nuvem (Eclipse Mosquitto ou outro).
3. **Publica**, a cada segundo:

   * A vazão de água em `agua/fluxo`.
   * O volume total acumulado em `agua/litros`.
4. **Assina** o tópico `agua/comando` para receber comandos externos que controlam a eletroválvula (abrir/fechar o fluxo de água).
5. Se o tempo de banho ultrapassar o limite (10 minutos):

   * O sistema aciona o relé para fechar a válvula.
   * Publica uma notificação no MQTT.
6. Todo o sistema funciona em tempo real, permitindo monitoramento e controle remoto via qualquer cliente MQTT (como MQTT.fx, dashboards, ou aplicativos personalizados).

---

# 🌐 Comunicação via Internet (TCP/IP) e MQTT

### 🚀 Como funciona:

* O sistema conecta-se à internet via **Wi-Fi (TCP/IP)**.
* Utiliza o protocolo **MQTT** para comunicação com um broker na nuvem.
* Permite:

  * **Envio de dados:** vazão e volume de água em tempo real.
  * **Recebimento de comandos:** para controle da válvula remotamente.
* Essa comunicação garante que os usuários possam monitorar o consumo de água, receber alertas e controlar o sistema de qualquer lugar com acesso à internet.

---


