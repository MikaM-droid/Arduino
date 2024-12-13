#include <IRremote.hpp>

#define IR_REC_D_PIN 6
IRrecv irrecv(IR_REC_D_PIN);
byte result; 

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

#define LED_B 13
#define LED_R 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.begin(IR_REC_D_PIN);
  
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool remote_btn_clicked = irrecv.decode();
  if (remote_btn_clicked) {
    result = irrecv.decodedIRData.command;
    handleInput(result);
    delay(300);
    irrecv.resume();
  }
}

void handleInput (int irdata) {
  String btn = "-";
  switch (irdata) {
  case BTN_1:
    btn = "1";
    //red on
    digitalWrite(LED_R, HIGH);
    break;
  case BTN_2:
    btn = "2";
    //both on
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, HIGH);
    break;
  case BTN_3:
    btn = "3";
    //blue on
    digitalWrite(LED_B, HIGH);
    break;
  case BTN_4:
    btn = "4";
    //red off
    digitalWrite(LED_R, LOW);
    break;
  case BTN_5:
    btn = "5";
    //both off
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, LOW);
    break;
  case BTN_6:
    btn = "6";
    //blue off
    digitalWrite(LED_B, LOW);
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

Serial.println("button " + btn + " - IR-CMD: " + String(irdata));
}
