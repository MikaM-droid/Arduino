#define LED1_D_PIN    13
#define LED2_D_PIN    12
#define LED3_D_PIN    11
#define LED4_D_PIN    10
int pause = 80;

void setup() {
  // put your setup code here, to run once:
    pinMode(LED1_D_PIN, OUTPUT) ;
    pinMode(LED2_D_PIN, OUTPUT) ;
    pinMode(LED3_D_PIN, OUTPUT) ;
    pinMode(LED4_D_PIN, OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1_D_PIN, LOW);
  delay(pause);
  digitalWrite(LED1_D_PIN, HIGH);
  digitalWrite(LED2_D_PIN, LOW);
  delay(pause);
  digitalWrite(LED2_D_PIN, HIGH);
  digitalWrite(LED3_D_PIN, LOW);
  delay(pause);
  digitalWrite(LED3_D_PIN, HIGH);
  digitalWrite(LED4_D_PIN, LOW);
  delay(pause);
  digitalWrite(LED4_D_PIN, HIGH);
}
