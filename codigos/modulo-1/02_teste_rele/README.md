# 1.3 — Teste do módulo relé com fita LED 12 V
**Objetivo:** acionar uma fita LED 12 V pelo módulo relé (liga 2 s, desliga 2 s).

**Materiais:** Arduino UNO, módulo relé 1 canal 5 V (ativo em LOW), fonte 12 V, fita LED 12 V, jumpers.

| Ligação | Para |
|---|---|
| 5V do Arduino | VCC do relé |
| GND do Arduino | GND do relé |
| Pino 7 | IN do relé |
| +12 V da fonte | COM do relé |
| NA do relé | + da fita LED |
| − da fita LED | − da fonte |

⚠️ Só 5–12 V. Nunca ligue 127/220 V sem profissional habilitado (NR-10).
**Bibliotecas:** nenhuma.
Apostila: aula 1.3 · www.e3maker.com.br
