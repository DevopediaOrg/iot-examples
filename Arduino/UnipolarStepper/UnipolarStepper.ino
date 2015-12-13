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
  Purpose : Drive the unipolar stepper motor 28-BYJ48 that has 5 wires.
            ULN2003 driver module is used for the purpose. There are 
            different implementations in this code for illustration:
            0: Using Stepper library.
            1: Half-wave drive from first principles.
            2: Using third-party AccelStepper library.
            3: With acceleration using AccelStepper library.
  Date    : 21 Nov 2015
  Boards  : ArduinoUno, LaunchPadF5529
  =====================================================================
*/

// Comment/uncomment as suitable for your hardware
// #define LaunchPadF5529

// AccelStepper:
// http://www.airspayce.com/mikem/arduino/AccelStepper/

// Motor pins
#ifdef LaunchPadF5529
#define motorPin1 P8_2
#define motorPin2 P3_7
#define motorPin3 P4_0
#define motorPin4 P4_3
#else
#define motorPin1 2
#define motorPin2 3
#define motorPin3 4
#define motorPin4 5
#endif

#include <Stepper.h>
#include <AccelStepper.h>

// The sequence 1-3-2-4 required for proper sequencing of 28-BYJ48
// steps = Number of steps in one revolution * Gear ratio = (360/Stride Angle) * 63.68395 = (360/5.625) * 63.68395 = 4076
#define STEPS_PER_REV 4076
#define NUM_STEPS 64

Stepper stepper1(NUM_STEPS, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
  Serial.begin(9600);
  setup0(); // modify this to try different implementations
}

void loop()
{
  loop0(); // modify this to try different implementations
}

void setup0()
{
  stepper1.setSpeed(200);
}

void loop0()
{
  Serial.println(millis());
  stepper1.setSpeed(256); // in RPM
  stepper1.step(STEPS_PER_REV/2); // Rotate CW
  delay(2000);
 
  stepper1.setSpeed(256);
  stepper1.step(-STEPS_PER_REV/2); // Rotate CCW
  delay(2000);
}


//=====================================================================
int Steps = 0;
boolean Direction = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left = STEPS_PER_REV - 1;
long time;

void setup1()
{
  pinMode(motorPin1, OUTPUT); 
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT); 
  pinMode(motorPin4, OUTPUT); 
}

void loop1()
{
  while (steps_left>0) {
    stepper(1);
    
    #ifdef LaunchPadF5529
    delay(1);
    #else
    delay(2); // use 2 ms on Arduino Uno to prevent stalling
    #endif

    steps_left--;
  }

  // Delay and change direction
  delay(2000);
  Direction = !Direction;
  steps_left = STEPS_PER_REV-1;
}

void stepper(int xw)
{
  for (int x = 0; x < xw; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        break; 
      case 1:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, HIGH);
        break; 
      case 2:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        break; 
      case 3:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        break; 
      case 4:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        break; 
      case 5:
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        break; 
      case 6:
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        break; 
      case 7:
        digitalWrite(motorPin1, HIGH); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        break; 
      default:
        digitalWrite(motorPin1, LOW); 
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
        break; 
    }
    updateSteps();
  }
}

void updateSteps()
{
  if (Direction==1) { Steps++; }
  if (Direction==0) { Steps--; }
  if (Steps>7) { Steps=0; }
  if (Steps<0) { Steps=7; }
}


//=====================================================================
void setup2()
{
  stepper2.setMaxSpeed(800.0); // in steps per sec
  stepper2.move(1);
  stepper2.setSpeed(800);
}

void loop2()
{
  stepper2.runSpeed();
}


//=====================================================================
void setup3()
{    
  stepper2.setMaxSpeed(800.0);
  stepper2.setAcceleration(100.0);
  stepper2.setSpeed(600);
  stepper2.moveTo(STEPS_PER_REV);
}

void loop3()
{
  // Change direction at the limits
  if (stepper2.distanceToGo() == 0) {
    stepper2.moveTo(-stepper2.currentPosition());
  }
  stepper2.run();
}
