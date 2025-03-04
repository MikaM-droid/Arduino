#define LED_R 9
#define LED_G 10
#define LED_B 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

    pinMode(LED_R, OUTPUT) ;
    pinMode(LED_G, OUTPUT) ;
    pinMode(LED_B, OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  // Arrays for names and rgb values
  String names[] = {"DodgerBlue", "Gold", "Lime", "Red", "Purple"};
  int rgb_rood[] = {30, 255, 0, 255, 128};
  int rgb_groen[] = {144, 215, 255, 0, 0};
  int rgb_blauw[] = {255, 0, 0, 0, 128};

  int amountColor = sizeof(names) / sizeof(names[0]); //calculates the amount of colors

  //makes sure it runs through all the colors
  for (int i = 0; i < amountColor; i++) {
    rgb_led(names[i], rgb_rood[i], rgb_groen[i], rgb_blauw[i]); //puts LED on color
    delay(2500);
  }
}

void rgb_led(String naam, byte rgb_red, byte rgb_groen, byte rgb_blauw) {
  analogWrite(LED_R, rgb_red);
  analogWrite(LED_G, rgb_groen);
  analogWrite(LED_B, rgb_blauw);

  // Shows color name on serial monitor + numbers used for the color
  Serial.print("Color: " + naam );
  Serial.print(" | Rood: ");
  Serial.print(rgb_red);
  Serial.print(", Groen: ");
  Serial.print(rgb_groen);
  Serial.print(", Blauw: ");
  Serial.println(rgb_blauw);
}