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
  Purpose : Put the Bluetooth module in AT command mode. Run a bunch of
            commands to configure the module. Module must be forced to
            enter AT command mode by long pressing the reset button
            before powering it up.
  Date    : 11 Mar 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define EN_PIN P2_0
#else
#define EN_PIN 9
#define BT_TX 2
#define BT_RX 3
#endif

// SoftwareSerial is used so that the usual Serial can be
// used for debugging. SoftwareSerial does not support 25MHz
// platforms such as LaunchPadF5529.
// Comment/uncomment as suitable since #include within #ifdef is not compiling!
// For LaunchPadF5529
// #define Bluetooth Serial1 // P3_4 and P3_3
// For ArduinoUno
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(BT_TX, BT_RX);

void setup()
{
  Serial.begin(9600);

  // This may be redundant since we are long pressing
  // reset button to put module into AT command mode
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);

  // Default baud rate in AT command mode
  Bluetooth.begin(38400);

  Serial.print("Waiting for AT commands ... ");
}

void loop()
{
  if (Bluetooth.available())
    Serial.write(Bluetooth.read());

  if (Serial.available())
      Bluetooth.write(Serial.read());
}

