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
  Purpose : Drive an LED strip using Darlington array ULN2003. PWM is
            used to control the colours. Hence, pins must be capable
            of PWM out. Two implementations are illustrated.
  Date    : 16 Dec 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

typedef struct {
  int pin;
  long calibration;
} ColourLine;

#ifdef LaunchPadF5529
#define R_LINE P2_5
#define G_LINE P2_4
#define B_LINE P1_5
#else
#define R_LINE 3
#define G_LINE 5
#define B_LINE 6
#endif

#define COLOUR_DELAY 3
#define HUE_MAX  6.0
#define HUE_DELTA 0.01

ColourLine rgb[3] = {
  { R_LINE, 100 },
  { G_LINE, 256 },
  { B_LINE, 200 }
};
float hue=0.0, saturation=1, value=1;

void setup () {
  for (int k=0; k<3; k++) {
    analogWrite(rgb[k].pin, rgb[k].calibration);
  }
  delay(1000);
}

void loop() {
  loop0(); // update this to use alternative implementations
}


// ================================================================================================
// An implementation that changes colours using HSV
// ================================================================================================
void loop0() {
  hue += HUE_DELTA;
  if (hue > HUE_MAX) hue=0.0;

  long rgbval = HSV_to_RGB(hue, saturation, value);
  for (int k=0; k<3; k++) {
    analogWrite(rgb[k].pin, ((rgbval>>(8*(2-k))) & 0xFF) * rgb[k].calibration/256);
  }
      
  delay(COLOUR_DELAY);
}

long HSV_to_RGB( float h, float s, float v ) {
  // Source: http://www.jerome-bernard.com/blog/2013/01/12/rgb-led-strip-controlled-by-an-arduino/
  // HSV gives smoother colour transitions than RGB
  int i;
  float m, n, f;

  if ((s<0.0) || (s>1.0) || (v<1.0) || (v>1.0)) {
    return 0L;
  }

  if ((h < 0.0) || (h > 6.0)) {
    return long( v * 255 ) + long( v * 255 ) * 256 + long( v * 255 ) * 65536;
  }
  
  i = floor(h);
  f = h - i;
  if (!(i&1)) {
    f = 1 - f; // if i is even
  }
  m = v * (1 - s);
  n = v * (1 - s * f);
  switch (i) {
    case 6:
    case 0: 
      return long(v * 255 ) * 65536 + long( n * 255 ) * 256 + long( m * 255);
    case 1:
      return long(n * 255 ) * 65536 + long( v * 255 ) * 256 + long( m * 255);
    case 2: 
      return long(m * 255 ) * 65536 + long( v * 255 ) * 256 + long( n * 255);
    case 3: 
      return long(m * 255 ) * 65536 + long( n * 255 ) * 256 + long( v * 255);
    case 4: 
      return long(n * 255 ) * 65536 + long( m * 255 ) * 256 + long( v * 255);
    case 5: 
      return long(v * 255 ) * 65536 + long( m * 255 ) * 256 + long( n * 255);
  }
} 


// ================================================================================================
// This is a simple implementation that changes RGB values directly. Calibration is ignored.
// ================================================================================================
void loop1() {
  int r, g, b;

  // fade from blue to violet
  for (r = 0; r < 256; r++) {
    analogWrite(R_LINE, r);
    delay(COLOUR_DELAY);
  }
  // fade from violet to red
  for (b = 255; b > 0; b--) {
    analogWrite(B_LINE, b);
    delay(COLOUR_DELAY);
  }
  // fade from red to yellow
  for (g = 0; g < 256; g++) {
    analogWrite(G_LINE, g);
    delay(COLOUR_DELAY);
  }
  // fade from yellow to green
  for (r = 255; r > 0; r--) {
    analogWrite(R_LINE, r);
    delay(COLOUR_DELAY);
  }
  // fade from green to teal
  for (b = 0; b < 256; b++) {
    analogWrite(B_LINE, b);
    delay(COLOUR_DELAY);
  }
  // fade from teal to blue
  for (g = 255; g > 0; g--) {
    analogWrite(G_LINE, g);
    delay(COLOUR_DELAY);
  }
}

