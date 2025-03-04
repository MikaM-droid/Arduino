#define PIN A1

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(
    "Waarde is heel misschien " + String(getLichtje())
  );

  delay(1200);
}

int getLichtje(){
  return analogRead(PIN);
}
