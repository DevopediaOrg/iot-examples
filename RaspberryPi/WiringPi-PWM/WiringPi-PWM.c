'''=====================================================================
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
  Purpose : Use WiringPi C library to fade an LED using hardware PWM.
            Compile as "gcc WiringPi-PWM.c -o pwm -Wall -lwiringPi"
            or use the Makefile, "make all"
            Run as "sudo ./pwm"
  Date    : 21 Apr 2019
  Boards  : Raspberry Pi 2, 3
=====================================================================
'''

// Code adapted from:
// https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// WiringPi numbering: 1 (GPIO18), 26 (GPIO12), 22 (GPIO18), 23 (GPIO19)
// Found to work only on pins 1 and 26
// Official documentation claims support for only pin 1
const int LEDPIN = 1; 

int main(void) {
    int intensity ;

    if(wiringPiSetup() == -1) exit(1) ;

    pinMode(LEDPIN, PWM_OUTPUT) ;

    while(1) {
        for(intensity = 0; intensity < 1024 ; ++intensity) {
            pwmWrite(LEDPIN, intensity) ;	/* provide PWM value for duty cycle */
            delay(1) ;
        }
        delay(1);

        for(intensity = 1023 ; intensity >= 0 ; --intensity) {
            pwmWrite(LEDPIN, intensity) ;
            delay(1) ;
        }
        delay(1);
    }
}
