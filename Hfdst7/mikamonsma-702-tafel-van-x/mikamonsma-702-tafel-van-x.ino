void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Voer een geheel getal in groter dan 1: ");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {            //checks for available data
    int input = Serial.parseInt();         //Reads input as string and turns it into an int


    if (input > 1) {
      Serial.println("De tafel van " + String(input) + " is:");   //Checks if input value is above 1

      for (int i = 1; i <= 10; i++) {       //The calculation part
        int result = input * i;
        Serial.println(String(input) + " x " + String(i) + " = " + String(result));
      }

      Serial.println("Berekening voltooid. Voer een nieuw getal in:");   //Let's user know the calculation is complete
    }

    delay(500);
  }
  }
