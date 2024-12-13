#define BTN1 1
#define BTN2 2
#define BTN3 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);

  if (analogRead(BTN1) == LOW) {
    Serial.println(random(0, 200));
  }  else if (analogRead(BTN2) == LOW) {
    Serial.println(random(200, 400));
  }  else if (analogRead(BTN3) == LOW) {
    Serial.println(random(400, 600));
  }

}
