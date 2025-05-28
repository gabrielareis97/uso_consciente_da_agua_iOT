# 💧 Projeto Uso Consciente da Água

Sistema inteligente para controle de consumo de água no chuveiro, baseado em IoT. Mede a vazão, conta o tempo, emite um alerta aos 5 minutos e desliga automaticamente após 10 minutos. Os dados são enviados via MQTT para um broker na nuvem.

---

## 🚀 Funcionamento

- Monitora o tempo e o fluxo da água.
- Exibe informações no display LCD.
- Emite alerta aos 05 minutos
- Desliga automaticamente após 10 minutos.
- Permite controle remoto via MQTT (comandos abrir/fechar).
- Publica dados de fluxo (L/min) e volume total (litros).

---

## 🧠 Tecnologias

•  ESP32 DevKitC

•  Módulo Relé 5V

•  Display LCD 16x2 com Interface I2C

•  LED interno do ESP32 (GPIO 2)

• Protocolo MQTT (Broker público: tcp://broker.hivemq.com:1883)



---

## 📡 Comunicação MQTT

| Publicações         | Descrição                        |
|---------------------|----------------------------------|
| `chuveiro/consumo`        | Vazão em L/min              
| `chuveiro/alerta`       | Emite alerta aos 5min de uso  |

| Assinatura          | Comando                          |
|---------------------|----------------------------------|
| `chuveiro/comando`      | `ABRIR` ou `FECHAR`            |

---

## 🛠️ Documentação

- 🔗 [Hardware](docs/hardware.md)
- 🔗 [Comunicação MQTT](docs/comunicacao_mqtt.md)
- 🔗 [Instruções de Execução](docs/instrucoes_execucao.md)

---

## 🖼️ Imagens

## 🔧 Esquema de Montagem

![Esquema de Montagem](https://github.com/user-attachments/assets/6aaa3c25-3a19-4a77-a755-282b509a65b8)


---

## 🧰 Protótipo Montado

![Protótipo Montado](https://github.com/user-attachments/assets/b55aa417-a97e-487b-8934-35ea3b7354bd)



---

## 🔄 Fluxograma de Funcionamento

![Fluxograma de Funcionamento](imagens/fluxograma.png)



---

## 👨‍💻 Equipe

- Ana Júlia Real Costa
- Gabriela dos Reis Barreto
- Lucas Diniz Fabbri

Universidade Presbiteriana Mackenzie – 2025
