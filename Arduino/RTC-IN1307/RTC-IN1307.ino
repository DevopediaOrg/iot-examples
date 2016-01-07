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
  Purpose : Interface to Real-Time Clock (RTC) chip IN1307, which has
            an I2C interface. DS1307 is an equivalent chip but is not
            tested with this code. Code allows users to set the time
            via UART. RTClib is used in this code.
  Date    : 07 Jan 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// RTClib:
// https://github.com/jcw/RTClib

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void printDateTime(DateTime inDt)
{
  Serial.print(inDt.day(), DEC);
  Serial.print('/');
  Serial.print(inDt.month(), DEC);
  Serial.print('/');
  Serial.print(inDt.year(), DEC);
  Serial.print(' ');
  Serial.print(inDt.hour(), DEC);
  Serial.print(':');
  Serial.print(inDt.minute(), DEC);
  Serial.print(':');
  Serial.print(inDt.second(), DEC);  
}

DateTime* readInputTime()
{
  // Default Energia distribution has SERIAL_BUFFER_SIZE set to 16
  // in hardware/msp430/cores/msp430/HardwareSerial.cpp
  // Change this to 64 so that at least 19 bytes can be stored in Serial buffer

  int dd, mm, yyyy, hh, ii, ss;

  // dd/mm/yyyy hh:ii:ss in 24-hour format
  // Use 24/03/2016 11:22:33, not 24/3/2016 11:22:33
  while (Serial.available()){
    dd = Serial.parseInt();
    mm = Serial.parseInt();
    yyyy = Serial.parseInt();
    hh = Serial.parseInt();
    ii = Serial.parseInt();
    ss = Serial.parseInt();
    DateTime *dt = new DateTime(yyyy, mm, dd, hh, ii, ss);
    return dt;
  }
  return NULL;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  delay(100);
  while (!RTC.isrunning()) {
    Serial.println(F("RTC is NOT running. Clearing CH bit ..."));
    RTC.writeByteInRam(0, 0); // Clear CH bit
    delay(100);

    // For a start, set time based on when this code was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop()
{
  // Read time as user input via UART
  DateTime *startDt = readInputTime();
  if (startDt) RTC.adjust(*startDt);

  // Get current time and print it in regular intervals  
  DateTime currDt = RTC.now();
  printDateTime(currDt);
  Serial.println();
  delay(1000);
}

