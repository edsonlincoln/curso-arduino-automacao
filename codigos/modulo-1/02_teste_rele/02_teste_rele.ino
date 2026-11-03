// Teste do relé — liga e desliga a fita LED 12 V
const int RELE = 7;

void setup() {
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, HIGH);   // módulo ativo em LOW: HIGH = desligado
}

void loop() {
  digitalWrite(RELE, LOW);    // liga a fita
  delay(2000);
  digitalWrite(RELE, HIGH);   // desliga a fita
  delay(2000);
}
