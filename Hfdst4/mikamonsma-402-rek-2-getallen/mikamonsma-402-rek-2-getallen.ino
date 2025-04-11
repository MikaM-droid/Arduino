// Void setup runs automatically once, it does this to initialize the settings
void setup() { 

  // Serial monitor defining. Runs at 9600 bits per second
  Serial.begin(9600); 

  // Define variables (arithmetic operations)
  int getal1 = 5;       
    int getal2 = 8;

    // The next few variables are used to store the results of different
    // arithmetic operations
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

  // Addition operation
  a = getal1 + getal2;
  // Print value of the result above
  Serial.println(a);

  // Multiply
  b = getal1 * getal2;
  Serial.println(b);

  // Division
  c = getal1 / getal2;
  Serial.println(c);

  // Subtraction
  d = getal1 - getal2;
  Serial.println(d);
}

void loop() {
  // put your main code here, to run repeatedly:

}
