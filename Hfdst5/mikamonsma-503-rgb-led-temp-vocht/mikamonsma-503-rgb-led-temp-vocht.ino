#include <DHT.h>
#include <DHT_U.h>

  // Define the pins for the LED and the button
  #define LED_R 9 
  #define LED_G 10
  #define LED_B 11
  #define LMPIN A2

  // Define the type of sensor and the pin for the sensor
  #define DHTTYPE DHT11
  #define DHTPIN 4

  // Define the object for the sensor
  DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the sensor
  dht.begin();

  // Initialize the serial communication
  Serial.begin(9600);

  // Set the pins for the LED as outputs
  pinMode(LED_R, OUTPUT) ;
  pinMode(LED_G, OUTPUT) ;
  pinMode(LED_B, OUTPUT) ;

}

void loop() {
  // Read the temperature from the sensor
  // Use float to store the temperature making sure it's a decimal
  float temperatuurtje = dht.readTemperature();

  // If the temperature is not a number, print an error message
  if(isnan(temperatuurtje)) {
    Serial.println("Failed bozo");
    return;
  }

  // Print the temperature
  Serial.println(String(temperatuurtje) + " graden C");

  // If the temperature is less than 15, turn on the red LED
  if (temperatuurtje < 15) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 255);
    }
  // If the temperature is between 15 and 23, turn on the green LED
  else if (temperatuurtje >= 15 && temperatuurtje < 23) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 0);    
  }
  // If the temperature is greater than 23, turn on the blue LED
  else {
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);    
  }

  // Wait 2 seconds before reading the temperature again
  delay(2000);
}
