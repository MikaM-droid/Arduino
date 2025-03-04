#define LATCH_PIN 4
#define CLK_PIN   7
#define DATA_PIN  8

 void SendDataToSegment(byte Segment_no, byte hexValue);
 
const byte A_HEX = 0x88;  // A
const byte B_HEX = 0x83;  // b
const byte C_HEX  = 0xC6; //C
const byte D_HEX = 0xA1;  // d
const byte E_HEX = 0x86;  // E
const byte F_HEX = 0x8E;  // F
const byte G_HEX = 0xC2;  // G
const byte H_HEX = 0x89;  // H
const byte I_HEX = 0xF9;  // I
const byte J_HEX = 0xE1;  // J
const byte L_HEX = 0xC7;  // L
const byte N_HEX = 0xAB;  // n
const byte O_HEX = 0xC0;  // O
const byte P_HEX = 0x8C;  // P
const byte S_HEX = 0x92;  // S
const byte U_HEX = 0xC1;  // U
const byte Y_HEX = 0x91;  // Y
const byte Z_HEX = 0xA4;  // Z

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

/* Main program================================================================= */
void loop() {
//Update the display with the current counter value
  SendDataToSegment(select_seg1 , H_HEX);
  SendDataToSegment(select_seg2 , I_HEX);
  SendDataToSegment(select_seg3 , L_HEX);
  SendDataToSegment(select_seg4, L_HEX);   
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