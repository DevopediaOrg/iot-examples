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
  Purpose : Interface Raspberry Pi with ADXL345 accelerometer via I2C.
            We use the Adafruit Python ADXL345 for this purpose.
            This can installed with "sudo pip3 install adafruit-adxl345"
            See https://github.com/adafruit/Adafruit_Python_ADXL345
            Ensure that I2C is enabled via raspi-config.
            Ensure that line i2c-dev is present in file /etc/modules
  Date    : 22 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''

import time
import Adafruit_ADXL345

accel = Adafruit_ADXL345.ADXL345()

print('Printing X, Y, Z axis values, press Ctrl-C to quit...')
while True:
    x, y, z = accel.read()
    print('X={0}, Y={1}, Z={2}'.format(x, y, z))
    time.sleep(0.5)
