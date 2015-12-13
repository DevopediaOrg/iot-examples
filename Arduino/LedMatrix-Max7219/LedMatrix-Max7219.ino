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
  Purpose : Drive one or more 8x8 LED matrices using MAX7219. SPI is
            is used for interfacing. Two variants are presented below:
            0: From first principles.
            1: Two 8x8 matrices using LedControl library.
  Date    : 12 Dec 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
#define LaunchPadF5529

#define NUM_DEV 2 // number of matrices

void setup()
{
  setup0(); // modify this to try different implementations
}

void loop()
{
  loop0(); // modify this to try different implementations
}


//=====================================================================
#ifdef LaunchPadF5529
int Max7219_pinCLK = P3_2;
int Max7219_pinCS = P2_6;
int Max7219_pinDIN = P3_0;
#else
int Max7219_pinCLK = 13;
int Max7219_pinCS = 10;
int Max7219_pinDIN = 11;
#endif

unsigned char pattern[21][8]={
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x80, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x40, 0x80, 0x80, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x60, 0x80, 0x80, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x60, 0x90, 0x80, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x60, 0x90, 0x88, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x60, 0x90, 0x88, 0x44, 0x40, 0x00, 0x00, 0x00, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x00, 0x00, 0x00, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x08, 0x00, 0x00, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x08, 0x10, 0x00, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x08, 0x10, 0x20, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x08, 0x10, 0x60, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x08, 0x90, 0x60, 
  0x60, 0x90, 0x88, 0x44, 0x44, 0x88, 0x90, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // transpose rows and columns for effect! 
  0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00
};

void Write_Max7219_byte(unsigned char DATA) 
{   
  for(int i=0; i<8; i++)
  {    
    digitalWrite(Max7219_pinCLK, LOW);
    digitalWrite(Max7219_pinDIN, DATA & 0x80); // MSB first: send out the most significant bit
    DATA = DATA<<1;
    digitalWrite(Max7219_pinCLK, HIGH); // on rising edge, data will be read: CPOL = CPHA = 0
  }                                 
}

void Write_Max7219(unsigned char address, unsigned char dat)
{
  digitalWrite(Max7219_pinCS, LOW);
  for (int i=0; i<NUM_DEV; i++) {
    // Repeat the same data for all devices
    Write_Max7219_byte(address);
    Write_Max7219_byte(dat);
  }
  digitalWrite(Max7219_pinCS, HIGH);
}

void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00); // decode mode: none  
  Write_Max7219(0x0a, 0x03); // intensity: 7/32 duty cycle
  Write_Max7219(0x0b, 0x07); // scan limit: all digits
  Write_Max7219(0x0c, 0x01); // shutdown: normal mode
  Write_Max7219(0x0f, 0x00); // testing: normal mode
}

void setup0()
{

  pinMode(Max7219_pinCLK, OUTPUT);
  pinMode(Max7219_pinCS, OUTPUT);
  pinMode(Max7219_pinDIN, OUTPUT);
  delay(50);
  Init_MAX7219();

  // Light up everything as a test
  Write_Max7219(0x0f, 0x01); // testing mode
  delay(1000);
  Write_Max7219(0x0f, 0x00); // normal mode
}

void loop0()
{ 
  for (int j=0; j<sizeof(pattern)/8; j++) {
    for (int i=0; i<8; i++) {
      Write_Max7219(i+1, pattern[j][i]); // digit x addressed as x+1
    }
    delay(500);
  }   
}


//=====================================================================
// LedControl:
// https://github.com/arvindpdmn/LedControl
// http://playground.arduino.cc/Main/LedControl

#include "LedControl.h"

#ifdef LaunchPadF5529
LedControl lc = LedControl(P3_0, P3_2, P2_6, NUM_DEV);  // DIN, CLK, CS, #Dev
#else
LedControl lc = LedControl(11, 13, 10, NUM_DEV);  // DIN, CLK, CS, #Dev
#endif

unsigned int FrameDelay = 200;

byte Invader1[] =
{
  // Frame 1  
  B00011000,
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B10100101,
  // Frame 2
  B00011000,
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte Invader2[] =
{
  // Frame 1  
  B00100100,
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100,
  // Frame 2
  B00100100,
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};

byte * Invaders[] = {
  Invader1, Invader2
};
unsigned int NumFrames = sizeof(Invader1)/(sizeof(byte)<<3);

void display_invader(unsigned int devid, byte *data)
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(devid, i, data[i]);
  }
}

void setup1()
{
  lc.init();
  for (int i = 0; i < NUM_DEV; i++) {
    lc.shutdown(i, false);  // wakeup display
    lc.setIntensity(i, 3); // 7/32 duty cycle
    lc.clearDisplay(i);  // clear display
  }
}

void loop1()
{
  for (int j=0; j < NumFrames; j++) { 
    for (int i=0; i < NUM_DEV; i++) { 
      display_invader(i, Invaders[i] + 8*j);
    }
    delay(FrameDelay);
  }
}


