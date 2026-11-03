// Aula 2.3 — Velocidade do cooler 12 V com MOSFET e PWM (Kitnet Inteligente E3Maker)
// Potenciômetro no A1 controla a velocidade; MOSFET (IRLZ44N ou módulo) no pino 9.
const int PINO_POT = A1;   // cursor do potenciômetro
const int PINO_FAN = 9;    // pino PWM ligado ao gate do MOSFET

void setup() {
  pinMode(PINO_FAN, OUTPUT);
  analogWrite(PINO_FAN, 0);     // começa parado
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(PINO_POT);          // 0 a 1023
  int pwm     = map(leitura, 0, 1023, 0, 255);  // converte para 0 a 255
  analogWrite(PINO_FAN, pwm);

  Serial.print("PWM: "); Serial.print(pwm);
  Serial.print("  (");   Serial.print(pwm * 100 / 255); Serial.println(" %)");
  delay(200);
}
