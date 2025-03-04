#define PIN A2

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(
    "Waarde is heel misschien " + String(getTemp())
  );

  delay(1200);
}

float getTemp(){
  float sensorTempDa = 0; 

  for(int i = 0; i < 3; i++){
    sensorTempDa = analogRead(PIN);
    Serial.println("Waarde" + String(i+1));
    delay(500);
  }

    return analogRead(PIN);

}