# ch55xRebootTool

![ch55xRebootTool photo](https://raw.githubusercontent.com/DeqingSun/ch55xduino/playground/pcb/ch55xRebootTool/ch55xRebootTool.jpg)

ch55xRebootTool is a hardware tool to reset a WCH chip target into the bootloader without touching the board with your finger. It solves 2 problems: 

1. Some chips can not jump to bootloader from user code.

2. When you are developing the USB host code, the USB port will be occupied by a device.

## How to use the tool

### Basic usage

Connect 2 micro USB cables from the computer to the 2 micro USB ports on the left. The upper one is connected to the target, and the lower one is to send commands to the controller on board.

The left MicroUSB port and the USB A port next to it are connected. The target can be plugged into either port.

If your target chip needs to pull down a pin to enter the bootloader, connect that pin to the P1.6 on the board. If the target uses D+, no connection is needed.

Open the ch55xRebootTool serial port @ 1200 rate and it will kick target into the bootloader.

### Use the serial adapter

This board can also be used as a serial adapter. Just use the 3-pin header on the right. Note the board can not work at the 1200 rate or higher than 115200. 

### Use a USB device for host code development

Plug the device on the USB port on the right side of the top. When the P1.7 on the board gets pulled down. The board will supply power to the device, and switch the target from the computer to the device. You may use a pin on the target to do the control

Note the target will switch back to the computer in bootloader mode.

## Enter the bootloader

Most WCH chips can upload firmware via USB. However, the chip must enter the bootloader to upload the firmware. Generally, there are 2 ways to enter bootloader:

1. Pull a specific pin to GND or D+ to VCC, depending on your settings in the configuration byte. Then power the chip.

2. Jump into the bootloader within the user code. But this does not work for chips such as CH549.

If you already played with the CH55xduino on a CH55x chip, you may not feel the pain. Because when you upload the code, the Arduino environment will open the virtual serial port on the CH55x chip at a 1200 baud rate. The CH55xduino firmware will jump to the bootloader automatically and receive the code from the computer. The user experience is just pressing a button on your computer and everything gets ready. 

But if the firmware is not working properly or you are using chips like CH549, the chip won't enter the bootloader automatically. You may need to unplug the USB cable, hold a button and plug the USB cable back, that is a pain when you repeat the process over and over again.

Instead of doing it manually, the ch55xRebootTool will act as a serial adapter. When you open the serial port at a 1200 baud rate, the tool will disconnect the power from the target chip using a PMOS, connect a 10K resistor to D+, and pulldown the pin P1.6, before restoring the power cycle. Basically, the ch55xRebootTool does the power cycle and pulls the pin for you. 

## Use a USB device

When developing the host code, you may need to switch the target back and forth between the computer and the device. This tool does it automatically for you. You just need to pull the Pin 1.7 low to connect the device. When it is released, the target will be connected back to the computer. 

When I design the board. I wish the target can send a reset command on the USB bus, and the controller knows when the target left the bootloader, and can switch to the device automatically. But I have not got it working so far. 


