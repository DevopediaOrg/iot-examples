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
  Purpose : Send commands from an Android device via Bluetooth to turn
            on/off or blink and LED. A suggested Android app is the
            Bluetooth SPP Tools Pro.
  Date    : 7 Jan 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define LED RED_LED // on-board, aka P1_0
#else
#define LED 13 // on-board
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

boolean ToBlink = false;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting... ");

  // Change this if your BT module is configured to a different rate
  // Or configured the BT module using AT commands
  Bluetooth.begin(38400);

  pinMode(LED, OUTPUT);

  Serial.println("done");
}

void loop()
{
  // Process commands received via BT
  if (Bluetooth.available()) {
    char dataFromBt = Bluetooth.read();
    Serial.print("Received from BT: 0x");
    Serial.println(dataFromBt, HEX);

    if (dataFromBt == '1') {
      Serial.println("Turning on...");
      digitalWrite(LED, HIGH);
      ToBlink = false;
    }
    else if (dataFromBt == '0') {
      Serial.println("Turning off...");
      digitalWrite(LED, LOW);
      ToBlink = false;
    }
    else if (dataFromBt == 'b') {
      Serial.println("Blinking...");
      ToBlink = true;
    }
  }

  // Send Serial commands to BT
  if (Serial.available()) {
    char buffer[64];
    int numBytes = Serial.readBytesUntil('\n', buffer, 63);
    buffer[numBytes] = 0;
    Bluetooth.println(buffer);
  }

  if (ToBlink) {
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
  }
}

