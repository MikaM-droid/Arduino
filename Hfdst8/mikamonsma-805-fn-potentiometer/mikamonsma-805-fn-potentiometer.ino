#define PIN A0

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(
    "Waarde is heel misschien " + String(getWaarde())
  );

  delay(1200);
}

int getWaarde(){
  return analogRead(PIN);
}