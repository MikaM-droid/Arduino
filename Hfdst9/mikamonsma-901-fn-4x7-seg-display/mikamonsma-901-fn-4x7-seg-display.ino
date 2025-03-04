#define LATCH_PIN 4
#define CLK_PIN   7
#define DATA_PIN  8

 void SendDataToSegment(byte Segment_no, byte hexValue);
 
const byte C_HEX  = 0xC6;  //P
const byte P_HEX  = 0x8C;  //C
const byte ZERO_HEX = 0xC0; // 0
const byte ONE_HEX  = 0xF9; // 1
const byte TWO_HEX  = 0xA4; // 2
const byte THREE_HEX = 0xB0; // 3
const byte FOUR_HEX = 0x99; // 4
const byte FIVE_HEX = 0x92; // 5
const byte SIX_HEX  = 0x82; // 6
const byte SEVEN_HEX = 0xF8; // 7
const byte EIGHT_HEX = 0x80; // 8
const byte NINE_HEX = 0x90; // 9

byte select_seg1 = 0xF1 ;
byte select_seg2 = 0xF2 ;
byte select_seg3 = 0xF4 ;
byte select_seg4 = 0xF8 ;

const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

void setup () {
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
}

void loop() {
  SendDataToSegment(select_seg1 , ZERO_HEX);
  SendDataToSegment(select_seg2 , TWO_HEX);
  SendDataToSegment(select_seg3 , NINE_HEX);
  SendDataToSegment(select_seg4, SEVEN_HEX);   
}
 
void SendDataToSegment(byte Segment_no, byte hexValue) {
  //Make Latch pin Low
  digitalWrite(LATCH_PIN,LOW);
  //Transfer Segmenent data
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
    //Transfer Segmenent Number
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no );
    //Make Latch pin High so the data appear on Latch parallel pins
  digitalWrite(LATCH_PIN,HIGH);
}