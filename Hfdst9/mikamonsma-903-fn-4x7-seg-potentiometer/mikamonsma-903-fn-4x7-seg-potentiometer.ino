// Pin definitions for the 4-digit 7-segment display
#define LATCH_PIN 4  // Latch pin for the shift register
#define CLK_PIN   7  // Clock pin for the shift register
#define DATA_PIN  8  // Data pin for the shift register
#define POT_PIN  A0  // Analog input pin for the potentiometer

// Function prototype declaration
void SendDataToSegment(byte Segment_no, byte hexValue);

// Hex values for different display patterns
const byte BLANK_HEX = 0xFF; // Blank display (all segments off)
const byte C_HEX  = 0xC6;    // Display 'C'
const byte P_HEX  = 0x8C;    // Display 'P'
const byte ZERO_HEX = 0xC0;  // Display '0'
const byte ONE_HEX  = 0xF9;  // Display '1'
const byte TWO_HEX  = 0xA4;  // Display '2'
const byte THREE_HEX = 0xB0; // Display '3'
const byte FOUR_HEX = 0x99;  // Display '4'
const byte FIVE_HEX = 0x92;  // Display '5'
const byte SIX_HEX  = 0x82;  // Display '6'
const byte SEVEN_HEX = 0xF8; // Display '7'
const byte EIGHT_HEX = 0x80; // Display '8'
const byte NINE_HEX = 0x90;  // Display '9'

// Segment selection values for each digit position
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8}; // Values to select each of the 4 digits

// Array containing hex values for digits 0-9
const byte DIGIT_HEX[] = {
  ZERO_HEX, ONE_HEX, TWO_HEX, THREE_HEX, FOUR_HEX,
  FIVE_HEX, SIX_HEX, SEVEN_HEX, EIGHT_HEX, NINE_HEX
};

// Setup function - runs once when the program starts
void setup() {
  // Configure pins as outputs for the shift register
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  // Configure potentiometer pin as input
  pinMode(POT_PIN, INPUT);
}

/* Main program======================================================================================= */
void loop() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(POT_PIN);
  // Update the display with the potentiometer value
  refreshDisplay(potValue);
}

// Function to update the display with a number
void refreshDisplay(int number) {
  int digits[4] = {0, 0, 0, 0};  // Array to store individual digits
  int numDigits = 0;             // Counter for number of digits

  // Break down the number into individual digits
  while (number > 0 && numDigits < 4) {
    digits[3 - numDigits] = number % 10; // Extract the least significant digit
    number /= 10;                        // Remove the least significant digit
    numDigits++;
  }

  // Update all 4 segments of the display
  for (int i = 0; i < 4; i++) {
    if (i < 4 - numDigits) {
      // Turn off unused segments (leading zeros)
      SendDataToSegment(SEGMENT_SELECT[i], BLANK_HEX);
    } else {
      //display the digits
      SendDataToSegment(SEGMENT_SELECT[i], DIGIT_HEX[digits[i]]);
    }
    delay(3); // Small delay to ensure proper display refresh
  }
}

// Function to send data to a specific segment of the display
void SendDataToSegment(byte Segment_no, byte hexValue) {
  // Prepare shift register for data input
  digitalWrite(LATCH_PIN, LOW);
  
  // Send the segment pattern data
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, hexValue);
  
  // Send the segment selection data
  shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, Segment_no);
  
  // Update the display with the new data
  digitalWrite(LATCH_PIN, HIGH);
}
