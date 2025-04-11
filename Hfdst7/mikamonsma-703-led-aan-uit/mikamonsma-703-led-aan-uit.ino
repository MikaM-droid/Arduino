// Define the number of LEDs
#define NUM_LEDS 4
// Define the pins of the LEDs
int ledPins[NUM_LEDS] = {13, 12, 11, 10};
// Define the pause time
int pause = 60;

void setup() {
  // Put every LED-pin as an OUTPUT
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Loop through the LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);  // Turns current LED on
    delay(pause);                  // Wait for the defined pause time before turning off the LED
    digitalWrite(ledPins[i], HIGH); // Turns current LED off
  }
}
