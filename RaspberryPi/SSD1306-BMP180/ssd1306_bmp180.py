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
  Purpose : Use BMP180 to obtain three sensor readings: temperature,
            barometric pressure and altitude. BMP180 uses an I2C 
            interface.
            Show these readings on SSD1306 OLED display. This uses an
            SPI interface.
            RPI is used with the WaveShare Pioneer600 that contains
            both BM180 and SSD1306. Code is adapted from examples at
            https://www.waveshare.com/wiki/File:Pioneer600-Code.tar.gz
            For this example, install Python packages (via pip3):
            smbus, pillow
  Date    : 19 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''

import time
from BMP180 import BMP180
import spidev
import SSD1306
from PIL import Image, ImageDraw, ImageFont

bmp = BMP180()
disp = SSD1306.SSD1306(19, 16, spidev.SpiDev(0, 0))
disp.begin()
image = Image.new('1', (disp.width, disp.height))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()

while True:
    temperature = "{:.2f} C".format(bmp.read_temperature())
    pressure = "{:.2f} hPa".format(bmp.read_pressure() / 100.0)
    altitude = "{:.2f} m".format(bmp.read_altitude())

    print(temperature, pressure, altitude)

    draw.rectangle((0,0,disp.width,disp.height), outline=0, fill=0)
    draw.text((2, 2), temperature, font=font, fill=255)
    draw.text((2, 2+20), pressure, font=font, fill=255)
    draw.text((2, 2+40), altitude, font=font, fill=255)
    disp.image(image)
    disp.display()

    time.sleep(1)
