void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Wat is je naam ? ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String naam = Serial.readString();
    Serial.print("Hallo " + naam );
    Serial.println("Wat is je naam ? ");
  }
}
