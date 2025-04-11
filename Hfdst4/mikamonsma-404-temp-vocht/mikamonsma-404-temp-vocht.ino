 // Temperature and humidity sensor
#include <DHT.h>
#include <DHT_U.h>

  #define DHTTYPE DHT11 // Defines the type of sensor which is DHT11
  #define DHTPIN 4 // Defines the pin number of the sensor which is 4

  DHT dht = DHT(DHTPIN, DHTTYPE); // DHT is the object of the DHT sensor if we want 
  // to use the DH

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  dht.begin(); // Initializes the DHT sensor to start reading the data

  Serial.println("The DHT has started!");

}

void loop() {

  delay(2000); // Waits 2 seconds before reading the data again

  float h = dht.readHumidity(); // Reads the humidity data from the sensor

  float t = dht.readTemperature(); // Reads the temperature data from the sensor

  float f = dht.readTemperature(true); // Reads the temperature data from the sensor in Fahrenheit

  if (isnan(h) || isnan(t) || isnan(f)) { // Checks if the data is valid (''Is not a number'')
    Serial.println(F("Failed to read from DHT sensor!")); // Prints the error message if the data is invalid
    return; // Exits the function if the data is invalid making sure  the programm doesn't continue
  }

  Serial.print(F("Humidity: ")); // Prints the humidity data
  Serial.print(h);
  Serial.print(F("%  Temperature: ")); // Prints the temperature data
  Serial.print(t);
  Serial.print(F("°C ")); // Prints the temperature data
  Serial.println(f);

}
