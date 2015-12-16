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
  Purpose : Read values from a joystick and display the same on a 2x16
            line LCD module. LiquidCrystal library is used in this
            example. 4-pin mode is used for the LCD. Since RW pin is
            grounded, only write operation is possible.
  Date    : 16 Dec 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

#include <LiquidCrystal.h>

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define VREF 3300 // mV
#define ADC_MAX 4095
LiquidCrystal lcd(P2_0, P2_2, P2_5, P2_4, P1_5, P1_4); // RS, E, D4, D5, D6, D7
#else
#define VREF 1100 // mV
#define ADC_MAX 1023
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7
#endif

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  #ifndef LaunchPadF5529
  // Since Uno has only a 10-bit ADC, improve accuracy using internal 1.1V
  analogReference(INTERNAL);
  #endif
}

void loop()
{
  int xin = map(analogRead(A2), 0, ADC_MAX, 0, VREF);
  int yin = map(analogRead(A1), 0, ADC_MAX, 0, VREF);

  // For debugging
  Serial.print("Position (x, y): ");
  Serial.print(xin);
  Serial.print(", ");
  Serial.println(yin);
  
  lcd.clear(); // need to clear previous screen
  lcd.setCursor(0, 0);
  lcd.print("X: ");
  lcd.print(xin);
  lcd.setCursor(0, 1);
  lcd.print("Y: ");
  lcd.print(yin);

  delay(200);
}
