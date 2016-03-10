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
  Boards  : Raspberry Pi 2
  =====================================================================
'''

# Wiki examples on RPi.GPIO:
# https://sourceforge.net/p/raspberry-gpio-python/wiki/Examples/

import RPi.GPIO as GPIO
import time

ToBlink = True # True: blink, False: fade
LedPin = 7 # GPIO7 for board numbering; GPIO4 for BCM numbering
ButtonPin = 8

def init():
    GPIO.setmode(GPIO.BOARD)
    
    GPIO.setup(LedPin, GPIO.OUT)
    
    # Pulldown mode and detect event when push button is released
    GPIO.setup(ButtonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.add_event_detect(ButtonPin, GPIO.FALLING)

    
def readButton():
    global ToBlink
    if GPIO.event_detected(ButtonPin):
        ToBlink = not ToBlink

    
def blink(n=1):
    for _ in range(n):
        GPIO.output(LedPin, True)
        time.sleep(1)
        GPIO.output(LedPin, False)
        time.sleep(1)

        
def fade(n=1):
    pwm = GPIO.PWM(LedPin, 500)
    for _ in range(n):
        for dutyCycle in range(0, 100, 5):
            pwm.start(dutyCycle)
            time.sleep(0.05)
        for dutyCycle in range(100, 0, -5):
            pwm.start(dutyCycle)
            time.sleep(0.05)
    pwm.stop()


init()
try:
    while True:
        readButton()
        if ToBlink:
            blink()
        else:
            fade()
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
