const byte LED_R = 9;
const byte LED_G = 10;
const byte LED_B = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(LED_R, random(0, 255));
  analogWrite(LED_G, random(0, 255));
  analogWrite(LED_B, random(0, 255));

  delay(500);
}
