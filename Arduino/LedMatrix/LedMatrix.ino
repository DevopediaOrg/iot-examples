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
  Purpose : Drive an 8x8 LED matrix without any IC.
  Date    : 13 Dec 2015
  Boards  : ArduinoUno
  =====================================================================
*/

// Adapted from:
// Arduino Cookbook by Michael Margolis. 2011. Section 7.8

// Wiring connections from uC to display: (below are pin numbers on display):
// Columns on LED (left to right): 13, 3, 4, 10, 6, 11, 15, 16
// Rows on LED (top to bottom): 5, 2, 7, 1, 12, 8, 14, 9
const int columnPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int rowPins[] = {19, 18, 17, 16, 15, 12, 11, 10};

#define ROW_CATHODE
#ifdef ROW_CATHODE
#define ROW_ON LOW
#define COL_ON HIGH
#else
#define ROW_ON HIGH
#define COL_ON LOW
#endif

byte bigHeart[] = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

byte smallHeart[] = {
  B00000000,
  B00000000,
  B00010100,
  B00111110,
  B00111110,
  B00011100,
  B00001000,
  B00000000
};

void show( byte * image, unsigned long duration) {
  unsigned long start = millis();
  while (start + duration > millis()) {
    for (int row = 0; row < 8; row++) {
      digitalWrite(rowPins[row], ROW_ON);
      for (int column = 0; column < 8; column++) {
        boolean pixel = bitRead(image[row], column);
        if (pixel == 1) {
          digitalWrite(columnPins[column], COL_ON); // make the circuit
        }
        delayMicroseconds(300);
        digitalWrite(columnPins[column], !COL_ON);
      }
      digitalWrite(rowPins[row], !ROW_ON);
    }
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], LOW);
  }
}

void loop() {
  show(smallHeart, 80);
  show(bigHeart, 160);
  delay(800);
}
