// Projeto 1 — Luz de corredor automática (Kitnet Inteligente E3Maker)
const int PINO_PIR  = 2;    // saída do sensor de presença
const int PINO_LDR  = A0;   // sensor de luz (divisor com 10 kΩ)
const int PINO_RELE = 7;    // entrada do módulo relé
const int LIMITE_ESCURO = 700;  // acima disso = escuro (ajuste no passo 11)

void setup() {
  pinMode(PINO_PIR, INPUT);
  pinMode(PINO_RELE, OUTPUT);
  digitalWrite(PINO_RELE, HIGH);   // relé ativo em LOW: começa desligado
  Serial.begin(9600);              // para ver os valores no Monitor Serial
}

void loop() {
  int  luz      = analogRead(PINO_LDR);            // baixo = claro, alto = escuro
  bool presenca = digitalRead(PINO_PIR) == HIGH;   // true = tem gente
  bool escuro   = luz > LIMITE_ESCURO;             // true = está escuro

  Serial.print("Luz: ");      Serial.print(luz);
  Serial.print("  Presenca: "); Serial.println(presenca);

  if (presenca && escuro) {
    digitalWrite(PINO_RELE, LOW);    // liga a luz
  } else {
    digitalWrite(PINO_RELE, HIGH);   // desliga a luz
  }
  delay(200);
}
