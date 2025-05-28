# 🔧 Documentação do Hardware

## 💡 Descrição Geral

Este sistema é composto por um microcontrolador ESP32 DevKit V4, um módulo relé responsável por acionar uma eletroválvula 12V e um display LCD 16x2 (I2C) que serve como interface visual. O objetivo principal do projeto é controlar o tempo de uso da água no chuveiro, promovendo economia e conscientização no consumo. O usuário pode abrir ou fechar o chuveiro manualmente via MQTT, enviando comandos remotos. Além disso, o sistema realiza o monitoramento automático do tempo de uso, gerando alertas e desligando o chuveiro automaticamente se o tempo máximo for atingido.

---

## 🧰 Componentes Utilizados

| Componente                     | Função                                     | Observações                                             |
|---------------------------------|--------------------------------------------|---------------------------------------------------------|
| **ESP32 DevKit V4**             | Microcontrolador principal                 | Conexão Wi-Fi, controle do relé, botão e display LCD    |
| **Módulo Relé 5V**              | Acionamento da eletroválvula               | Conectado no pino GPIO 2                   |
| **Eletroválvula 12V**           | Controla o fluxo de água                   | Abre/fecha a passagem da água (acionada via relé)      |
| **Display LCD 16x2 (I2C)**      | Interface visual para exibir dados         | SDA (GPIO 21) e SCL (GPIO 22) – Endereço I2C: 0x27      |
| **Fonte 12V**                   | Alimentação da eletroválvula               | Necessária no hardware físico                           |
| **Monitor Serial (Wokwi)**      | Debug e visualização de dados na simulação | Comunicação via porta serial (TX/RX)                    |


---

## 🔌 Esquema de Montagem

![image](https://github.com/user-attachments/assets/0b984a1f-a5fd-4fa8-8f6d-26793473407e)

---

## 🧩 Visão dos Componentes




### ⚡ Módulo Relé 5V  
![Relé](../imagens/rele.png)

---
### ⚡ESP32 DevKitC
![image](https://github.com/user-attachments/assets/13dc8881-cd96-40e4-b5fe-1f5cad5c6511)


---

### 🖥️ Display LCD 16x2
![image](https://github.com/user-attachments/assets/71751188-392b-4a78-85d1-a7a81d030ceb)


---


## 📐 Dimensões Sugeridas

| Componente        | Dimensões Aproximadas      |
| ----------------- | -------------------------- |
| ESP32 DevKit V4   | 60mm x 30mm                |
| Módulo Relé       | 50mm x 25mm                |
| Display LCD       | 80mm x 36mm                |
| Caixa Eletrônica  | 120mm x 90mm x 60mm        |
| Eletroválvula 12V | 70mm x 55mm                |


---

## 📸 Foto do Protótipo Montado  

![image](https://github.com/user-attachments/assets/07b7070c-1df3-4429-b81b-22164061e58e)


---

