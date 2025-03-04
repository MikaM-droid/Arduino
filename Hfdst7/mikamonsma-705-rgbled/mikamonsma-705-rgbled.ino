#define LED_R_PIN 9
#define LED_G_PIN 11
#define LED_B_PIN 10

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void loop() {
  int redValue = getValidRGBValue("Red");
  int greenValue = getValidRGBValue("Green");
  int blueValue = getValidRGBValue("Blue");

  //sets LED on the given value
  setRGBColor(redValue, greenValue, blueValue);

  Serial.println("Look at the LED");

  while (Serial.available() == 0) {
    //Waits for input before a new color will be questioned
  }
}

//function to get a valid RGB number ------------------------------------------------
int getValidRGBValue(String color) {
  int value = -1; //Makes sure the loop runs atleast once so it asks for a value

  while (value < 0 || value > 255) {
    Serial.println("Fill in a number for the color " + color + "   (0-255)");

    while (Serial.available() == 0) {
      //Wait for the input
    }

    value = Serial.parseInt();

    //Empty buffer to prevent issues
    while (Serial.available() > 0) {
      Serial.read();
    }

    if (value < 0 || value > 255) {
      Serial.println("Invalid, you're stupid. Read the question again.");
    }
  }
  return value;
}

//Function to set the RGB lights on given value ---------------------------------------
void setRGBColor(int red, int green, int blue) {
  analogWrite(LED_R_PIN, red);
  analogWrite(LED_G_PIN, green);
  analogWrite(LED_B_PIN, blue);
}

