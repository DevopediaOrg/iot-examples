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
  Purpose : Use RPi.GPIO module to blink or fade an LED. Execution
            switches between the two whenever a push button is pressed
            and released. Fading uses software PWM since RPi.GPIO
            module does not support hardware PWM. Note that RPi.GPIO
            is available by default on Raspbian Jessie.
  Date    : 10 Mar 2016
  Boards  : Raspberry Pi 3
  =====================================================================
'''

# Wiki examples on RPi.GPIO:
# https://sourceforge.net/p/raspberry-gpio-python/wiki/Examples/

import time
import sys
from itertools import chain
import RPi.GPIO as GPIO


def blink(pin, n=1):
    for _ in range(n):
        GPIO.output(pin, True)
        time.sleep(0.5)
        GPIO.output(pin, False)
        time.sleep(0.5)


def fade(pin, n=1000):
    pwm = GPIO.PWM(pin, 100)
    pwm.start(0)
    try:
        for _ in range(n):
            for dc in chain(range(0, 101, 5), range(100, -1, -5)):
                pwm.ChangeDutyCycle(dc)
                time.sleep(0.05)
    except KeyboardInterrupt:
        pwm.stop()
        raise KeyboardInterrupt
    pwm.stop()


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'fade':
        ToFade = True
    else:
        ToFade = False

    LedPin = 7 # GPIO7 for board numbering; GPIO4 for BCM numbering
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(LedPin, GPIO.OUT)

    try:
        while True:
            if ToFade:
                blink(LedPin)
            else:
                fade(LedPin)
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()
