# Ch55xduino: Small Devices Arduino for ch55x devices

**Getting started on the Ch55x the easy way. Forked from Sduino project, also based on 
ch554_sdcc project**

Ch55xduino is an Arduino-like programming API for the CH55X, a family of low-cost MCS51 USB MCU. The project tries to remove the difficulty of setting up a compiling environment. Users can simply write code in Arduino IDE and hit one button to flash the chip to get code running. No configuration or guesswork needed. 

CH551/2/4 may be the lowest part count system that works with Arduino. The minimal system only requires one chip, 2 decoupling capacitors, and one optional pull-up resistor. These features made it ideal for DIY projects. 

![Script running gif](https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/docs/blinkLED.gif)

At this moment the project is still working-in-progress. USB-CDC communication, delay, millis, and the digital and analog pin functions are supported. Refer to examples in this repo for more info.

## Installation

Automatic IDE integration is supported via the
Arduino Boards Manager. This is the recommanded way of installation now. 

Start the Arduino-IDE. In *File->Preferences*, *Settings* tab, enter

> https://raw.githubusercontent.com/DeqingSun/ch55xduino/ch55xduino/package_ch55xduino_mcs51_index.json

as an *Additional Boards Manager URL*.

* Open *Tools->Board:...->Boards Manager*
* Find Sduino by typing 'sd' into the search line
* Click on the list entry
* Click on *Install*.

Now you should find a new entry *CH55x Boards* in the list at
*Tools->Board:...*

* Choose *CH552 Board* from the list
* open the standard Blink example from *File->Examples->01. Basics->Blink*
* Change pin number in Blink example. For example, if you have LED on P3_0, you will write pin 30.
* compile it by hitting *Verify*
* If your board is never used with ch55xduino before, you need to make the ch55x chip enter bootloader mode. You need to disconnect USB and unpower ch55x, connect the pull-up resistor on D+ line (generally a 10K resistor between D+ and 5V, controlled by a push-button or adjacent pads). Then you connect USB. and hit *Upload*. Also, a blank new chip will enter the bootloader automatically.
* If you have used ch55xduino once and your code doesn't crash the USB subsystem, you can simply press *Upload*. Arduino and the firmware will kick the chip into the bootloader automatically.

## Known issues


## Included libraries

To be added. No library yet.


## Compatibility with the Arduino world

Since there is no free C++ compiler for the MCS51, it is impossible to do a
full 1:1 port of the whole enviroment as is has been done for the STM32 and
the ESP8266.

This is not a drop-in replacement for an AVR, but thanks to some C
preprocessor magic the programming API is still very, very similar and it is
often enough to just move over the opening bracket of the class
instanciation statement and to replace the dot in a method call for an
underscore. Check the [migration
guide](https://tenbaht.github.io/sduino/api/migration/) for an overview.



## Supported Systems:

Arduino IDE versions 1.8.12 are tested, but
most versions >=1.6.6 should work.

* Windows: Tested on Windows 7. Ch55xduino should work on XP (not tested).

* MacOS: tested on 10.14.
