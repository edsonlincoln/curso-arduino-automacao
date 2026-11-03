// Aula 2.1 — Lendo temperatura e umidade com o DHT22 (Kitnet Inteligente E3Maker)
// Bibliotecas: "DHT sensor library" + "Adafruit Unified Sensor" (Adafruit)
#include <DHT.h>

#define PINO_DHT 2        // pino de dados do DHT22
#define TIPO_DHT DHT22    // troque por DHT11 se for o azul pequeno

DHT dht(PINO_DHT, TIPO_DHT);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Lendo o DHT22...");
}

void loop() {
  delay(2500);                          // o DHT22 só mede a cada 2 s (no mínimo)
  float umidade     = dht.readHumidity();
  float temperatura = dht.readTemperature();   // em °C

  if (isnan(umidade) || isnan(temperatura)) {  // isnan = "não é número" = falhou
    Serial.println("Falha na leitura: confira os fios do DHT22");
    return;
  }
  Serial.print("Temperatura: "); Serial.print(temperatura, 1); Serial.print(" C   ");
  Serial.print("Umidade: ");     Serial.print(umidade, 0);     Serial.println(" %");
}
