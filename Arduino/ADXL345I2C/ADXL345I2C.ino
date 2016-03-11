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
  Purpose : Interface to the ADXL345 accelerometer via I2C.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno
  =====================================================================
*/

#include <Wire.h>

// ALT ADDRESS (SDO) HIGH: 0x1D
// ALT ADDRESS (SDO) LOW: 0x53
#define I2C_Add 0x1D

// ADXL345 register addresses
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define DATAX 0x32
#define DATAY 0x34
#define DATAZ 0x36

#define FULL_RES 0x08

enum {
  Range_2g = 0,
  Range_4g,
  Range_8g,
  Range_16g
} Range;

void setup()
{
  Wire.begin(); 
 
  Serial.begin(115200);
 
  initADXL345(Range_16g);
}

void loop()
{
  Serial.print("X: ");
  Serial.print(readAxis(DATAX));
  Serial.print(" Y: ");
  Serial.print(readAxis(DATAY));
  Serial.print(" Z: ");
  Serial.println(readAxis(DATAZ));

  delay(100);
}

int readAxis(byte axis)
{
  int data;
   
  Wire.beginTransmission(I2C_Add);
  Wire.write(axis);
  Wire.endTransmission();
 
  Wire.beginTransmission(I2C_Add);
  Wire.requestFrom(I2C_Add, 2);
 
  if (Wire.available()) {
    data = (int)Wire.read();
    data = data | (Wire.read() << 8);
  }
  else {
    data = 0;
  }
   
  Wire.endTransmission(); 

  return data;
}

void initADXL345(byte range)
{
  Wire.beginTransmission(I2C_Add);
 
  // Configure the sensor
  Wire.write(DATA_FORMAT);
  Wire.write(FULL_RES | range);
  Wire.endTransmission();
 
  // Start measurements
  Wire.beginTransmission(I2C_Add);
  Wire.write(POWER_CTL);
  Wire.write(0x08);
 
  Wire.endTransmission();
}
