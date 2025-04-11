// Pin definitions for the 4-digit 7-segment display
// LATCH_PIN: Controls when data is latched to the display
// CLK_PIN: Clock signal for data transfer
// DATA_PIN: Serial data input
#define LATCH_PIN 4
#define CLK_PIN   7
#define DATA_PIN  8

// Function prototype for sending data to a specific segment
void SendDataToSegment(byte Segment_no, byte hexValue);
 
// Hexadecimal values for displaying different characters on 7-segment display
// These values represent the segments that need to be lit for each character
const byte C_HEX  = 0xC6;  // Display 'C'
const byte P_HEX  = 0x8C;  // Display 'P'
const byte ZERO_HEX = 0xC0; // Display '0'
const byte ONE_HEX  = 0xF9; // Display '1'
const byte TWO_HEX  = 0xA4; // Display '2'
const byte THREE_HEX = 0xB0; // Display '3'
const byte FOUR_HEX = 0x99; // Display '4'
const byte FIVE_HEX = 0x92; // Display '5'
const byte SIX_HEX  = 0x82; // Display '6'
const byte SEVEN_HEX = 0xF8; // Display '7'
const byte EIGHT_HEX = 0x80; // Display '8'
const byte NINE_HEX = 0x90; // Display '9'

// Segment selection values for each digit position
// These values determine which digit is being addressed
byte select_seg1 = 0xF1; // First digit (rightmost)
byte select_seg2 = 0xF2; // Second digit
byte select_seg3 = 0xF4; // Third digit
byte select_seg4 = 0xF8; // Fourth digit (leftmost)

// Array containing all segment selection values
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void setup() {
  // Initialize all pins as outputs
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  // Display "0297" on the 4-digit display
  // Each SendDataToSegment call updates one digit
  SendDataToSegment(select_seg1, ZERO_HEX);  // Display '0' on first digit
  SendDataToSegment(select_seg2, TWO_HEX);   // Display '2' on second digit
  SendDataToSegment(select_seg3, NINE_HEX);  // Display '9' on third digit
  SendDataToSegment(select_seg4, SEVEN_HEX); // Display '7' on fourth digit
}
 
void SendDataToSegment(byte Segment_no, byte hexValue) {
  // Prepare to send data by setting LATCH_PIN low
  digitalWrite(LATCH_PIN, LOW);
  
  // Send the segment pattern data first
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
  
  // Send the segment selection data
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no);
  
  // Latch the data to make it visible on the display
  digitalWrite(LATCH_PIN, HIGH);
}