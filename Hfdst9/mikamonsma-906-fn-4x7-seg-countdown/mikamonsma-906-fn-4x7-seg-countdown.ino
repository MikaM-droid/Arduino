// Pins for 7-segment display
#define LATCH_PIN 4
#define CLOCK_PIN 7
#define DATA_PIN 8

// Segment IDs
byte segmentIDs[4] = {
  0xF1, // Segment 1
  0xF2, // Segment 2
  0xF4, // Segment 3
  0xF8  // Segment 4
};

// Numbers as bytes
byte segmentNumbers[10] = {
  0xC0, // 0
  0xF9, // 1
  0xA4, // 2
  0xB0, // 3
  0x99, // 4
  0x92, // 5
  0x82, // 6
  0xF8, // 7
  0x80, // 8
  0x90, // 9
};

byte segmentLetters[20] = {
  0xFF, //1- blank hex 
  0x88,  //2- A
  0x83,  //3- B
  0xC6, //4- C
  0xA1,  //5- D
  0x86,  //6- E
  0x8E,  //7- F
  0xC2,  //8- G
  0x89,  //9- H
  0xF9,  //10- I
  0xE1,  //11- J
  0xC7,  //12- L
  0xAB,  //13- N
  0xC0,  //14- O
  0x8C,  //15- P
  0x92,  //16- S
  0x87, //17- T
  0xC1,  //18- U
  0x91,  //19- Y
  0xA4,  //20- Z
};


/*
  Set a raw value

  byte segmentID        Sets the segment ID
  byte rawValue         Raw value to be written
  @returns              void
*/

void segment_set_raw(byte segmentID, byte rawValue) {

  // Open for data
  digitalWrite(LATCH_PIN, LOW);

  // Send data
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, rawValue);

  // Send register ID
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, segmentID);

  // Close data
  digitalWrite(LATCH_PIN, HIGH);
  
}

/*
  Set a number

  byte segmentID        Sets the segment ID
  u8 (int) number       The number to write (0-9)
  @returns              void
*/

void segment_set_number(byte segmentID, u8 number) {
  if (number > 9) return;
  segment_set_raw(segmentID, segmentNumbers[number]);
}

/*
  Clear a segment

  byte segmentID        Sets the segment ID
  @returns              void
*/
void segment_set_clear(byte segmentID) {
  segment_set_raw(segmentID, 0xFF);
}

void segment_show_ibyte(int segmentID, byte toShow) {
  if (segmentID < 1 || segmentID > 4) return;

  byte segment = segmentIDs[segmentID - 1];
  segment_set_raw(segment, toShow);
}

void segment_show_inum(int segmentID, int toShow, boolean showDot) {
  if (segmentID < 1 || segmentID > 4) return;
  if (toShow > 9) return;

  byte segment = segmentIDs[segmentID - 1];
  byte numberToShow = segmentNumbers[toShow];

  if (showDot == true) {
    // numberToShow &= numberToShow + 0x7F;
    bitWrite(numberToShow, 7, 0);
  }

  segment_set_raw(segment, numberToShow);
}

void segment_show_clear(int segmentID) {
  if (segmentID < 1 || segmentID > 4) return;
  byte segment = segmentIDs[segmentID - 1];
  segment_set_raw(segment, 0xFF);
}

void segment_show(int num) {
  bool show = false;
  if (num > 9999) {
    num = 9999;
    show = true;
  }

  // Serial.println(num);

  if (num > 999) {
    segment_show_inum(1, num/1000, false);
  } else {
    segment_show_clear(1);
  }

  if (num > 99) {
    segment_show_inum(2, num/100 % 10, false);
  } else {
    segment_show_clear(2);
  }

  if (num > 9) {
    segment_show_inum(3, num/10 % 10, false);
  } else {
    segment_show_clear(3);
  }

  if (num > 0) {
    segment_show_inum(4, num/1 % 10, show);
  } else {
    segment_show_clear(4);
  }
}

/*
  Setup all the pins

  @returns              void
*/

void segment_setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  Serial.begin(9600);
}
