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
  Purpose : Detect door open/close events using a reed switch.
						This example shows how to write interrupt code.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
int reedSwitch = P2_4; // pins of P1 and P2 are interrupt capable
#else
// Ref. https://www.arduino.cc/en/Reference/AttachInterrupt
int reedSwitch = 2; // pins 2 and 3 are interrupt capable on Uno
#endif

boolean prevDoorOpen = false;

// We use volatile because variables are changed within ISR.
// Compiler will not optimize volatile variables.
volatile boolean doorOpen = false;
volatile boolean stateChange = false;
volatile int interruptTs = 0;

void setup() {
  Serial.begin(115200);
  pinMode(reedSwitch, INPUT_PULLUP);

  #ifdef LaunchPadF5529
  attachInterrupt(reedSwitch, onDoorOpen, CHANGE);
  #else
  attachInterrupt(digitalPinToInterrupt(reedSwitch), onDoorOpen, CHANGE);
  #endif
}

void loop() {
  if (stateChange) {
    if (doorOpen) {
      Serial.println("\nSomeone has opened the door!");
    }
    else {
      Serial.println("\nSomeone has closed the door!");
    }
    stateChange = false;
  }
}

void onDoorOpen() {
  // software debouncing: 0 ms to bypass
  if ((long)(millis() - interruptTs) >= 0) {
    interruptTs = millis();

		// Note the state, print later.
    // Serial cannot be used here since further
    // interrupts are disabled within an ISR.
		// It is also good design to do minimal stuff
    // within ISR.
    stateChange = true;
    doorOpen = digitalRead(reedSwitch);
  }
}
