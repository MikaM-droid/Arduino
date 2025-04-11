void setup() {
  Serial.begin(9600);
  Serial.println("Voer een geheel getal in groter dan 1: ");
}

void loop() {

  // Check if any data has been sent to the serial port
  if (Serial.available() > 0) {
    // Read the input as an int
    int input = Serial.parseInt();

    // Check if the input is greater than 1
    if (input > 1) {
      // Print the table of the input
      Serial.println("De tafel van " + String(input) + " is:");

      // Loop through the numbers 1 to 10
      for (int i = 1; i <= 10; i++) {
        // Calculate the result of the multiplication and store the result of the multiplication in the variable result
        int result = input * i;
        // Print the result of the multiplication
        Serial.println(String(input) + " x " + String(i) + " = " + String(result));
      }

      // Print a message to the user
      Serial.println("Berekening voltooid. Voer een nieuw getal in:");
    }

    delay(500);
  }
  }
