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
  Purpose : Use MQ2 gas sensor module and read analog values. The code
            also includes calibration. Since the mapping betweeen Rs
            and PPM is non-linear no conversion to PPM is done at the
            moment. No compensation has been included for current
            humidity and temperature.
  Date    : 10 Feb 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define VREF 3300L // mV
#define AIN A5 // aka P6_5
#define ADC_MAX 4095
#else
#define VREF 5000L // mV
#define AIN A5 // aka 19
#define ADC_MAX 1023
#endif

// Source: http://www.seeedstudio.com/wiki/Grove_-_Gas_Sensor%28MQ2%29
// This code is adapted from the above source but calculations are wrong.
// Next version will correct this.

unsigned long Ro; // sensor resistance: H2 1000ppm in clean air

unsigned long averager(int pin, unsigned int numSamples) {
  unsigned long sum = 0L;
  for(int i = 0; i < numSamples; i++) {
    sum += analogRead(pin);
    delay(1);
  }
  return sum/numSamples;
}

void calibrate() {
  unsigned long voltage = VREF*averager(AIN, 100)/(ADC_MAX+1);
  unsigned long Rs_air = 100L*(VREF-voltage)/voltage; // scale by 100
  Ro = Rs_air*10/98; // comes from MQ2 datasheet
  Serial.print("Calibrated Ro (x100): ");
  Serial.println(Ro);
}

void setup() {
  Serial.begin(9600);
  calibrate(); // should be done in clean conditions
}
 
void loop() {
  unsigned long voltage = VREF*analogRead(AIN)/(ADC_MAX+1);
  
  if (voltage) {
    unsigned long Rs = 100L*(VREF-voltage)/voltage; // scale by 100
    unsigned long ratio = Rs*100L/Ro;
  
    Serial.print("Voltage = ");
    Serial.print(voltage);
    Serial.print("mv; Rs (x100) = ");
    Serial.print(Rs);
    Serial.print("; Ratio (x100) = ");
    Serial.println(ratio);
  }
  
  delay(1000);
}
