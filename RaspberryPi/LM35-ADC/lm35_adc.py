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
  Purpose : Interface Raspberry Pi with MCP3008 for ADC functionality.
            LM35 temperature sensor is connected to CH1 of MCP3008.
            MCP3008 is powered with 3.3V.
            If environment variable TS_API_KEY is set, data is sent to
            the ThingSpeak IoT cloud. REST API is used.
  Date    : 14 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''


import os
import spidev
from tsconn import ThingSpeakConnector
from time import sleep


def adc_read(channel):
    raw_data = spi.xfer([1, (8 + channel) << 4, 0])
    processed_data = ((raw_data[1] & 3) << 8) + raw_data[2]
    return processed_data


def adc2voltage(adc_val, precision=2):
    voltage = (adc_val * 3.3) / float(1023)
    voltage = round(voltage, precision)
    return voltage


def adc2celsius(adc_val, precision=2):
    # 10-bit ADC, 3.3V supply, 10 mV/deg C
    temperature = ((adc_val * 330) / float(1023))
    temperature = round(temperature, precision)
    return temperature


spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 5000

adc_channel = 1

tspeak = None
if os.environ['TS_API_KEY']:
    tspeak = ThingSpeakConnector(os.environ['TS_API_KEY'])

while True:
    adc_temperature = adc_read(adc_channel)
    voltage = adc2voltage(adc_temperature)
    temperature = adc2celsius(adc_temperature)
    print("adc_val = {}; voltage = {} V; temperature = {} C".format(adc_temperature, voltage, temperature))

    # Send data to ThingSpeak IoT cloud
    if tspeak:
        tspeak.send(temperature)

    sleep(1)