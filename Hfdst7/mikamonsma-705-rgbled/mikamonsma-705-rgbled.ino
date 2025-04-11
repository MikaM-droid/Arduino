#define LED_R_PIN 9
#define LED_G_PIN 11
#define LED_B_PIN 10

//---------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

//---------------------------------------------------------------------------------------------------

void loop() {
  // Get a valid RGB value
  int redValue = getValidRGBValue("Red");
  int greenValue = getValidRGBValue("Green");
  int blueValue = getValidRGBValue("Blue");

  // Set the LED on the given value
  setRGBColor(redValue, greenValue, blueValue);

  Serial.println("Look at the LED");

  // Wait for input before a new color will be questioned
  while (Serial.available() == 0) {
  }
}

//function to get a valid RGB number ----------------------------------------------------------------

int getValidRGBValue(String color) {
  int value = -1; //Ensures that the loop runs at least once to prompt for a value

  // Loop until a valid RGB value is entered
  while (value < 0 || value > 255) {
    Serial.println("Fill in a number for the color " + color + "   (0-255)");

    // Wait for the input
    while (Serial.available() == 0) {
    }

    // Read the input as an int
    value = Serial.parseInt();

    // Empty buffer to prevent issues
    while (Serial.available() > 0) {
      Serial.read();
    }

    // Check if the value is valid
    if (value < 0 || value > 255) {
      Serial.println("Invalid, you're stupid. Read the question again.");
    }
  }
  return value;
}

//Function to set the RGB lights on given value -------------------------------------------------------

// Using the parameters red, green and blue, the function sets the RGB lights on the given value
void setRGBColor(int red, int green, int blue) {
  // Set the RGB lights on the given value
  analogWrite(LED_R_PIN, red);
  analogWrite(LED_G_PIN, green);
  analogWrite(LED_B_PIN, blue);
}

