// Pin definitions for the 4-digit 7-segment display
#define LATCH_PIN 4  // Latch pin for the shift register
#define CLK_PIN   7  // Clock pin for the shift register
#define DATA_PIN  8  // Data pin for the shift register

// Function prototype for sending data to segments
void SendDataToSegment(byte Segment_no, byte hexValue);

// Hex values for blank display and letters A-Z
const byte BLANK_HEX = 0xFF; // Blank display (all segments off)
const byte A_HEX = 0x88;     // A
const byte B_HEX = 0x83;     // b
const byte C_HEX  = 0xC6;    // C
const byte D_HEX = 0xA1;     // d
const byte E_HEX = 0x86;     // E
const byte F_HEX = 0x8E;     // F
const byte G_HEX = 0xC2;     // G
const byte H_HEX = 0x89;     // H
const byte I_HEX = 0xF9;     // I
const byte J_HEX = 0xE1;     // J
const byte L_HEX = 0xC7;     // L
const byte N_HEX = 0xAB;     // n
const byte O_HEX = 0xC0;     // O
const byte P_HEX = 0x8C;     // P
const byte S_HEX = 0x92;     // S
const byte T_HEX = 0x87;     // T
const byte U_HEX = 0xC1;     // U
const byte Y_HEX = 0x91;     // Y
const byte Z_HEX = 0xA4;     // Z

// Hex values for numbers 0-9
const byte ZERO_HEX = 0xC0;  // 0
const byte ONE_HEX  = 0xF9;  // 1
const byte TWO_HEX  = 0xA4;  // 2
const byte THREE_HEX = 0xB0; // 3
const byte FOUR_HEX = 0x99;  // 4
const byte FIVE_HEX = 0x92;  // 5
const byte SIX_HEX  = 0x82;  // 6
const byte SEVEN_HEX = 0xF8; // 7
const byte EIGHT_HEX = 0x80; // 8
const byte NINE_HEX = 0x90;  // 9

// Segment selection bytes for each digit
byte select_seg1 = 0xF1;  // First digit
byte select_seg2 = 0xF2;  // Second digit
byte select_seg3 = 0xF4;  // Third digit
byte select_seg4 = 0xF8;  // Fourth digit

//==============================================================================
// Array of segment selection bytes for easy iteration
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};

// Mapping of letters A-Z to their corresponding hex values
// BLANK_HEX is used for letters that can't be displayed on a 7-segment display
const byte CHAR_HEX_MAP[26] = {
  A_HEX, B_HEX, C_HEX, D_HEX, E_HEX, F_HEX, G_HEX, H_HEX, I_HEX, J_HEX, 
  BLANK_HEX, L_HEX, BLANK_HEX, N_HEX, O_HEX, P_HEX, BLANK_HEX, BLANK_HEX, S_HEX, BLANK_HEX, 
  U_HEX, BLANK_HEX, BLANK_HEX, BLANK_HEX, Y_HEX, Z_HEX
};

//==============================================================================
// Variables for timing and sensor reading
unsigned long last = 0;  // Last time the display was updated
int val = 0;            // Value read from analog sensor

void setup() {
  // Initialize all pins as outputs
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

// Arrays defining the scrolling sequences for each digit
// Each array contains 4 values that will be displayed in sequence
const int letterSequence1[] = {C_HEX, A_HEX, T_HEX, BLANK_HEX};  // First digit sequence
const int letterSequence2[] = {A_HEX, T_HEX, BLANK_HEX, C_HEX};  // Second digit sequence
const int letterSequence3[] = {T_HEX, BLANK_HEX, C_HEX, A_HEX};  // Third digit sequence
const int letterSequence4[] = {BLANK_HEX, C_HEX, A_HEX, T_HEX};  // Fourth digit sequence
int letterIndex = 0;  // Current position in the sequence

//===============================================================================

void loop() {
  // Update display every 1000ms (1 second)
  if (millis() - last >= 1000) {
    last = millis();  // Update the last recorded time

    // Read analog sensor value (though not currently used in display logic)
    val = analogRead(A0);
    Serial.println("Sensor read!");  // Debug message

    // Move to next position in the sequence
    letterIndex++;
    if (letterIndex >= 4) {  // Reset to beginning if we've reached the end
      letterIndex = 0;
    }
  }

  // Update all four digits with their current sequence values
  SendDataToSegment(select_seg1, letterSequence1[letterIndex]);
  SendDataToSegment(select_seg2, letterSequence2[letterIndex]);
  SendDataToSegment(select_seg3, letterSequence3[letterIndex]);
  SendDataToSegment(select_seg4, letterSequence4[letterIndex]);
}

//===============================================================================
 
void SendDataToSegment(byte Segment_no, byte hexValue) {
  // Prepare shift register for new data
  digitalWrite(LATCH_PIN, LOW);
  
  // Send the segment pattern (which segments to light up)
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
  
  // Send the segment number (which digit to display on)
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no);
  
  // Latch the data to make it visible on the display
  digitalWrite(LATCH_PIN, HIGH);
}