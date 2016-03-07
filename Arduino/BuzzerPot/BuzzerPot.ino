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
  Purpose : Using a potentiometer, drive a buzzer. We illustrate two
            variations:
            DIRECT   : Buzzer is directly connected to potentiometer.
            WITH_PWM : Buzzer is sampled by microcontroller, which then
                       uses PWM to drive the buzzer.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define VREF 3300 // mV
#define AIN A3 // aka P6_3
#define ADC_MAX 4095
#define BUZZER_OUT P2_4
#else
#define VREF 5000 // mV
#define AIN A5 // aka 17
#define ADC_MAX 1023
#define BUZZER_OUT 3
#endif

// Variation: Drive buzzer via PWM: change the wiring first
//#define WITH_PWM

// Variation: Change the tone rather than loudness when WITH_PWM is defined
//#define VARY_TONE

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(AIN);
  int voltage = map(sensorValue, 0, ADC_MAX, 0, VREF); // for debugging

  #if defined(WITH_PWM)
  int writeOut = map(sensorValue, 0, ADC_MAX, 0, 255);
  analogWrite(BUZZER_OUT, writeOut);
  #elif defined(VARY_TONE)
  int toneOut = map(sensorValue, 0, ADC_MAX, 100, 15000);
  tone(BUZZER_OUT, toneOut);
  #endif

  Serial.print(sensorValue);
  Serial.print("\t");
  Serial.print(voltage);
  #if defined(WITH_PWM)
  Serial.print("\t");
  Serial.println(writeOut);
  #elif defined(VARY_TONE)
  Serial.print("\t");
  Serial.println(toneOut);
  #else
  Serial.println("");
  #endif

  delay(200); // delay in between reads for stability
}
