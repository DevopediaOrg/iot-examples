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
  Purpose : Use analog input to read temperature measurement from LM35.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define VREF 3300 // mV
#define AIN A5 // aka P6_5
#define ADC_MAX 4095
#else
#define VREF 1100 // mV
#define AIN A5 // aka 19
#define ADC_MAX 1023
#endif

void setup()
{
  Serial.begin(9600);

  #ifndef LaunchPadF5529
  // Since Uno has only a 10-bit ADC, improve accuracy using internal 1.1V
  analogReference(INTERNAL);
  #endif
}

void loop()
{
  float temperature = (VREF*0.1*analogRead(AIN))/(ADC_MAX+1); // 10mV => 1 degree C
  Serial.print("Temperature is ");
  Serial.print(temperature, 1);
  Serial.println(" degree Celsius.");

  // Avoid float to reduce code size
  /*
  int temperature = map(analogRead(AIN), 0, ADC_MAX, 0, VREF); // 10mV => 1 degree C
  Serial.print("Temperature is ");
  Serial.print(temperature / 10);
  Serial.print(".");
  Serial.print(temperature % 10);
  Serial.println(" degree Celsius.");
  */
  
  delay(1000);
}