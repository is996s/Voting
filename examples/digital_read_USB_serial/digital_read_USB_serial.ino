void    mDelaymS( uint16_t n )  ;
uint8_t pushButton = 34;
void setup() {

  //pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  uint8_t buttonState = digitalRead(pushButton);
  // print out the state of the button:
  if (buttonState) {
    USBSerial_print_n("HIGH\n", 5);
    USBSerial_flush();
  } else {
    USBSerial_print_n("LOW\n", 4);
    USBSerial_flush();
  }

  mDelaymS(100);        // delay in between reads for stability
}
