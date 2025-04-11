// String concatenation
void setup() {
  Serial.begin(9600);

  // Generate a random number between 5 and 15 (excl 15)
  int getal1 = random(5, 15);
  int getal2 = random(5, 15);
  int getal3 = random(5, 15);
  int getal4 = random(5, 15);

  Serial.println(getal1);
  Serial.println(getal2);
  Serial.println(getal3);
  Serial.println(getal4);

  Serial.println("---------------------");

  Serial.println("Basic math:");

  Serial.println("Reken operatoren");
  Serial.println("+, -, /, *"); // Addition, Minus, Divide, Multiply

  Serial.println(""); // Empty line

  Serial.println( String(getal1) + " + " + String(getal2) + " == " + String(getal1 + getal2) );
  Serial.println( String(getal3) + " - " + String(getal4) + " == " + String(getal3 - getal4) );

  Serial.println( String(getal1) + " / " + String(getal2) + " == " + String(getal1 / getal2) );
  Serial.println( String(getal3) + " * " + String(getal4) + " == " + String(getal3 * getal4) );

  Serial.println("");

  // Logical operators
  // || is OR, && is AND, ! is NOT
  Serial.println("Vergelijkings- en logische operatoren");
  // Greater than, Greater than or equal to, Less than, Less than or equal to, Equal to, 
  //Not equal to, Greater than or equal to
  Serial.println(">, >=, <, <=, ==, !=, => 1=true, 0=false"); 

  Serial.println("");

  // String makes sure the numbers are printed as strings
  Serial.println( String(getal1) + " > " + String(getal2) + " == " + String(getal1 > getal2) );
  Serial.println( String(getal3) + " >= " + String(getal4) + " == " + String(getal3 >= getal4) );  

  Serial.println( String(getal1) + " > " + String(getal2) + " && " + String(getal3) + " >= " + String(getal4) + " == " + String(getal1 > getal2 && getal3 >= getal4) );
  Serial.println( String(getal1) + " > " + String(getal2) + " || " + String(getal3) + " >= " + String(getal4) + " == " + String(getal1 > getal2 || getal3 >= getal4) );

  Serial.println("");

  Serial.println( String(getal1) + " < " + String(getal2) + " == " + String(getal1 < getal2) );
  Serial.println( String(getal3) + " <= " + String(getal4) + " == " + String(getal3 <= getal4) );  

  Serial.println( String(getal1) + " < " + String(getal2) + " && " + String(getal3) + " <= " + String(getal4) + " == " + String(getal1 < getal2 && getal3 <= getal4) );
  Serial.println( String(getal1) + " < " + String(getal2) + " || " + String(getal3) + " <= " + String(getal4) + " == " + String(getal1 < getal2 || getal3 <= getal4) );  

  Serial.println("");  

  Serial.println( String(getal1) + " == " + String(getal2) + " == " + String(getal1 == getal2) );
  Serial.println( String(getal3) + " != " + String(getal4) + " == " + String(getal3 != getal4) );  

  Serial.println( String(getal1) + " == " + String(getal2) + " && " + String(getal3) + " != " + String(getal4) + " == " + String(getal1 == getal2 && getal3 != getal4) );
  Serial.println( String(getal1) + " == " + String(getal2) + " || " + String(getal3) + " != " + String(getal4) + " == " + String(getal1 == getal2 || getal3 != getal4) );
}

void loop() {
  // put your main code here, to run repeatedly:

}
