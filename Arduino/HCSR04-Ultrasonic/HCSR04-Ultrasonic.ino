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
  Purpose : Sense the distance of an object/obstacle using ultrasound.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

#ifdef LaunchPadF5529
#define TriggerPin P2_0
#define EchoPin P2_2
#else
#define TriggerPin 2
#define EchoPin 3
#endif

#define VelocitySound 340 // meters/sec

void setup()
{
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  digitalWrite(TriggerPin, LOW);

  #ifdef LaunchPadF5529
  pinMode(EchoPin, INPUT_PULLDOWN);
  #else
  pinMode(EchoPin, INPUT);
  digitalWrite(EchoPin, HIGH);
  #endif
}

void loop()
{
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  unsigned int pulseDuration = pulseIn(EchoPin, HIGH);
  if (pulseDuration) {
    float distance = float(pulseDuration)*VelocitySound/20000; // us->s (/1000000); m->cm (*100)
    if (distance <= 2) { // minimum distance the sensor can measure
      Serial.println("Obstacle is too close.");
    }
    else if (distance > 400) { // maximum distance the sensor can measure
      Serial.println("Obstacle is probably out of range.");
    }
    else {
      Serial.print("Obstacle is ");
      Serial.print(distance);
      Serial.println(" cms away.");
    }
  }
  else {
    Serial.println("No obstacle detected.");
  }
  delay(500); // minimum measurement cycle recommended in 60ms
}