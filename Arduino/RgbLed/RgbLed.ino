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
  Purpose : Change colours on an RGB LED. PWM is used to control the
            colours. Hence, pins must be capable of PWM out.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define R_LED P2_5
#define G_LED P2_4
#define B_LED P1_5
#else
#define R_LED 3
#define G_LED 5
#define B_LED 6
#endif

void setup() {                
}

void loop() {
  // Use sin() to obtain smooth transitions: to keep the channels
  // out of phase, add an arbitrary phase offset.
  // For abrupt transitions, try random(255)
  for (unsigned char i=0; i<256; i+=5) {
    analogWrite(R_LED, map(1000*sin(i*2*PI/255),-1000,1000,255,0));
    analogWrite(G_LED, map(1000*sin(2+i*2*PI/255),-1000,1000,255,0));
    analogWrite(B_LED, map(1000*sin(4+i*2*PI/255),-1000,1000,255,0));
    delay(10);
  }
}