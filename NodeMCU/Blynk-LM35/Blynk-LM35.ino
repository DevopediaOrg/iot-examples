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
  Purpose : Send temperature readings from LM35 and display the same
            on the Blynk app.
  Date    : 14 Mar 2016
  Boards  : NodeMCU
  =====================================================================
*/

// Blynk:
// https://github.com/blynkkk/blynk-library/releases
// http://www.blynk.cc/

#define BLYNK_PRINT Serial    // Comment this out to disable prints

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

char auth[] = "xxx";

int adcPin = 17;
float temperature;
SimpleTimer timer;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "xxx", "xxx");

  // Timer-based callback
  timer.setInterval(1000L, sendReadings);
}

void sendReadings()
{
  Blynk.virtualWrite(10, temperature); // virtual pin 10
}

void loop()
{
  Blynk.run();
  timer.run();
  
  unsigned int adcValue = analogRead(adcPin);
  temperature = adcValue * 330 / 1024; // 3.3 VREF, 10-bit ADC, 10mV = 1 degree Celsius

  // Just for debugging
  Serial.print("ADC value: ");
  Serial.print(adcValue);
  Serial.print("; Current temperature (Celsius): ");
  Serial.println(temperature);
}

