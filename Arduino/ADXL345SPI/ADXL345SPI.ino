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

char POWER_CTL = 0x2D;
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32;
char DATAX1 = 0x33;
char DATAY0 = 0x34;
char DATAY1 = 0x35;
char DATAZ0 = 0x36;
char DATAZ1 = 0x37;

char values[10];
int x,y,z;

void setup(){ 
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  Serial.begin(9600);
  
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  
  writeRegister(DATA_FORMAT, 0x00); // -+2g
  writeRegister(POWER_CTL, 0x08);  //Measurement mode  
}

void loop(){
  // Reading 6 bytes of data starting at register DATAX0 will retrieve 
  // the x,y and z acceleration values from the ADXL345.
  readRegister(DATAX0, 6, values);

  // 10-bit acceleration values stored across 2 bytes.
  x = ((int)values[1]<<8)|(int)values[0];
  y = ((int)values[3]<<8)|(int)values[2];
  z = ((int)values[5]<<8)|(int)values[4];
  
  Serial.print(x, DEC);
  Serial.print(',');
  Serial.print(y, DEC);
  Serial.print(',');
  Serial.println(z, DEC);      
  delay(200); 
}

//This function will write a value to a register on the ADXL345.
//Parameters:
//  char registerAddress - The register to write a value to
//  char value - The value to be written to the specified register.
void writeRegister(char registerAddress, char value){
  digitalWrite(CS, LOW);
  SPI.transfer(registerAddress);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);

  #ifndef LaunchPadF5529
  //delay(100); // may be required on Arduino Uno
  #endif
}

//This function will read a certain number of registers starting from a specified address and store their values in a buffer.
//Parameters:
//  char registerAddress - The register addresse to start the read sequence from.
//  int numBytes - The number of registers that should be read.
//  char * values - A pointer to a buffer where the results of the operation should be stored.
void readRegister(char registerAddress, int numBytes, char * values){
  //Since we're performing a read operation, the most significant bit of the register address should be set.
  char address = 0x80 | registerAddress;
  //If we're doing a multi-byte read, bit 6 needs to be set as well.
  if(numBytes > 1) address = address | 0x40;
  
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  for(int i=0; i<numBytes; i++){
    values[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS, HIGH);

  #ifndef LaunchPadF5529
  //delay(100); // may be required on Arduino Uno
  #endif
}