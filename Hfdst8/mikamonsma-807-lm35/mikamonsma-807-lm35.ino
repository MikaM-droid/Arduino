// Define the pin of the LM35 temperature sensor
#define PIN A2

//---------------------------------------------------------------------------------------------------

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(9600);
}

//---------------------------------------------------------------------------------------------------

void loop() {
  Serial.println(
    "Waarde is heel misschien " + String(getTemp())
  );
  delay(1200);
}

//---------------------------------------------------------------------------------------------------

float getTemp(){
  // Initialize the variable sensorTempDa
  float sensorTempDa = 0; 

  // Loop through the 3 readings
  for(int i = 0; i < 3; i++){
    // Read the temperature from the sensor
    sensorTempDa += analogRead(PIN); // using += to add the value to the variable
    // Print the value of the temperature
    Serial.println("Waarde" + String(i+1));
    delay(500);
  }

  return sensorTempDa / 3; // dividing by 3 to get the average
}