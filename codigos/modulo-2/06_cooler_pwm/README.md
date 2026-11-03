# 2.3 — Cooler 12 V com MOSFET e PWM
**Objetivo:** Controlar a velocidade de um cooler 12 V com potenciômetro.

**Materiais:** Arduino UNO, MOSFET IRLZ44N (ou módulo MOSFET), resistores 100 Ω e 10 kΩ, diodo 1N4007, cooler 12 V, fonte 12 V, potenciômetro 10 kΩ.

| Pino do Arduino | Ligação |
|---|---|
| A1 | cursor do potenciômetro (pontas em 5V e GND) |
| 9 | 100 Ω → Gate do MOSFET (10 kΩ do Gate ao GND) |
| GND | Source do MOSFET + GND da fonte 12 V (GND comum) |

+12 V → + do cooler · − do cooler → Drain · diodo 1N4007 em paralelo com o cooler (faixa no +12 V).

⚠️ Só 5–12 V CC. GND comum entre a fonte e o Arduino quando houver MOSFET.

**Bibliotecas:** nenhuma

Apostila: aula 2.3 · www.e3maker.com.br
