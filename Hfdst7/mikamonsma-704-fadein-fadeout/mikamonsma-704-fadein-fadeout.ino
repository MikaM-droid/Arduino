// Define the number of LEDs
#define NUM_LEDS 4
// Define the pins of the LEDs
int ledPins[NUM_LEDS] = {13, 12, 11, 10};

void setup() {
  // Put every LED-pin as an OUTPUT
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Loop through the LEDs
  for (int brightness = 0; brightness <= 255; brightness++) {
    // Loop through the LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], brightness);
    }
    delay (20); // Wait for 20 milliseconds to fade in
  }
  delay (1000); // Wait for 1 second to reach max brightness

  // Decrease the brightness of the LEDs
  for (int brightness = 255; brightness >= 0; brightness--) {
    // Loop through the LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], brightness);
    }
    delay(10); // Wait for 10 milliseconds to fade out
  }
  delay(1000); // Wait for 1 second to reach min brightness
}

