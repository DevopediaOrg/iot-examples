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
  Purpose : Use an IR LED and an IR photodiode to detect proximity of
            an obstable. An indicator LED glows in response to the
            proximity of the obstacle. This indicator can be programmed
            as a digital or an analog output.
  Date    : 16 Feb 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define IRIN A5
#define LedIndicator P2_0
#else
#define IRIN A5
#define LedIndicator 5
#endif

// Default is an LED with varying brightness
// #define UseDigitalLed

unsigned int RefHighValue = 0;
unsigned int RefLowValue = 0;

unsigned int calibrate(unsigned int numSamples) {
  unsigned long sum = 0L;
  for (int i=0; i<numSamples; i++) {
    sum += analogRead(IRIN);
  }
  return sum/numSamples;  
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LedIndicator, OUTPUT);
  #ifdef UseDigitalLed
  digitalWrite(LedIndicator, LOW);
  #else
  analogWrite(LedIndicator, 0);
  #endif

  RefHighValue = calibrate(100);
  Serial.print("Calibrated ADC high value (no obstacles): ");
  Serial.println(RefHighValue);

  Serial.println("Place obstacle and press enter to calibrate ...");
  while (!Serial.available()); // block till something is received
  while (Serial.available()) Serial.read(); // read all available bytes one by one
  RefLowValue = calibrate(100);
  Serial.print("Calibrated ADC low value (very close obstacle): ");
  Serial.println(RefLowValue);
}

void loop() {
  unsigned int readVal = analogRead(IRIN);
  int ledVal;
  
  #ifdef UseDigitalLed
  if (readVal < RefLowValue+(RefHighValue-RefLowValue)/2) ledVal = HIGH;
  else ledVal = LOW;
  digitalWrite(LedIndicator, ledVal);
  #else
  ledVal = map(readVal, RefLowValue, RefHighValue, 255, 0);
  if (ledVal<0) ledVal = 0;
  else if (ledVal>255) ledVal = 255;
  analogWrite(LedIndicator, ledVal);
  #endif

  // For debugging: comment out for more responsive behaviour
  Serial.print(readVal);
  Serial.print(" --> ");
  Serial.println(ledVal);

  delay(10);
}

