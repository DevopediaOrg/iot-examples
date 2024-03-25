"""
Send and receive UART serial data.

For the Tetris game, the UART serial interface
is used as the display. Arduino IDE isn't suitable since newline must be 
entered to send commands to the device.

Needs modules pyserial and keyboard.

Call this with serial port name as the first and only argument.
"""

import sys
import time
import serial
import keyboard


def write_to_port(data):
    ser.write(data.name.encode())


# Setup key press callbacks
keyboard.on_press_key("j", write_to_port)
keyboard.on_press_key("k", write_to_port)
keyboard.on_press_key("l", write_to_port)
keyboard.on_press_key("i", write_to_port)


with serial.Serial(sys.argv[1], 115200, timeout=None) as ser:
    while True:
        rxdata = ser.readline().strip()
        try:
            print(rxdata.decode('latin1'))
        except UnicodeDecodeError as e:
            print("ERROR: ", e)
        time.sleep(0.001) # 1ms