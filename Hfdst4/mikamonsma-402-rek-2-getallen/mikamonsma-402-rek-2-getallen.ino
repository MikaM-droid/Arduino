void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  int getal1 = 5;
    int getal2 = 8;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

a = getal1 + getal2;
  Serial.print(a);

b = getal1 * getal2;
  Serial.print(b);

c = getal1 / getal2;
  Serial.print(c);

d = getal1 - getal2;
  Serial.print(d);


}

void loop() {
  // put your main code here, to run repeatedly:

}
