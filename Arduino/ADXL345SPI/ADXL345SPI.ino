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
  Purpose : Interface to the ADXL345 accelerometer via SPI.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
int CS = P2_7;
#else
int CS = 10;
#endif

#include <SPI.h>

// ADXL345 register addresses
#define BW_RATE 0x2C
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define DATAX 0x32
#define DATAY 0x34
#define DATAZ 0x36

#define FULL_RES 0x08
#define READ_OP 0x80
#define MULTIBYTE_READ 0x40
#define MEASURE_MODE 0x08

enum {
  Range_2g = 0,
  Range_4g,
  Range_8g,
  Range_16g
} Range;

void setup()
{ 
  Serial.begin(115200);
  
  initADXL345(Range_16g);
}

void loop()
{
  char values[6];
  int x,y,z;

  // Reading 6 bytes of data starting at register DATAX0 will retrieve 
  // the x, y and z acceleration values from the ADXL345.
  readRegister(DATAX, 6, values);

  // 13-bit acceleration values stored across 2 bytes.
  x = ((int)values[1]<<8)|(int)values[0];
  y = ((int)values[3]<<8)|(int)values[2];
  z = ((int)values[5]<<8)|(int)values[4];
  
  Serial.print("X: ");
  Serial.print(x, DEC);
  Serial.print(" Y: ");
  Serial.print(y, DEC);
  Serial.print(" Z: ");
  Serial.println(z, DEC);

  delay(500); 
}

void initADXL345(byte range)
{
  #ifdef LaunchPadF5529
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  #else
  SPI.begin();
  #endif
  
  // We use SPI in 4-wire mode
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  writeRegister(BW_RATE, 0x0D); // 800 Hz o/p, 400 Hz BW
  writeRegister(DATA_FORMAT, FULL_RES | range);
  writeRegister(POWER_CTL, MEASURE_MODE);  
}

void writeRegister(char registerAddress, char value)
{
  #ifndef LaunchPadF5529
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  #endif

  digitalWrite(CS, LOW);
  SPI.transfer(registerAddress);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);

  #ifndef LaunchPadF5529
  SPI.endTransaction();
  delay(10); // may be required on Arduino Uno
  #endif
}

void readRegister(char registerAddress, int numBytes, char * values)
{
  char address = READ_OP | registerAddress;
  if(numBytes > 1) address = MULTIBYTE_READ | address;
  
  #ifndef LaunchPadF5529
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  #endif

  digitalWrite(CS, LOW);
  SPI.transfer(address);
  for(int i=0; i<numBytes; i++){
    values[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS, HIGH);
  
  #ifndef LaunchPadF5529
  SPI.endTransaction();
  delay(10); // may be required on Arduino Uno
  #endif
}
