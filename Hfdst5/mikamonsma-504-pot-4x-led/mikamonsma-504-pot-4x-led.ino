// Potentiometer and 4 LEDs
// Define the pins for the LED and the potentiometer
#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13

// Define the pin for the potentiometer
#define POT_PIN A0

void setup() {
  // Set the pin for the potentiometer as an input
  pinMode(POT_PIN, INPUT);
  // Set the pins for the LEDs as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  // Read the potentiometer
  // Analogread is used to output Pulse Width Modulation (PWM) values
  // Which can be used to control the brightness of the LEDs
  int knopje = analogRead(POT_PIN);
  delay(500);

  Serial.println(knopje);

  // If the potentiometer is less than 128, turn on all the LEDs
  if (knopje < 128) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

  // If the potentiometer is between 128 and 384, turn on the first LED and turn off the other three
  } else if (knopje > 128 && knopje < 384) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

  // If the potentiometer is between 384 and 640, turn on the first two LEDs and turn off the other two
  } else if (knopje > 384 && knopje < 640) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

  // If the potentiometer is between 640 and 896, turn on the first two LEDs and turn off the other two
  } else if (knopje > 640 && knopje < 896) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);

  // If the potentiometer is greater than 896, turn off all the LEDs
  } else if (knopje > 896) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);  
  }
}
