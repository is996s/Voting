#!/usr/bin/python

import serial
import serial.tools.list_ports
from time import sleep

comlist = serial.tools.list_ports.comports()
ch55xRebootToolDevice = None
for element in comlist:
    if (element.vid == 0x1209 and element.pid == 0xC550):
        if (element.product == "CH55xReboot"):
            ch55xRebootToolDevice = element.device

if (ch55xRebootToolDevice!=None):
    print("ch55xRebootTool Found on: " + ch55xRebootToolDevice)
    ch55xRebootToolSerial = serial.Serial(ch55xRebootToolDevice,baudrate=1200,timeout=0.01,rtscts=1)
    sleep(0.1)
    ch55xRebootToolSerial.close()
    #sleep(1)
else:
    print("ch55xRebootTool not found.")
