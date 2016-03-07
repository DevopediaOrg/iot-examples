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
  Purpose : LDR is a light dependant resistor. Read the analog voltage
            across the LDR and derive the resistance.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define AIN A5 // aka P6_5
#define ADC_MAX 4095
#else
#define AIN A5 // aka 19
#define ADC_MAX 1023
#endif

#define R1 10 // in kilo-ohms
#define Vcc 3300 // in mV

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(AIN);
  unsigned int voltage = map(value, 0, ADC_MAX, 0, 3300);
  unsigned int resistance = voltage*R1/(Vcc-voltage); // comes from voltage divider concept
  
  Serial.print("Value: ");
  Serial.print(value);
  Serial.print("; Voltage (mV): ");
  Serial.print(voltage);
  Serial.print(" of ");
  Serial.print(Vcc);
  Serial.print("; Resistance (kilo-ohms): ");
  Serial.println(resistance);

  delay(1000);
}
