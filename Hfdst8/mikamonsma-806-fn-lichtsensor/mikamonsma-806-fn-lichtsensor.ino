// Define the pin of the light sensor
#define PIN A1

//---------------------------------------------------------------------------------------------------

void setup() {
  pinMode(PIN, INPUT);
    Serial.begin(9600);
  }

//---------------------------------------------------------------------------------------------------

void loop() {
  Serial.println(
    "Waarde is heel misschien " + String(getLichtje())
  );
  delay(1200);
}

//---------------------------------------------------------------------------------------------------

// Function to get the value of the light sensor
int getLichtje(){
  return analogRead(PIN);
}
