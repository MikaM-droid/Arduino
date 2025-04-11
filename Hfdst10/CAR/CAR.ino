// Arduino Car ----------------------------------------------------------------------------------

#include <SoftwareSerial.h>

#define ENA 3
#define IN1 4
#define IN2 5

#define ENB 10
#define IN3 9
#define IN4 8

#define BT_RX 2  // Arduino RX connects to Bluetooth TX
#define BT_TX 7  // Arduino TX connects to Bluetooth RX

#define PIEP 12

SoftwareSerial BT(BT_RX, BT_TX);

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define STOP 'X'
#define BEEP 'Y'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

#define SPEED 'V' 

int currentSpeed = 150;  // Default speed
int minSpeed = 80;       // Minimum speed
int maxSpeed = 255;      // Maximum speed 

void setup() {
  // put your setup code here, to run once:
  pinMode (ENA, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);

  pinMode (ENB, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode(PIEP, OUTPUT);
  digitalWrite(PIEP, HIGH);
  
  BT.begin(9600);  // Initialize Bluetooth module
  Serial.begin(9600);  // Debugging via Serial Monitor

  Serial.println("Arduino Bluetooth Car Ready!");

  delay(100);
}

// Moving-----------------------------------------------------------------------------------------
// Using int speed so the speed can be adjust in the loop as desired.

void forward(int speed){
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Moving forward, speed: ");
  Serial.println(speed);
}

void backward(int speed){
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.print("Moving backwards, speed: ");
  Serial.println(speed);
}

// Turning---------------------------------------------------------------------------------------

void left(int speed){
  analogWrite(ENA, speed / 2); // Reduce left motor speed :)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Turning left, speed: ");
  Serial.println(speed);
}

void right(int speed){
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed / 2); // Reduce right motor speed :)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Turning right, speed: ");
  Serial.println(speed);
}

// Stopping----------------------------------------------------------------------------------------

void stop(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  Serial.println("Stopped");
}

// Beep Beep---------------------------------------------------------------------------------------

void beep() {
  Serial.println("Beep!");
  digitalWrite(PIEP, LOW);  // Turn buzzer ON (if active LOW)
  delay(100);
  digitalWrite(PIEP, HIGH); // Turn buzzer OFF
  delay(100); // Prevents multiple beeps from a single button press
}

// Handling speed-----------------------------------------------------------------------------------

void processSpeedData() {
  Serial.println("Speed command detected!");
  
  // Wait a bit for the data to arrive
  delay(50);
  
  // For Bluetooth app that sends speed as next byte after 'V'
  if (BT.available()) {
    int speedByte = BT.read();
    Serial.print("Raw speed data: ");
    Serial.print(speedByte);
    Serial.print(" (");
    Serial.write(speedByte);
    Serial.println(")");
    
    // Method 1: If it sends 0-9 as ASCII characters '0' to '9'
    if (speedByte >= '0' && speedByte <= '9') {
      int speedValue = speedByte - '0';  // Convert ASCII to number
      setSpeedFromValue(speedValue);
      return;
    }
    
    // Method 2: If it sends digit 1-10 as its actual value (not ASCII)
    if (speedByte >= 1 && speedByte <= 10) {
      setSpeedFromValue(speedByte);
      return;
    }
    
    // Method 3: If it sends values 0-255 directly
    if (speedByte >= 0 && speedByte <= 255) {
      currentSpeed = constrain(speedByte, minSpeed, maxSpeed);
      Serial.print("Direct speed set to: ");
      Serial.println(currentSpeed);
      return;
    }
  }
}

void setSpeedFromValue(int value) {
  // Map a 0-10 value to our speed range
  int speedValue = map(value, 0, 10, minSpeed, maxSpeed);
  currentSpeed = speedValue;
  Serial.print("Mapped speed value ");
  Serial.print(value);
  Serial.print(" to motor speed: ");
  Serial.println(currentSpeed);
}


// Execute Commands --------------------------------------------------------------------------------

void executeCommand(char command) {
  Serial.print("Command received: "); // Debugging
  Serial.println(command);

  switch (command) {
    case FORWARD: 
      forward(currentSpeed); 
      break;
    case BACKWARD: 
      backward(currentSpeed); 
      break;
    case LEFT: 
      left(currentSpeed); 
      break;
    case RIGHT: 
      right(currentSpeed); 
      break;
    case STOP: 
      stop(); 
      break;
    case BEEP: 
      beep(); 
      break;
    case SPEED:
      processSpeedData();
      break;
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9':
      // Handle direct speed digits (some apps might send digits directly)
      int speedValue = command - '0';  // Convert ASCII to integer
      setSpeedFromValue(speedValue);
      break;
    default:
      // Print unknown commands for debugging
      Serial.print("Unknown command: ");
      Serial.write(command);
      Serial.print(" (");
      Serial.print((int)command);
      Serial.println(")");
      break;
  }
}


// Main Loop ---------------------------------------------------------------------------------------

void loop() {
  // Process incoming Bluetooth data
  while (BT.available()) {
    char command = BT.read();
    
    // Debug output for every character received
    Serial.print("Received: ");
    Serial.write(command);
    Serial.print(" (");
    Serial.print((int)command);
    Serial.println(")");
    
    // Execute the command
    executeCommand(command);
    
    // Small delay to let more data arrive if needed
    delay(10);
  }
}
