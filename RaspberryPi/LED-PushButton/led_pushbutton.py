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
  Purpose : Use GPIO Zero module to control an LED. LED state toggles
            whenever a push button is pressed and released.
  Date    : 14 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''

import time
import sys
from gpiozero import LED, Button
from signal import pause


led = LED(4)
button = Button(17)

# Here we associate button events with LED callbacks
button.when_pressed = led.on
button.when_released = led.off

pause()
