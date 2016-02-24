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
  Purpose : Use an IR receiver/decoder to decode and store commands
            from a household remote control. Use an IR LED to send the
            commands to the household gadget/appliance.
  Date    : 23 Feb 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
int rxPin = P2_0;
#else
int rxPin = 2;
#endif

// IRremote
// Source: https://github.com/z3t0/Arduino-IRremote/releases

#include <IRremote.h>

#define NumActions 2
decode_results actions[NumActions];
char printBuff[48];

IRrecv irrecv(rxPin);
IRsend irsend;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();

  trainTransmitter(NumActions);
}

void loop()
{
  if (Serial.available()) {
    int command = Serial.read() - 0x30; // ASCII to int
    if (command>0 && command<=NumActions) {
      Serial.print("Sending command: 0x");
      Serial.println(actions[command-1].value, HEX);

      // Change to another protocol depending on application
      // :can make use of decode_type to automate this
      irsend.sendNEC(actions[command-1].value, actions[command-1].bits);
      
      delay(100);
    }
  }
}

#ifdef LaunchPadF5529
class
#endif
decode_results receiveData()
{
  decode_results data;
  while (!irrecv.decode(&data));
  snprintf(printBuff, sizeof(printBuff), "[type %d, value 0x%lx, %d bits]", data.decode_type, data.value, data.bits);
  Serial.println(printBuff);
  irrecv.resume();
  return data;
}

boolean addToActions(int idx, decode_results data)
{
  // Add only if command is different from stored actions
  // Return: true if just added, false if ignored
  for (int i=0; i<idx; i++) {
    if (actions[i].value==data.value || data.decode_type==-1) {
      Serial.println("Skipping this command. Try again ...");
      return false;
    }
  }

  actions[idx] = data;
  Serial.println("Added this command.");
  return true;
}

void trainTransmitter(unsigned int numActions)
{
  for (int i=0; i<numActions; i++) {
    snprintf(printBuff, sizeof(printBuff), "Action %d: press remote control's button ... ", i+1);
    Serial.println(printBuff);
    while (!addToActions(i, receiveData()));
  }

  Serial.println("Transmitter trained. Ready to use as remote control.");
}

