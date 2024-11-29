const byte LED_R = 9;
const byte LED_G = 10;
const byte LED_B = 11;
const byte analogInput = A1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int val = analogRead(analogInput);
  
  int newVal = map (val, 0, 1023, 0, 50);


  analogWrite(LED_R, random(0, 10));
  analogWrite(LED_G, random(0, 10));
  analogWrite(LED_B, random(0, 10));

  if (newVal > 30) {
    analogWrite(random(9, 12), 255);
  }

  Serial.println(newVal);

  delay(1000);
}