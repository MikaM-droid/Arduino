void setup() {

  Serial.begin(9600);

  // Register pins
  segment_setup();

  // PotMeter
  pinMode(A0, INPUT);

  // Delay
  delay(1000);

  // Uitleg
  Serial.println("Welcome to this 7 segment program :)!");
  Serial.println("Pick a program:");
  Serial.println("1      - Potentiometer");
  Serial.println("2      - Show word");
  Serial.println("3      - Countdown timer");
  Serial.println("4      - Scrolling text");

  Serial.println("");

  Serial.println("Enter the number of the mode you'd like to use ");

}

u32 i = 0;
unsigned long last = 0;

int val = 0;
int mode = 0;


void loop() {

  if (mode == 0) {
    if (Serial.available() > 0) {
      mode = Serial.readString().toInt();

      Serial.println("Mode that was chosen: " + String(mode));
    }
    return;
  }

  switch(mode) {
    case 1:
      PotMeter();
      break;
    case 2:
      Letter();
      break;
    case 3:
      Timer();
      break;
    case 4:
      scrollingText();
      break;
    default:
      Serial.println("Mode does not exist you stupid ah-");
      mode = 0;
  }

}

void PotMeter() {
  if (millis()-last >= 1000) {
    last = millis();

    val = analogRead(A0);

    Serial.println("Sensor read :)");
  }
  segment_show(val);
}

void Letter() {
  segment_show_ibyte(1, 0xC6);
  segment_show_ibyte(2, 0x88);
  segment_show_ibyte(3, 0x87);
  segment_show_ibyte(4, 0x92);
}

void Timer() {

}

void delayMillis(unsigned long duration) {
    unsigned long startTime = millis();  // Record the start time
    while (millis() - startTime < duration) {
        // Do nothing, just wait for the duration to pass
    }
}

void scrollingText() {
  segment_show_ibyte(1, 0xC6);
  segment_show_ibyte(2, 0x88);
  segment_show_ibyte(3, 0x87);
  segment_show_ibyte(4, 0x92);
  delayMillis(10000);
  segment_show_ibyte(1, 0xC2);
  segment_show_ibyte(2, 0x88);
  segment_show_ibyte(3, 0x88);
  segment_show_ibyte(4, 0x92);
}