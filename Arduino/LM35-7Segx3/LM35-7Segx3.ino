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
  Purpose : Use LM35 to sense temperature that is displayed. 
            Use 74HC595 shift register to control 3 7-segment displays.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
#define LaunchPadF5529

#ifdef LaunchPadF5529
#define VREF 3300 // mV
#define AIN A5 // aka P6_5
#define ADC_MAX 4095
const int SCLK = P1_3, RCLK = P1_2, DATA = P2_5;
const int DIGIT1 = P2_0, DIGIT2 = P2_2, DIGIT3 = P7_4;
#else
#define VREF 1100 // mV
#define AIN A5 // aka 19
#define ADC_MAX 1023
const int SCLK = 2, RCLK = 3, DATA = 4;
const int DIGIT1 = 5, DIGIT2 = 6, DIGIT3 = 7;
#endif

// Ref. http://en.wikipedia.org/wiki/Seven-segment_display
// A abcdefgh configuration can be treated as gfedcba but shift bits from LSB to MSB!
char ledCodes[] = {
  //0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B // abcdefgh configuration: 0-9
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F // gfedcba configuration: 0-9
};

void clockPulse()
{
  digitalWrite(SCLK, HIGH);
  digitalWrite(SCLK, LOW);
  digitalWrite(RCLK, HIGH);
  digitalWrite(RCLK, LOW);
}

void setShiftRegister8bit(int code)
{
   for (int i = 0; i < 8; i++)
   {
     digitalWrite(DATA, (((1 << i) & code) != 0) ? HIGH : LOW);
     clockPulse(); 
   }
}

void flashDigit(int signalOutput, int delayTime = 1)
{
  digitalWrite(signalOutput, LOW); // common cathode: turn on LED
  delay(delayTime);
  digitalWrite(signalOutput, HIGH); // common cathode: turn off LED
}

void showDigit(int digitValue, int dot, int digitIndex)
{
  // All relevant segments are on at the same time  
  setShiftRegister8bit(ledCodes[digitValue] | dot<<7);
  flashDigit(digitIndex, 5);
}

void setup()
{
  #ifndef LaunchPadF5529
  // Since Uno has only a 10-bit ADC, improve accuracy using internal 1.1V
  analogReference(INTERNAL);
  #endif
  
  Serial.begin(9600); 
  
  pinMode(SCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(DIGIT3, OUTPUT);

  digitalWrite(DATA, LOW);
  digitalWrite(DIGIT1, HIGH);
  digitalWrite(DIGIT2, HIGH);
  digitalWrite(DIGIT3, HIGH);
  
  // Flash all segments of all digits
  // Caution: potentially high current draw!
  setShiftRegister8bit(0xFF);
  digitalWrite(DIGIT1, LOW);
  digitalWrite(DIGIT2, LOW); 
  digitalWrite(DIGIT3, LOW);  
  delay(1000);
  digitalWrite(DIGIT1, HIGH);
  digitalWrite(DIGIT2, HIGH);  
  digitalWrite(DIGIT3, HIGH);  
  
  // Flash each segment of each digit one at a time
  // Flashing in sequence abcdefgh
  for (int i = 0; i < 8; i++)
  {
    setShiftRegister8bit(1<<i);
    flashDigit(DIGIT1, 100);
    flashDigit(DIGIT2, 100);
    flashDigit(DIGIT3, 100);
    delay(100);
  }
}

int currTs = 0, lastTs = 0;
int lastReading = 0, part = 0;

void loop()
{
  currTs = millis();
  if (currTs - lastTs > 1000) { // Read sensor value once per second
    lastReading = map(analogRead(AIN),0,ADC_MAX,0,VREF); // 10mV => 1 degree C
    lastTs = currTs;
    Serial.println(lastReading); // for debugging
  }

  // All three digits are controlled by a single shift register.
  // Therefore, we cannot have any delay in the loop for flicker-free display.
  // To human vision, it will appear as though all three digits are
  // controlled at the same time. In reality, they are driven one by one.
  showDigit(lastReading / 100, 0, DIGIT1);
  part = lastReading % 100;
  showDigit(part / 10, 1, DIGIT2);
  showDigit(part % 10, 0, DIGIT3);
}
