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
  Purpose : Investigate the effect of pressing a push button by reading
            the voltage as a digital value. The value is printed on the
            serial monitor but also used to light up an LED.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
const int pushButton = P1_1; // on-board
const int led = RED_LED; // on-board
#else
const int pushButton = 2; // external
const int led = 13; // on-board
#endif

void setup()
{
  Serial.begin(9600);

  #ifdef LaunchPadF5529
  pinMode(pushButton, INPUT_PULLUP);
  #else
  pinMode(pushButton, INPUT);
  #endif

  pinMode(led, OUTPUT);
}

void loop()
{
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  digitalWrite(led, buttonState);
  delay(100); // delay in between reads for stability
}
