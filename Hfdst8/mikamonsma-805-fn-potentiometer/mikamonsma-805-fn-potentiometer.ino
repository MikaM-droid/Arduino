// Define the pin of the potentiometer
#define PIN A0

//---------------------------------------------------------------------------------------------------

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(9600);
}

//---------------------------------------------------------------------------------------------------

void loop() {
  // Print the value of the potentiometer
  Serial.println(
    "Waarde is heel misschien " + String(getWaarde())
  );

  delay(1200);
}

//---------------------------------------------------------------------------------------------------

// Function to get the value of the potentiometer
int getWaarde(){
  // Return the value of the potentiometer to the main loop
  // This returns a value between 0 and 1023
  return analogRead(PIN); 
}