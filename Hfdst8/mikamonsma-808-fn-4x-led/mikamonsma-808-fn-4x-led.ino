// Define the pins of the LEDs
#define LED_R 9
#define LED_G 10
#define LED_B 11

//---------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
    pinMode(LED_R, OUTPUT) ;
    pinMode(LED_G, OUTPUT) ;
    pinMode(LED_B, OUTPUT) ;
}

//---------------------------------------------------------------------------------------------------

void loop() {
  // Arrays storing color names and corresponding RGB values
  String names[] = {"DodgerBlue", "Gold", "Lime", "Red", "Purple"};
  int rgb_rood[] = {30, 255, 0, 255, 128};
  int rgb_groen[] = {144, 215, 255, 0, 0};
  int rgb_blauw[] = {255, 0, 0, 0, 128};

  int amountColor = sizeof(names) / sizeof(names[0]); // Calculate the amount of colors

  // Loop through all color names and display them on the RGB LED
  for (int i = 0; i < amountColor; i++) {
    rgb_led(names[i], rgb_rood[i], rgb_groen[i], rgb_blauw[i]); // Set the RGB LED to the current color
    delay(2500);
  }
}

//---------------------------------------------------------------------------------------------------

void rgb_led(String naam, byte rgb_red, byte rgb_groen, byte rgb_blauw) {
  analogWrite(LED_R, rgb_red);
  analogWrite(LED_G, rgb_groen);
  analogWrite(LED_B, rgb_blauw);

  // Display the color name and corresponding RGB values on the serial monitor
  Serial.print("Color: " + naam );
  Serial.print(" | Rood: ");
  Serial.print(rgb_red);
  Serial.print(", Groen: ");
  Serial.print(rgb_groen);
  Serial.print(", Blauw: ");
  Serial.println(rgb_blauw);
}