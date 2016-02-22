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
  Purpose : Using a PIR module we detect motion. Debouncing is used in
            such a way that current motion has to stop for a minimum
            time interval before we record a new motion.
  Date    : 22 Feb 2016
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
int pirPin = P2_0;
int ledPin = RED_LED;
#else
int pirPin = 3;
int ledPin = 13;
#endif

typedef enum {
  NONE, // sensor is not ready for use
  INIT, // sensor is being initialized
  STILL, // sensor is detecting no motion
  MOTION, // sensor is detecting motion
  PAUSE // between motion and returning to stillness
} PIR_State;

int calibrationTime = 30;
long unsigned int motionPauseTs; // timestamp of start of motion
long unsigned int pauseInterval = 3000; // idle time in ms to end current motion event
PIR_State pirState = NONE;

void calibrate(int warmupTime)
{
  Serial.print("Calibrating sensor ");
  for(int i = 0; i < warmupTime; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
}

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pirState = INIT;
  calibrate(calibrationTime);
  pirState = STILL;
  
  delay(50);
}

void loop()
{
  long unsigned int currTs = millis();
  int pirValue = digitalRead(pirPin);
  digitalWrite(ledPin, pirValue); // LED reflects the sensor's output

  switch (pirState) {
    case STILL:
      if (pirValue == HIGH) {
        pirState = MOTION;
        Serial.print("Motion detected at time ");
        Serial.println(currTs/1000);
      }
      break;
    case MOTION:
      if (pirValue == LOW) {
        pirState = PAUSE;
        motionPauseTs = currTs;
      }
      break;
    case PAUSE:
      if (pirValue == LOW) {
        if (currTs - motionPauseTs > pauseInterval) {
          Serial.print("Motion ended at time ");
          Serial.println((currTs-pauseInterval)/1000);
          Serial.println("");
          pirState = STILL;
          delay(50);
        }
      }
      else {
        pirState = MOTION;
      }
      break;
    default:
      pirState = STILL; // reset if something's gone wrong
      break;
  }
}

