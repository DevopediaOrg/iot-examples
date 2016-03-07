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
  Purpose : FC04 sound sensor is to read an analog value. Value is
            used to drive an LED array that is supposed to light up to
            indicate sound loudness. This sensor responds well to base
            sounds (low frequency bands). In any case, adjust the
            trimmer on the module to suit your application.
  Date    : 08 Feb 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
const int leds[] = {P2_5, P2_4, P1_5, P1_4, P1_3, P1_2};
const int thresholds[] = {4000, 3700, 3000, 2400, 1200, 500};
#else
const int leds[] = {2, 3, 4, 5, 6, 7};
const int thresholds[] = {620, 560, 480, 400, 300, 200};
#endif

void setup()
{
  Serial.begin(9600);
  for (int i=0; i<sizeof(leds)/sizeof(int); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  int sensorValue = analogRead(A2);
  
  // Enable only for debugging: this will add delay to the loop
  // Serial.println(sensorValue);

  for (int i=0; i<sizeof(leds)/sizeof(int); i++) {
    if (sensorValue<thresholds[i]) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW);
  }
  
  delay(1);
}

