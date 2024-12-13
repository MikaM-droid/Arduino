#include <DHT.h>
#include <DHT_U.h>

  #define DHTTYPE DHT11
  #define DHTPIN 4

  DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  dht.begin();

  Serial.println("The DHT has started!");

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(f);

}
