#define LATCH_PIN 4
#define CLK_PIN   7
#define DATA_PIN  8

void SendDataToSegment(byte Segment_no, byte hexValue);

const byte BLANK_HEX = 0xFF; //blank hex 
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
const byte T_HEX = 0x87; // T
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

//==============================================================================

const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

const byte CHAR_HEX_MAP[26] = {
  A_HEX, B_HEX, C_HEX, D_HEX, E_HEX, F_HEX, G_HEX, H_HEX, I_HEX, J_HEX, 
  BLANK_HEX, L_HEX, BLANK_HEX, N_HEX, O_HEX, P_HEX, BLANK_HEX, BLANK_HEX, S_HEX, BLANK_HEX, 
  U_HEX, BLANK_HEX, BLANK_HEX, BLANK_HEX, Y_HEX, Z_HEX
};

//==============================================================================

unsigned long last = 0;

int val = 0;

void setup ()
{
/* All the pins like latch, clock and data pins are used as output */
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
}

const int letterSequence1[] = {C_HEX, A_HEX, T_HEX, BLANK_HEX};
const int letterSequence2[] = {A_HEX, T_HEX, BLANK_HEX, C_HEX};
const int letterSequence3[] = {T_HEX, BLANK_HEX, C_HEX, A_HEX};
const int letterSequence4[] = {BLANK_HEX, C_HEX, A_HEX, T_HEX};
int letterIndex = 0;

//===============================================================================

void loop() {
  if (millis() - last >= 1000) {  //checking how much time passed inbetween
    last = millis();  //update the last recorded time

    val = analogRead(A0);
    Serial.println("Sensor read!");  //print a debug message

    // Cycle through the letters
    letterIndex++;  
    if (letterIndex >= 4) {  //if the index exceeds array length, reset to 0
      letterIndex = 0;
    }
  }

  // Display updated letters
  SendDataToSegment(select_seg1, letterSequence1[letterIndex]);  // Changing every second
  SendDataToSegment(select_seg2, letterSequence2[letterIndex]);
  SendDataToSegment(select_seg3, letterSequence3[letterIndex]);
  SendDataToSegment(select_seg4, letterSequence4[letterIndex]);
}

//===============================================================================
 
void SendDataToSegment(byte Segment_no, byte hexValue)
{
  /* Make Latch pin Low */
  digitalWrite(LATCH_PIN,LOW);
  /* Transfer Segmenent data */
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
    /* Transfer Segmenent Number  */
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no );
    /* Make Latch pin High so the data appear on Latch parallel pins */
  digitalWrite(LATCH_PIN,HIGH);
}