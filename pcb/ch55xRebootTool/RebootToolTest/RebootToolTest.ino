#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "src/userUsbCdc/USBCDC.h"
extern __xdata uint8_t LineCoding[]; //lineCoding of CDC is located in this array
extern __xdata uint8_t controlLineState;
__xdata uint32_t oldBaudRate = 9600;
__xdata uint8_t oldLineState = 0;

#define USB_SWITCH_PIN 33
#define POWER_TARGET_PIN 34
#define USBDP_PULLUP_TARGET_PIN 14
#define BOOTLOADER_PULLDOWN_TARGET_PIN 16

#define SENSE_TARGET_SWTICH_PERF 17
#define POWER_PERF_PIN 11

void bootloaderRoutine() {
  USB_CTRL = 0;
  EA = 0;                                                                    //Disabling all interrupts is required.
  delayMicroseconds(50000);
  delayMicroseconds(50000);
  __asm__ ("lcall #0x3800");                                                 //Jump to bootloader code
  while (1);
}

void setup() {
  USBInit();

  pinMode(USB_SWITCH_PIN, OUTPUT);
  digitalWrite(USB_SWITCH_PIN, LOW);  //connect target to computer USB

  pinMode(POWER_TARGET_PIN, OUTPUT);
  digitalWrite(POWER_TARGET_PIN, LOW);

  pinMode(USBDP_PULLUP_TARGET_PIN, OUTPUT);
  digitalWrite(USBDP_PULLUP_TARGET_PIN, HIGH);

  pinMode(BOOTLOADER_PULLDOWN_TARGET_PIN, INPUT);
  
  pinMode(SENSE_TARGET_SWTICH_PERF, INPUT_PULLUP);

  pinMode(POWER_PERF_PIN, OUTPUT);
  digitalWrite(POWER_PERF_PIN, HIGH);

  Serial0_begin(9600);

}

void loop() {
  __xdata uint32_t currentBaudRate = *((__xdata uint32_t *)LineCoding); //both linecoding and sdcc are little-endian
  __xdata uint8_t currentLineState = controlLineState; //both linecoding and sdcc are little-endian

  while (USBSerial_available()) {
    char serialChar = USBSerial_read();
    Serial0_write(serialChar);
  }
  Serial0_flush();

  while (Serial0_available()) {
    char serialChar = Serial0_read();
    USBSerial_write(serialChar);
  }
  USBSerial_flush();

  if (oldBaudRate != currentBaudRate) {
    oldBaudRate = currentBaudRate;
    Serial0_begin(currentBaudRate);
  }

  if (oldLineState != currentLineState) {
    if  ( ((currentLineState & 0x01) == 0) && ((oldLineState & 0x01) == 1)) {
      if (currentBaudRate == 1200) {
        digitalWrite(POWER_TARGET_PIN, HIGH); //Cut target power
        digitalWrite(POWER_PERF_PIN, HIGH); //Cut peripheral power
        digitalWrite(USB_SWITCH_PIN, LOW);  //connect target to computer USB
        delay(100);
        digitalWrite(USBDP_PULLUP_TARGET_PIN, LOW); //Connect pull up resistor to target
        digitalWrite(BOOTLOADER_PULLDOWN_TARGET_PIN, LOW); //if the bootloader require a pin to be pulled low, use this pin  
        pinMode(BOOTLOADER_PULLDOWN_TARGET_PIN, OUTPUT);
        delay(10);
        digitalWrite(POWER_TARGET_PIN, LOW); //Restore target power
        delay(50);
        digitalWrite(USBDP_PULLUP_TARGET_PIN, HIGH); //Disconnect pull up resistor to target
        pinMode(BOOTLOADER_PULLDOWN_TARGET_PIN, INPUT);
      }
    }
    oldLineState = currentLineState;
  }

  if (digitalRead(15) == LOW) {
    delay(10);
    if (digitalRead(15) == LOW) {
      bootloaderRoutine();
    }
  }

  if (digitalRead(SENSE_TARGET_SWTICH_PERF)) {
    digitalWrite(POWER_PERF_PIN, HIGH); //Cut peripheral power
    digitalWrite(USB_SWITCH_PIN, LOW);  //connect target to computer USB
  } else {
    digitalWrite(POWER_PERF_PIN, LOW); //Set peripheral power
    digitalWrite(USB_SWITCH_PIN, HIGH);  //connect target to peripheral USB
  }

}
