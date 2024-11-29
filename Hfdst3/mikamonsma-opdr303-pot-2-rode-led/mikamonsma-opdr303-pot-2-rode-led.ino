const byte LED1 = 10;
const byte LED2 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sensorValue = analogRead(A0);

  int newVal = map(sensorValue, 0, 1023, 0, 255);

  analogWrite(LED1, random(0, 255));
  analogWrite(LED2, random(0, 255));

  Serial.println(newVal);
  delay(1000);
}