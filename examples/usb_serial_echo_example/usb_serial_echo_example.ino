
__xdata char recvStr[64];
uint8_t recvStrPtr = 0;
bool stringComplete = false;
uint16_t echoCounter = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {

  while (USBSerial_available()) {
    char serialChar = USBSerial_read();
    if ((serialChar == '\n') || (serialChar == '\r') ) {
      recvStr[recvStrPtr] = '\0';
      if (recvStrPtr > 0) {
        stringComplete = true;
        break;
      }
    } else {
      recvStr[recvStrPtr] = serialChar;
      recvStrPtr++;
      if (recvStrPtr == 63) {
        recvStr[recvStrPtr] = '\0';
        stringComplete = true;
        break;
      }
    }
  }

  if (stringComplete) {
    USBSerial_print_s("ECHO:");
    USBSerial_println_s(recvStr);
    USBSerial_flush();
    stringComplete = false;
    recvStrPtr = 0;

    echoCounter++;
    USBSerial_print_s("echo count: ");
    USBSerial_println_i(echoCounter);
    USBSerial_flush();
  }
}
