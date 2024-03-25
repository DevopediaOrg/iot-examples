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
  Purpose : Tetris game is implemented. Display uses the MAX7219 FC16
            module that cascades four 8x8 dot matrix displays. For user
            control, we use four pushbuttons. The displays should be 
            powered by an independent power supply and not from the
            Arduino.
  Date    : 25 Mar 2024
  Boards  : ArduinoUno
  =====================================================================
*/
#include <MD_MAX72xx.h>
#include "Common.h"
#include "Tetrimino.h"
#include "DotMatrixBoard.h"
#include "KeypadReader.h"

// TODO Possible game improvements:
// - Reduce tick and factor for faster play at higher levels
// - Display score and Game Over message to user
// - Add sounds

unsigned long lastTs = 0;
unsigned long counter = 0;
int tick = 100;
int factor = 5;
DotMatrixBoard* dm;
KeypadReader kpr;

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));
  kpr.setPins(3, 4, 5, 6);
}

void loop()
{
  bool toPrint = false;

  unsigned long nowTs = millis();
  if (nowTs - lastTs < tick) return;
  lastTs = nowTs;
  counter++;
  #ifdef DEBUG
  Serial.print("Counter: "); Serial.println(counter);
  #endif

  if (dm == NULL) {
    dm = new DotMatrixBoard(32, 8);
    dm->setPins(11, 10, 13);
    #ifdef DEBUG
    dm->testPrint(true);
    delay(1000);
    dm->testPrint(false);
    #endif
  }

  String cmd = kpr.read();
  if (cmd.length() > 0) {
    #ifdef DEBUG
    Serial.print("Cmd: "); Serial.println(cmd);
    #endif
    dm->processCmd(cmd);
    toPrint = true;
  }

  if (counter % factor == 0) {
    #ifdef DEBUG
    Serial.println("Fall");
    #endif
    dm->updateFall();
    toPrint = true;
  }

  if (toPrint) dm->print();

  if (dm->isGameOver()) {
    Serial.println("Game Over!\n");
    delete dm;
    dm = NULL;
    while (true) { }
  }
}
