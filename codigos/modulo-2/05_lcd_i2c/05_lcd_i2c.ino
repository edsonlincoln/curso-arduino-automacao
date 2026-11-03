// Aula 2.2 — DHT22 + display LCD 16x2 I2C (Kitnet Inteligente E3Maker)
// Bibliotecas: "DHT sensor library", "Adafruit Unified Sensor", "LiquidCrystal I2C" (Frank de Brabander)
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PINO_DHT 2
#define TIPO_DHT DHT22

DHT dht(PINO_DHT, TIPO_DHT);
LiquidCrystal_I2C lcd(0x27, 16, 2);   // se a tela ficar vazia, troque 0x27 por 0x3F

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Kitnet 01");
  lcd.setCursor(0, 1); lcd.print("Iniciando...");
}

void loop() {
  delay(2500);
  float u = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0, 1);
  if (isnan(u) || isnan(t)) {
    lcd.print("Erro no sensor  ");
    return;
  }
  lcd.print(t, 1); lcd.print((char)223); lcd.print("C  ");   // (char)223 = símbolo de grau
  lcd.print(u, 0); lcd.print("%     ");                      // espaços apagam sobras
}
