#include <DHT.h>
#include <DHT_U.h>

  #define LED_R 9
  #define LED_G 10
  #define LED_B 11
  #define LMPIN A2

  #define DHTTYPE DHT11
  #define DHTPIN 4

  DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();

  Serial.begin(9600);

  pinMode(LED_R, OUTPUT) ;
  pinMode(LED_G, OUTPUT) ;
  pinMode(LED_B, OUTPUT) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  float temperatuurtje = dht.readTemperature();

  if(isnan(temperatuurtje)) {
    Serial.println("Failed bozo");
    return;
  }

  Serial.println(String(temperatuurtje) + " graden C");

  if (temperatuurtje < 15) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 255);
    }
  else if (temperatuurtje >= 15 && temperatuurtje < 23) {
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 0);    
  }
  else {
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);    
  }

  delay(2000);
}
