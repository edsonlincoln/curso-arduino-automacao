# 2.2 — Display LCD 16x2 I2C
**Objetivo:** Mostrar temperatura e umidade no display.

**Materiais:** Arduino UNO, DHT22, LCD 16x2 com módulo I2C (PCF8574).

| Pino do Arduino | Ligação |
|---|---|
| 2 | dados do DHT22 |
| A4 | SDA do LCD |
| A5 | SCL do LCD |
| 5V / GND | VCC / GND do LCD e do DHT22 |

⚠️ Só 5–12 V CC. GND comum entre a fonte e o Arduino quando houver MOSFET.

**Bibliotecas:** DHT sensor library, Adafruit Unified Sensor, LiquidCrystal I2C (Frank de Brabander). Endereço 0x27 ou 0x3F (use o scanner da apostila).

Apostila: aula 2.2 · www.e3maker.com.br
