//---------------------------------------------------
// Arduino car

#include <SoftwareSerial.h>

//---------------------------------------------------
// Pin defining

// Motor control pins
#define ENA 3
#define IN1 4
#define IN2 5

#define ENB 10
#define IN3 9
#define IN4 8

// Bluetooth
#define BT_RX 2
#define BT_TX 7
SoftwareSerial BT(BT_RX, BT_TX);

// Buzzer
#define PIEP 12

// Lijnsensoren
#define LINE_LEFT A0
#define LINE_CENTER A1
#define LINE_RIGHT A2

// Object sensors
#define OBJECT_LEFT A3
#define OBJECT_RIGHT A4

// Ultrasonic
#define TRIG_PIN 6
#define ECHO_PIN 11 // changed from D0 to D11

// Bluetooth Commands
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define STOP 'S'
#define BEEP 'Y'
#define SPEED 'V'

//---------------------------------------------------
// Speed values

int currentSpeed = 150;
int minSpeed = 80;
int maxSpeed = 255;

//---------------------------------------------------
// Pin setup

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PIEP, OUTPUT);
  digitalWrite(PIEP, HIGH);

  pinMode(LINE_LEFT, INPUT);
  pinMode(LINE_CENTER, INPUT);
  pinMode(LINE_RIGHT, INPUT);

  pinMode(OBJECT_LEFT, INPUT);
  pinMode(OBJECT_RIGHT, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino Bluetooth Car Ready!");
  delay(100);
}

//---------------------------------------------------
// Movement functions

void forward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Moving forward, speed: ");
  Serial.println(speed);
}

void backward(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.print("Moving backward, speed: ");
  Serial.println(speed);
}

void left(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Turning left, speed: ");
  Serial.println(speed);
}

void right(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.print("Turning right, speed: ");
  Serial.println(speed);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stopped");
}

void beep() {
  Serial.println("Beep!");
  digitalWrite(PIEP, LOW);
  delay(100);
  digitalWrite(PIEP, HIGH);
  delay(100);
}

//---------------------------------------------------
// Speed control

void processSpeedData() {
  Serial.println("Speed command detected!");
  delay(50);
  if (BT.available()) {
    int speedByte = BT.read();
    Serial.print("Raw speed data: ");
    Serial.print(speedByte);
    Serial.print(" (");
    Serial.write(speedByte);
    Serial.println(")");

    if (speedByte >= '0' && speedByte <= '9') {
      int speedValue = speedByte - '0';
      setSpeedFromValue(speedValue);
      return;
    }

    if (speedByte >= 1 && speedByte <= 10) {
      setSpeedFromValue(speedByte);
      return;
    }

    if (speedByte >= 0 && speedByte <= 255) {
      currentSpeed = constrain(speedByte, minSpeed, maxSpeed);
      Serial.print("Direct speed set to: ");
      Serial.println(currentSpeed);
    }
  }
}

void setSpeedFromValue(int value) {
  int speedValue = map(value, 0, 10, minSpeed, maxSpeed);
  currentSpeed = speedValue;
  Serial.print("Mapped speed value ");
  Serial.print(value);
  Serial.print(" to motor speed: ");
  Serial.println(currentSpeed);
}

//---------------------------------------------------
// Ultrasonic function

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout at 30ms = ~5m
  return duration * 0.034 / 2;
}

//---------------------------------------------------
// Autonomous driving function (Improved)

void autonomousMode() {
  long rawDistance = getDistance();
  long distance = rawDistance;

  if (distance <= 0 || distance > 300) {
    Serial.print("Invalid distance reading: ");
    Serial.println(rawDistance);
    distance = 300;
  }

  bool leftLine = digitalRead(LINE_LEFT);
  bool centerLine = digitalRead(LINE_CENTER);
  bool rightLine = digitalRead(LINE_RIGHT);

  bool objLeft = digitalRead(OBJECT_LEFT);
  bool objRight = digitalRead(OBJECT_RIGHT);

  Serial.println("---- Autonomous Debug Info ----");
  Serial.print("Distance (cm): ");
  Serial.println(distance);

  Serial.print("Line Sensors - Left: ");
  Serial.print(leftLine);
  Serial.print("  Center: ");
  Serial.print(centerLine);
  Serial.print("  Right: ");
  Serial.println(rightLine);

  Serial.print("Object Sensors - Left: ");
  Serial.print(objLeft);
  Serial.print("  Right: ");
  Serial.println(objRight);
  Serial.println("--------------------------------");

  if (distance < 15 || objLeft == LOW || objRight == LOW) {
    Serial.println("⚠️ Obstacle detected! Avoiding...");

    stop();
    delay(400);
    backward(currentSpeed);
    delay(400);

    if (objRight == LOW) {
      Serial.println("Turning left to avoid object on the right.");
      left(currentSpeed);
    } else {
      Serial.println("Turning right to avoid object on the left or center.");
      right(currentSpeed);
    }

    delay(500);
    return;
  }

  if (leftLine == LOW && centerLine == HIGH && rightLine == LOW) {
    Serial.println("Following line - Moving forward.");
    forward(currentSpeed);
  } else if (leftLine == HIGH && centerLine == LOW) {
    Serial.println("Adjusting - Turning left.");
    left(currentSpeed);
  } else if (rightLine == HIGH && centerLine == LOW) {
    Serial.println("Adjusting - Turning right.");
    right(currentSpeed);
  } else {
    Serial.println("⚠️ Line lost - Stopping.");
    stop();
  }
}

//---------------------------------------------------
// Bluetooth command handler

void executeCommand(char command) {
  Serial.print("Command received: ");
  Serial.println(command);

  switch (command) {
    case FORWARD: forward(currentSpeed); break;
    case BACKWARD: backward(currentSpeed); break;
    case LEFT: left(currentSpeed); break;
    case RIGHT: right(currentSpeed); break;
    case STOP: stop(); break;
    case BEEP: beep(); break;
    case SPEED: processSpeedData(); break;
    case 'A':
      Serial.println("Autonomous mode started...");
      while (true) {
        autonomousMode();
        delay(50);
        if (BT.available()) {
          char stopCommand = BT.read();
          if (stopCommand == 'S') {
            stop();
            Serial.println("Autonomous mode stopped.");
            break;
          }
        }
      }
      break;
    case '0'...'9':
      setSpeedFromValue(command - '0');
      break;
    default:
      Serial.print("Unknown command: ");
      Serial.write(command);
      Serial.print(" (");
      Serial.print((int)command);
      Serial.println(")");
      break;
  }
}

//---------------------------------------------------
// Main loop

void loop() {
  while (BT.available()) {
    char command = BT.read();
    Serial.print("Received: ");
    Serial.write(command);
    Serial.print(" (");
    Serial.print((int)command);
    Serial.println(")");
    executeCommand(command);
    delay(10);
  }
}