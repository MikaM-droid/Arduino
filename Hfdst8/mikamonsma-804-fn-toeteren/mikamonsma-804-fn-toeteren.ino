#define BUZZ 5

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZ, OUTPUT);

  Serial.begin(9600);

  buzzo(200);
}

void loop() {
  // put your main code here, to run repeatedly:
 
}

void buzzo(int time) {
  digitalWrite(BUZZ, HIGH);
  delay(time);
  digitalWrite(BUZZ, LOW);

} 
