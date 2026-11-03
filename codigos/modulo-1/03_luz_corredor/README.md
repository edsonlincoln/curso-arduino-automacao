# 1.4 — Projeto 1: luz de corredor automática
**Objetivo:** acender a fita LED 12 V só quando está escuro E há presença.

**Materiais:** Arduino UNO, sensor PIR HC-SR501, LDR + resistor 10 kΩ (ou módulo LDR), módulo relé 1 canal, fonte 12 V, fita LED 12 V.

| Pino do Arduino | Ligação |
|---|---|
| 2 | OUT do PIR |
| A0 | ponto entre resistor 10 kΩ e LDR (5V → 10 kΩ → A0 → LDR → GND) ou AO do módulo |
| 7 | IN do relé |
| 5V / GND | VCC/GND do PIR, do LDR e do relé |

Lado da carga: +12 V → COM · NA → + fita · − fita → − fonte.

**Ajustes:** espere 30–60 s de aquecimento do PIR; calibre `LIMITE_ESCURO` pelo Monitor Serial (9600); trimpot Tx = tempo, Sx = alcance.
**Bibliotecas:** nenhuma.
Apostila: aula 1.4 · www.e3maker.com.br
