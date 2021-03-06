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
  Purpose : Use WiringPi-Python binding of WiringPi C implementation.
            See https://github.com/WiringPi/WiringPi-Python
            This example shows HW PWM on GPIO18. To use HW PWM, run 
            as "sudo python3 wiring_pwm.py" 
            Code also shows the use of SW PWM, which is possible on
            any GPIO pin. To use SW PWM, run as 
            "python3 wiring_pwm.py sw"
  Date    : 13 Jun 2017
  Boards  : Raspberry Pi 2, 3
=====================================================================
'''

import time
import sys
from itertools import chain
import wiringpi


def hw_pwm(n=1000):
    # Official WiringPi C API says support on only GPIO18
    # :however, found to work (in WiringPi Python) with other 
    #  HW-PWM pins GPIO12, GPIO13, GPIO19
    pin = 18
    wiringpi.pinMode(pin, wiringpi.PWM_OUTPUT)
    for _ in range(n):
        for val in chain(range(0, 1024, 50), range(1023, -1, -50)):
            wiringpi.pwmWrite(pin, val)
            time.sleep(0.05)


def sw_pwm(pin, n=1000):
    wiringpi.pinMode(pin, wiringpi.OUTPUT)
    wiringpi.softPwmCreate(pin, 0, 100)
    for _ in range(n):
        for dc in chain(range(0, 101, 5), range(100, -1, -5)):
            wiringpi.softPwmWrite(pin, dc)
            time.sleep(0.05)


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'sw':
        SwPwm = True
    else:
        SwPwm = False

    LedPin = 18 # BCM numbering is default
    wiringpi.wiringPiSetupGpio()

    try:
        if SwPwm:
            sw_pwm(LedPin)
        else:
            hw_pwm()
    except KeyboardInterrupt:
        wiringpi.pinMode(LedPin, 0)
