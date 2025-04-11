/*
 * 4x7 Segment Display Control Program
 * This program controls a 4-digit 7-segment display using shift registers
 * It displays the word "HILL" on the display
 */

// Pin definitions for shift register control
#define LATCH_PIN 4  // Latch pin (ST_CP) of 74HC595
#define CLK_PIN   7  // Clock pin (SH_CP) of 74HC595
#define DATA_PIN  8  // Data pin (DS) of 74HC595

// Function prototype
void SendDataToSegment(byte Segment_no, byte hexValue);
 
// Hexadecimal patterns for letters on 7-segment display
// Each bit in the hex value controls a specific segment (a-g and decimal point)
const byte A_HEX = 0x88;  // A
const byte B_HEX = 0x83;  // b
const byte C_HEX  = 0xC6; // C
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

// Hexadecimal patterns for numbers on 7-segment display
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

// Segment selection patterns for each digit
// These values are used to select which digit to display
byte select_seg1 = 0xF1;  // First digit
byte select_seg2 = 0xF2;  // Second digit
byte select_seg3 = 0xF4;  // Third digit
byte select_seg4 = 0xF8;  // Fourth digit

// Array containing all segment selection patterns
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

// Setup function - runs once at startup
void setup() {
  // Set pin modes for shift register control
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

/* Main program================================================================= */
void loop() {
  // Update the display with the word "HILL"
  SendDataToSegment(select_seg1, H_HEX);  // Display 'H' on first digit
  SendDataToSegment(select_seg2, I_HEX);  // Display 'I' on second digit
  SendDataToSegment(select_seg3, L_HEX);  // Display 'L' on third digit
  SendDataToSegment(select_seg4, L_HEX);  // Display 'L' on fourth digit
}
 
void SendDataToSegment(byte Segment_no, byte hexValue) {
  // Make Latch pin Low to start data transfer
  digitalWrite(LATCH_PIN, LOW);
  
  // Transfer segment data (which segments to light up)
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
  
  // Transfer segment number (which digit to update)
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no);
  
  // Make Latch pin High to update the display
  digitalWrite(LATCH_PIN, HIGH);
}