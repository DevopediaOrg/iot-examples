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
  Purpose : Control an LED using commands "on" or "off" received on the
            serial port. This is a simple illustration of how we can
            control the system remotely using the serial interface.
            Implementation assumes characters are buffered and sent
            together as a single command. This is the case with Arduino
            and Energia serial monitors. This won't work in Fritzing 
            serial monitor since characters are sent as soon as they 
            are typed.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define LED RED_LED // on-board, aka P1_0
#else
#define LED 13 // external
#endif

int incomingByte;

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop()
{
  String data = readSerialData();
  if (data.length()) {
    if (data.equalsIgnoreCase("on")) {
      digitalWrite(LED, HIGH);
    } 
    else if (data.equalsIgnoreCase("off")) {
      digitalWrite(LED, LOW);
    }
    Serial.println(data); // echo the command for debugging
  }
}

String readSerialData()
{
  char buffer[16];
  unsigned int count = 0;
  while (Serial.available() > 0) {
    buffer[count++] = Serial.read();
    delayMicroseconds(250); // enough time to detect end of transfer
  }
  buffer[count++] = 0;
  return String(buffer);
}
