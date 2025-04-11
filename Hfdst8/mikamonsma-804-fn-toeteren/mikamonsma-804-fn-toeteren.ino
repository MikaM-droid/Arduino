// Define the pin of the buzzer
#define BUZZ 5 

//---------------------------------------------------------------------------------------------------

void setup() {
  pinMode(BUZZ, OUTPUT);

  Serial.begin(9600);

  buzzo(200); 
  // Call the buzzo function with 200 as a parameter
  // The 200 is used to set the duration of the buzz
}

//---------------------------------------------------------------------------------------------------

// Function to buzz the buzzer for a given time
// int time is used to set the duration of the buzz
void buzzo(int time) {
  digitalWrite(BUZZ, HIGH);
  delay(time);
  digitalWrite(BUZZ, LOW);
} 
