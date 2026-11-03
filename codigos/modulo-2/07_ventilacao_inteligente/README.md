# 2.4 — Projeto 2: ventilação inteligente
**Objetivo:** Ligar e acelerar o cooler conforme a temperatura, com histerese, display e alarme.

**Materiais:** Montagem das aulas 2.1 a 2.3 + buzzer ativo 5 V.

| Pino do Arduino | Ligação |
|---|---|
| 2 | dados do DHT22 |
| A4 / A5 | SDA / SCL do LCD |
| 9 | gate do MOSFET (via 100 Ω) |
| 8 | + do buzzer ativo |

⚠️ Só 5–12 V CC. GND comum entre a fonte e o Arduino quando houver MOSFET.

**Bibliotecas:** DHT sensor library, Adafruit Unified Sensor, LiquidCrystal I2C. Ajuste PWM_MIN para o seu cooler (aula 2.3).

Apostila: aula 2.4 · www.e3maker.com.br
