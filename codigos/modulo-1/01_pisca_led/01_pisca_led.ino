// Projeto 0 — Pisca LED (Kitnet Inteligente E3Maker)
const int LED = 13;          // o LED está no pino 13

void setup() {
  pinMode(LED, OUTPUT);      // pino 13 é saída
}

void loop() {
  digitalWrite(LED, HIGH);   // acende
  delay(500);                // espera meio segundo
  digitalWrite(LED, LOW);    // apaga
  delay(500);                // espera meio segundo
}
