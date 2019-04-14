/*=====================================================================
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
  Purpose : Use LM35 to sense temperature that is displayed. 
            External ADC 10-bit MCP3008 is used and read by Arduino
            via SPI.
  Date    : 14 Apr 2019
  Boards  : ArduinoUno 
  =====================================================================
*/

#include <MCP3XXX.h>

MCP3008 adc;

void setup()
{
  Serial.begin(9600);
  adc.begin();
}

void loop()
{
  unsigned int adcValue = adc.analogRead(0);
  float temperature = adcValue * 500 / 1023;
  Serial.print(adcValue);
  Serial.print(" ");
  Serial.println(temperature);
  delay(1000);
}
