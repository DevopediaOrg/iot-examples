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

/* Normal or alternate I2C address of the module */
#define I2C_Add 0x1D //0x53

/* ADXL345 register addresses */
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define X_Axis 0x32
#define Y_Axis 0x34
#define Z_Axis 0x36

/* Accelerometer range modes */
#define RANGE_2g 0
#define RANGE_4g 1
#define RANGE_8g 2
#define RANGE_16g 3

void setup()
{
  /* Initialise the I2C bus */
  Wire.begin(); 
 
  Serial.begin(9600);
 
  initADXL345(RANGE_2g);
}

void loop()
{
  Serial.print("X: ");
  Serial.print(readAxis(X_Axis));
 
  Serial.print(" Y: ");
  Serial.print(readAxis(Y_Axis));
 
  Serial.print(" Z: ");
  Serial.println(readAxis(Z_Axis));
  
  delay(100);
}

/* Read one of the 3 axis via the I2C interface */
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

/* Initialise the ADXL345 */
void initADXL345(byte range)
{
  Wire.beginTransmission(I2C_Add);
 
  /* Set the sensitivity of the module */
  Wire.write(DATA_FORMAT);
  Wire.write(range);
  Wire.endTransmission();
 
  /* Put the module into measurement mode to start taking measurements */
  Wire.beginTransmission(I2C_Add);
  Wire.write(POWER_CTL);
  Wire.write(0x08);
 
  Wire.endTransmission();
}