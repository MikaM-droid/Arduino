//--------------------------------------------------- CORRECT FILE!
// To do: Make the sensor turn left and right to check for distances.
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

// Servo pin
#define  SERVO_PIN 13

// Bluetooth
#define BT_RX 2
#define BT_TX 7
SoftwareSerial BT(BT_RX, BT_TX);

// Buzzer
#define PIEP 12

// Line sensors
#define LINE_LEFT A0
#define LINE_CENTER A1
#define LINE_RIGHT A2

// Object sensors
#define OBJECT_LEFT A3
#define OBJECT_RIGHT A4

// Ultrasonic
#define TRIG_PIN 6
#define ECHO_PIN 11

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
// Movement forward
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

//---------------------------------------------------
// Backward
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

//---------------------------------------------------
// Left
void left(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.print("Turning left, speed: ");
  Serial.println(speed);
}

//---------------------------------------------------
// Right
void right(int speed) {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.print("Turning right, speed: ");
  Serial.println(speed);
}

//---------------------------------------------------
// Stop
void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stopped");
}

//---------------------------------------------------
// Beep
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
// Ultrasonic distance

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

//---------------------------------------------------
// Autonomous mode

int lastDistance = 0;
int distanceChange = 0;
bool isStuck = false;

void autonomousMode() {

  int distance = getDistance();
  int leftLine = analogRead(LINE_LEFT);
  int centerLine = analogRead(LINE_CENTER);
  int rightLine = analogRead(LINE_RIGHT);
  bool objLeft = digitalRead(OBJECT_LEFT);
  bool objRight = digitalRead(OBJECT_RIGHT);

  distanceChange = distance - lastDistance;
  lastDistance = distance;

  Serial.print("Distance: "); Serial.println(distance);
  Serial.print("Distance change: "); Serial.println(distanceChange);
  Serial.print("Line sensors: L="); Serial.print(leftLine);
  Serial.print(" C="); Serial.print(centerLine);
  Serial.print(" R="); Serial.println(rightLine);
  Serial.print("Object sensors: Left="); Serial.print(objLeft);
  Serial.print(" Right="); Serial.println(objRight);

  int threshold = 500;

  bool obstacleDetected = false;

  if (abs(distanceChange) < 2 && distance < 5) {
    isStuck = true;
  } else {
    isStuck = false;
  }

  if (distance < 5 || objLeft == LOW || objRight == LOW || isStuck) {
    obstacleDetected = true;
  }

  if (obstacleDetected) {
    stop();
    beep();
    delay(100);

    backward(currentSpeed);
    delay(400);  // Increase backward duration

    if (isStuck) {
      if (random(2) == 0) {
        left(currentSpeed + 50);
        delay(1000);
      } else {
        right(currentSpeed + 50);
        delay(1000);
      }
    } else {
      if (objLeft == LOW && objRight == HIGH) {
        Serial.println("Obstacle on LEFT detected. Turning RIGHT.");
        right(currentSpeed + 30);
        delay(800);
      } else if (objRight == LOW && objLeft == HIGH) {
        Serial.println("Obstacle on RIGHT detected. Turning LEFT.");
        left(currentSpeed + 30);
        delay(800);
      } else {
        Serial.println("Obstacle detected in front or both sides. Turning randomly.");
        if (random(2) == 0) {
          left(currentSpeed + 30);
        } else {
          right(currentSpeed + 30);
        }
        delay(800);
      }
    }
    return;
  }

  if (leftLine < threshold && centerLine > threshold && rightLine < threshold) {
    forward(currentSpeed);
  } else if (leftLine > threshold && centerLine < threshold) {
    left(currentSpeed);
  } else if (rightLine > threshold && centerLine < threshold) {
    right(currentSpeed);
  } else {
    forward(currentSpeed);
  }
}

//---------------------------------------------------
// Command handler

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
  randomSeed(analogRead(0));

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

