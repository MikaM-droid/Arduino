// IR remote control
// The library IRremote is used to receive IR signals from a remote control
#include <IRremote.hpp>

// Define the pin for the IR receiver
#define IR_REC_D_PIN 6

// Create an object of the IRrecv class
IRrecv irrecv(IR_REC_D_PIN);

// Define a variable to store the result of the IR signal
byte result; 

// Define the buttons of the IR remote control
#define BTN_1 69
#define BTN_2 70
#define BTN_3 71
#define BTN_4 68
#define BTN_5 64
#define BTN_6 67
#define BTN_7 7
#define BTN_8 21
#define BTN_9 9
#define BTN_0 25

#define BTN_STER 22
#define BTN_HASHTAG 13

#define BTN_UP 24
#define BTN_DOWN 82
#define BTN_LEFT 8
#define BTN_RIGHT 90

#define BTN_OK 28

void setup() {
  Serial.begin(9600);
  // Initialize the IR receiver
  irrecv.begin(IR_REC_D_PIN);

}

void loop() {
  // Check if the IR receiver has received a signal
  bool remote_btn_clicked = irrecv.decode();
  if (remote_btn_clicked) {
    // Store the result of the IR signal
    result = irrecv.decodedIRData.command;
    // Handle the input
    handleInput(result);
    delay(500);
    // Resume the IR receiver
    irrecv.resume();
  }
}

void handleInput (int irdata) {
  // Define a variable to store the button
  String btn = "-";
  // Switch case to handle the input
  switch (irdata) {
  case BTN_1:
    btn = "1";
    break;
  case BTN_2:
    btn = "2";
    break;
  case BTN_3:
    btn = "3";
    break;
  case BTN_4:
    btn = "4";
    break;
  case BTN_5:
    btn = "5";
    break;
  case BTN_6:
    btn = "6";
    break;
  case BTN_7:
    btn = "7";
    break;
  case BTN_8:
    btn = "8";
    break;
  case BTN_9:
    btn = "9";
    break;
  case BTN_0:
    btn = "0";
    break;
  case BTN_STER:
    btn = "*";
    break;
  case BTN_HASHTAG:
    btn = "#";
    break;
  case BTN_UP:
    btn = "up";
    break;
  case BTN_LEFT:
    btn = "left";
    break;
  case BTN_DOWN:
    btn = "down";
    break;
  case BTN_RIGHT:
    btn = "right";
    break;
  case BTN_OK:
    btn = "ok";
    break;
  default:
    btn = "nonexistent";
}

  // Print the button and the IR command
  Serial.println("button " + btn + " - IR-CMD: " + String(irdata));
}