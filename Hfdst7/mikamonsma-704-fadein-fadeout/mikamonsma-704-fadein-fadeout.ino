#define NUM_LEDS 4 // amount of leds
int ledPins[NUM_LEDS] = {13, 12, 11, 10}; // array with the led pins

void setup() {
  // put your setup code here, to run once:
 for (int i = 0; i < NUM_LEDS; i++) {
 pinMode(ledPins[i], OUTPUT); }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int brightness = 0; brightness <= 255; brightness++) {    //let's the LEDs increase in brightness
    for (int i = 0; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], brightness);
    }
    delay (20); //fade timer
  }
  delay (1000); //waits on max brightness


  for (int brightness = 255; brightness >= 0; brightness--) {    //let's the LEDs decrease in brightness
    for (int i = 0; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], brightness);
    }
    delay(10);

  delay(1000);
}
}
