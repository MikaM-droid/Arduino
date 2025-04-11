// Button and LED
// Define the pins for the LED and the button
#define LED_BLUE 13
#define LED_RED 12

// Define the pins for the button
#define BTN_BLUE 2
#define BTN_RED 3

void setup() {

  Serial.begin(9600);

  // Sets the LED_BLUE pin as an output
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BTN_BLUE, INPUT);

  // Sets the LED_RED pin as an output
  pinMode(LED_RED, OUTPUT);
  pinMode(BTN_RED, INPUT); 
}

void loop() {

  // Prints the state of the buttons which is HIGH or LOW which means that the button is pressed or not
  Serial.println(String(!digitalRead(BTN_BLUE)) + " - " + String(!digitalRead(BTN_RED)));

 delay(200);

 int STATE_RED = digitalRead(BTN_RED);
 int STATE_BLUE = digitalRead(BTN_BLUE);

  // If the button is pressed, the LED is on
  if (STATE_BLUE == LOW) {
    digitalWrite(LED_BLUE, HIGH);
    Serial.println("Blue is on");
    // If the button is not pressed, the LED is off
    } else {
      delay(250);
      digitalWrite(LED_BLUE, LOW); // Digitalwrite is used to set the state of the LED which is HIGH or LOW
    }

  // If the button is pressed, the LED is on
  if (STATE_RED == LOW) {
    digitalWrite(LED_RED, HIGH);
    Serial.println("Red is on");
    // If the button is not pressed, the LED is off
    } else {
      delay(250);
      digitalWrite(LED_RED, LOW);
    }

}
