// RGB LED and 3 buttons
// Define the pins for the buttons
#define BTN1 1
#define BTN2 2
#define BTN3 3

void setup() {
  Serial.begin(9600);

  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
}

void loop() {

  delay(1000);

  // If the button is pressed, print a random number between 0 and 200
  if (digitalRead(BTN1) == LOW) {
    Serial.println(random(0, 200));
  // If the button is pressed, print a random number between 200 and 400  
  } else if (digitalRead(BTN2) == LOW) {
    Serial.println(random(200, 400));
  // If the button is pressed, print a random number between 400 and 600
  } else if (digitalRead(BTN3) == LOW) {
    Serial.println(random(400, 600));
  }

}
