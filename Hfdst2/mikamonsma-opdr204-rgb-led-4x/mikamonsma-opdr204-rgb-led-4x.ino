#define LED_R 9
#define LED_G 10
#define LED_B 11
int pause = 400;

void setup() {
  // put your setup code here, to run once:
    pinMode(LED_R, OUTPUT) ;
    pinMode(LED_G, OUTPUT) ;
    pinMode(LED_B, OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_R, 0);
  digitalWrite(LED_R, 255);
  delay(pause);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 0);
  digitalWrite(LED_G, 255);
  delay(pause);
  digitalWrite(LED_G, 0);
  digitalWrite(LED_B, 0);
  digitalWrite(LED_B, 255);
  delay(pause);
  digitalWrite(LED_B, 0);
  
}
