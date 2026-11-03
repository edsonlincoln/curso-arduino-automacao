// Projeto 2 — Ventilação inteligente (Kitnet Inteligente E3Maker)
// DHT22 no pino 2 · LCD I2C (A4/A5) · MOSFET do cooler no pino 9 · buzzer no pino 8
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PINO_DHT 2
#define TIPO_DHT DHT22
const int PINO_FAN    = 9;
const int PINO_BUZZER = 8;

// Faixas do projeto real de exaustor da E3Maker (ajuste para o seu ambiente)
const float T_LIGA    = 35.0;  // liga o cooler a partir daqui
const float T_DESLIGA = 33.0;  // só desliga abaixo daqui (histerese de 2 °C)
const float T_MAX     = 45.0;  // daqui para cima: 100 %
const float T_ALARME  = 55.0;  // alarme sonoro
const int   PWM_MIN   = 80;    // menor PWM em que o SEU cooler gira (descubra na aula 2.3)

DHT dht(PINO_DHT, TIPO_DHT);
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool ligado = false;

void setup() {
  pinMode(PINO_FAN, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  analogWrite(PINO_FAN, 0);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Ventilacao K01");
}

void loop() {
  delay(2500);
  float t = dht.readTemperature();
  float u = dht.readHumidity();

  if (isnan(t) || isnan(u)) {          // sensor falhou: por segurança, ventila no máximo
    analogWrite(PINO_FAN, 255);
    lcd.setCursor(0, 1); lcd.print("Erro sensor!    ");
    return;
  }

  // Histerese: liga em T_LIGA, só desliga em T_DESLIGA
  if (!ligado && t >= T_LIGA)    ligado = true;
  if (ligado  && t <= T_DESLIGA) ligado = false;

  int pwm = 0;
  if (ligado) {
    float tLimitada = constrain(t, T_LIGA, T_MAX);
    pwm = PWM_MIN + (tLimitada - T_LIGA) * (255 - PWM_MIN) / (T_MAX - T_LIGA);
  }
  analogWrite(PINO_FAN, pwm);

  if (t >= T_ALARME) digitalWrite(PINO_BUZZER, HIGH);
  else               digitalWrite(PINO_BUZZER, LOW);

  lcd.setCursor(0, 0);
  lcd.print(t, 1); lcd.print((char)223); lcd.print("C "); lcd.print(u, 0); lcd.print("%    ");
  lcd.setCursor(0, 1);
  if (t >= T_ALARME) lcd.print("ALARME! 100%    ");
  else { lcd.print("Fan: "); lcd.print(pwm * 100 / 255); lcd.print("%          "); }
}
