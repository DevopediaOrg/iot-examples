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
  Purpose : Control servo movement using push buttons.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define PB1 PUSH1 // on-board, aka P2_1
#define PB2 PUSH2 // on-board, aka P1_1
#define CTRL P1_4
#else
#define PB1 2 // external
#define PB2 3 // external
#define CTRL 9
#endif

#include <Servo.h>
 
Servo myservo; // a maximum of eight servo objects can be created

int pos = 0;
 
void setup()
{
  myservo.attach(CTRL);
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);

  #ifdef LaunchPadF5529
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  #endif

  sweep(); // test the full range once
}
 
 
void loop()
{
  pushbuttons();
}

void pushbuttons()
{
  if (!digitalRead(PB1)) {
    pos -= 5;
    delay(15);

    #ifdef LaunchPadF5529
    digitalWrite(RED_LED, HIGH);
    delay(100);
    digitalWrite(RED_LED, LOW);
    #endif
  }
  else if (!digitalRead(PB2)) {
    pos += 5;
    delay(15);

    #ifdef LaunchPadF5529
    digitalWrite(GREEN_LED, HIGH);
    delay(100);
    digitalWrite(GREEN_LED, LOW);
    #endif
  }

  if (pos>179) pos = 179;
  else if (pos<0) pos = 0;
  myservo.write(pos);
}

void sweep()
{
  for (pos = 0; pos < 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos>=1; pos -= 1) {                                
    myservo.write(pos);
    delay(15);
  }
}
