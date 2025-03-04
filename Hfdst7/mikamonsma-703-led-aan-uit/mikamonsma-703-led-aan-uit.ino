#define NUM_LEDS 4 // amount of leds
int ledPins[NUM_LEDS] = {13, 12, 11, 10}; // array with the led pins
int pause = 60;

void setup() {
  //put every LED-pin as an OUTPUT
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);  // turns current LED on
    delay(pause);                  // waits said time
    digitalWrite(ledPins[i], HIGH); // turns current LED off
  }
}
