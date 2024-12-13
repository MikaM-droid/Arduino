#define LED_BLUE 13
#define LED_RED 12

#define BTN_BLUE 2
#define BTN_RED 3

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(LED_BLUE, OUTPUT);
  pinMode(BTN_BLUE, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(BTN_RED, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 Serial.println(String(!digitalRead(BTN_BLUE)) + " - " + String(!digitalRead(BTN_RED)));

 delay(200);

 int STATE_RED = digitalRead(BTN_RED);
 int STATE_BLUE = digitalRead(BTN_BLUE);

 if (STATE_BLUE == LOW) {
  digitalWrite(LED_BLUE, HIGH);
  Serial.println("Blue is on");
 } else {
  delay(250);
  digitalWrite(LED_BLUE, LOW);
 }

  if (STATE_RED == LOW) {
  digitalWrite(LED_RED, HIGH);
  Serial.println("Red is on");
 } else {
  delay(250);
  digitalWrite(LED_RED, LOW);
 }

}
