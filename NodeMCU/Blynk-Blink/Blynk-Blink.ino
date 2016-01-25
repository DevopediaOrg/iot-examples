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
  Purpose : Control an LED manually from the Blynk app. This code can
            be compiled and uploaded from Arduino IDE. Update the code
            with your token, Wi-Fi SSID and password.
  Date    : 25 Jan 2016
  Boards  : NodeMCU
  =====================================================================
*/

// Blynk:
// https://github.com/blynkkk/blynk-library/releases
// http://www.blynk.cc/

#define BLYNK_PRINT Serial    // Comment out to disable prints

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Get Auth Token in the Blynk App.
char auth[] = "xxx";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "xxx", "xxx");
}

void loop()
{
  Blynk.run();
}
