'''=====================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ---------------------------------------------------------------------
  Purpose : Read commands from UART to control LED state.
            Use gpiozero module to control the LED.
  Date    : 15 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''

import serial
from gpiozero import LED

ser = serial.Serial("/dev/ttyAMA0", 115200)
led = LED(4)
ledcmds = ['off', 'on']
try:
    while True:
        cmd = ser.read_until().strip(b'\r\n').decode()

        if cmd not in ledcmds:
            ser.write("Not a valid LED command; valid commands are 'off' and 'on'.".encode())
            continue

        ser.write("Turning {} the LED...".format(cmd.upper()).encode())
        if cmd == 'on':
            led.on()
        else:
            led.off()
except KeyboardInterrupt:
    if ser != None:
        ser.close()
