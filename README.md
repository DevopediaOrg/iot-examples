
# Overview
A collection of examples for getting started in the Internet of Things (IoT). This includes code, wiring diagrams and documentation. In the description of each example, we list supported/tested boards. The same code may work on other boards with no or minimal changes. Files are organized in the following manner:

* `admin`: Utilities for maintaining this repo.
* `Arduino`: Projects on Arduino and Energia. Most examples are about Arduino Uno and TI LaunchPadF5529.
* `NodeMCU`: Projects on NodeMCU including those that can be programmed via Arduino IDE.
* `RaspberryPi`: Projects on mostly Raspberry Pi 2, although examples may work with other variants.

Examples using other platforms such as Intel Edison, Broadcom WICED or ARM mbedmay be added in future.
# Basic Examples

## ADXL345I2C
<table><tr>
<td>
<br><img src="Arduino/ADXL345I2C/ADXL345I2C_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno</pre></p>
<b>Description</b><p><pre>Interface to the ADXL345 accelerometer via I2C.
</pre></p>
</td>
</tr></table>


## ADXL345SPI
<table><tr>
<td>
<br><img src="Arduino/ADXL345SPI/ADXL345SPI_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Interface to the ADXL345 accelerometer via SPI.
</pre></p>
</td>
</tr></table>


## Blink
<table><tr>
<td>
<br><img src="Arduino/Blink/Blink-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/Blink/Blink_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Blink two LEDs alternatively. One LED is on the board and
the other is connected externally.
</pre></p>
</td>
</tr></table>


## BuzzerPot
<table><tr>
<td>
<br><img src="Arduino/BuzzerPot/BuzzerPot-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/BuzzerPot/BuzzerPot-PWM-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/BuzzerPot/BuzzerPot-PWM_bb.png" width=320px>
<br><img src="Arduino/BuzzerPot/BuzzerPot_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Using a potentiometer, drive a buzzer. We illustrate two
variations:
DIRECT   : Buzzer is directly connected to potentiometer.
WITH_PWM : Buzzer is sampled by microcontroller, which then
uses PWM to drive the buzzer.
</pre></p>
</td>
</tr></table>


## DigitalRead
<table><tr>
<td>
<br><img src="Arduino/DigitalRead/DigitalRead_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Investigate the effect of pressing a push button by reading
the voltage as a digital value. The value is printed on the
serial monitor but also used to light up an LED.
</pre></p>
</td>
</tr></table>


## FC04-SoundSensor
<table><tr>
<td>
<br><img src="Arduino/FC04-SoundSensor/FC04-SoundSensor-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/FC04-SoundSensor/FC04-SoundSensor_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>FC04 sound sensor is to read an analog value. Value is
used to drive an LED array that is supposed to light up to
indicate sound loudness. This sensor responds well to base
sounds (low frequency bands). In any case, adjust the
trimmer on the module to suit your application.
</pre></p>
</td>
</tr></table>


## HC05-Bluetooth
<table><tr>
<td>
<br><img src="Arduino/HC05-Bluetooth/HC05-Bluetooth_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Send commands from an Android device via Bluetooth to turn
on/off or blink and LED. A suggested Android app is the
Bluetooth SPP Tools Pro.
</pre></p>
</td>
</tr></table>


## HCSR04-Ultrasonic
<table><tr>
<td>
<br><img src="Arduino/HCSR04-Ultrasonic/HCSR04-Ultrasonic_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Sense the distance of an object/obstacle using ultrasound.
</pre></p>
</td>
</tr></table>


## HallEffect3144
<table><tr>
<td>
<br><img src="Arduino/HallEffect3144/HallEffect3144-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/HallEffect3144/HallEffect3144_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Detect door open/close events using a hall effect sensor.
Note that the orientation of the magnet (North pole or
South pole) matters. This example shows how to write
interrupt code.
</pre></p>
</td>
</tr></table>


## IR-Promixity-Detection
<table><tr>
<td>
<br><img src="Arduino/IR-Promixity-Detection/IR-Promixity-Detection_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Use an IR LED and an IR photodiode to detect proximity of
an obstable. An indicator LED glows in response to the
proximity of the obstacle. This indicator can be programmed
as a digital or an analog output.
</pre></p>
</td>
</tr></table>


## IR-RemoteControl
<table><tr>
<td>
<br><img src="Arduino/IR-RemoteControl/IR-RemoteControl_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Use an IR receiver/decoder to decode and store commands
from a household remote control. Use an IR LED to send the
commands to the household gadget/appliance.
</pre></p>
</td>
</tr></table>


## LCD-2x16-Joystick
<table><tr>
<td>
<br><img src="Arduino/LCD-2x16-Joystick/LCD-2x16-Joystick_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Read values from a joystick and display the same on a 2x16
line LCD module. LiquidCrystal library is used in this
example. 4-pin mode is used for the LCD. Since RW pin is
grounded, only write operation is possible.
</pre></p>
</td>
</tr></table>


## LDR
<table><tr>
<td>
<br><img src="Arduino/LDR/LDR-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/LDR/LDR_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>LDR is a light dependant resistor. Read the analog voltage
across the LDR and derive the resistance.
</pre></p>
</td>
</tr></table>


## LM35-7Segx3
<table><tr>
<td>
<br><img src="Arduino/LM35-7Segx3/LM35-7Segx3-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/LM35-7Segx3/LM35-7Segx3_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Use LM35 to sense temperature that is displayed. 
Use 74HC595 shift register to control 3 7-segment displays.
</pre></p>
</td>
</tr></table>


## LM35
<table><tr>
<td>
<br><img src="Arduino/LM35/LM35-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/LM35/LM35_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Use analog input to read temperature measurement from LM35.
</pre></p>
</td>
</tr></table>


## LedMatrix-Max7219
<table><tr>
<td>
<br><img src="Arduino/LedMatrix-Max7219/LedMatrix-Max7219_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Drive one or more 8x8 LED matrices using MAX7219. SPI is
is used for interfacing. Two variants are presented below:
0: From first principles.
1: Two 8x8 matrices using LedControl library.
</pre></p>
</td>
</tr></table>


## LedMatrix
<table><tr>
<td>
<br><img src="Arduino/LedMatrix/LedMatrix_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Drive an 8x8 LED matrix without any IC.
</pre></p>
</td>
</tr></table>


## LedStrip-ULN2003
<table><tr>
<td>
<br><img src="Arduino/LedStrip-ULN2003/LedStrip-ULN2003_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Drive an LED strip using Darlington array ULN2003. PWM is
used to control the colours. Hence, pins must be capable
of PWM out. Two implementations are illustrated.
</pre></p>
</td>
</tr></table>


## MQ2-GasSensor
<table><tr>
<td>
<br><img src="Arduino/MQ2-GasSensor/MQ2-GasSensor-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/MQ2-GasSensor/MQ2-GasSensor_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Use MQ2 gas sensor module and read analog values. The code
also includes calibration. Since the mapping betweeen Rs
and PPM is non-linear no conversion to PPM is done at the
moment. No compensation has been included for current
humidity and temperature.
</pre></p>
</td>
</tr></table>


## PIR-MotionDetector
<table><tr>
<td>
<br><img src="Arduino/PIR-MotionDetector/PIR-MotionDetector_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Using a PIR module we detect motion. Debouncing is used in
such a way that current motion has to stop for a minimum
time interval before we record a new motion.
</pre></p>
</td>
</tr></table>


## RTC-IN1307
<table><tr>
<td>
<br><img src="Arduino/RTC-IN1307/RTC-IN1307_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Interface to Real-Time Clock (RTC) chip IN1307, which has
an I2C interface. DS1307 is an equivalent chip but is not
tested with this code. Code allows users to set the time
via UART. RTClib is used in this code.
</pre></p>
</td>
</tr></table>


## ReedSwitch
<table><tr>
<td>
<br><img src="Arduino/ReedSwitch/ReedSwitch-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/ReedSwitch/ReedSwitch_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Detect door open/close events using a reed switch.
This example shows how to write interrupt code.
</pre></p>
</td>
</tr></table>


## RgbLed
<table><tr>
<td>
<br><img src="Arduino/RgbLed/RgbLed-LaunchPadF5529_bb.png" width=320px>
<br><img src="Arduino/RgbLed/RgbLed_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Change colours on an RGB LED. PWM is used to control the
colours. Hence, pins must be capable of PWM out.
</pre></p>
</td>
</tr></table>


## SerialCmds
<table><tr>
<td>
<br><img src="Arduino/SerialCmds/SerialCmds_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Control an LED using commands "on" or "off" received on the
serial port. This is a simple illustration of how we can
control the system remotely using the serial interface.
Implementation assumes characters are buffered and sent
together as a single command. This is the case with Arduino
and Energia serial monitors. This won't work in Fritzing 
serial monitor since characters are sent as soon as they 
are typed.
</pre></p>
</td>
</tr></table>


## ServoPushbutton
<table><tr>
<td>
<br><img src="Arduino/ServoPushbutton/ServoPushbutton_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Control servo movement using push buttons.
</pre></p>
</td>
</tr></table>


## UnipolarStepper
<table><tr>
<td>
<br><img src="Arduino/UnipolarStepper/UnipolarStepper-ULN2003_bb.png" width=320px>
<br><img src="Arduino/UnipolarStepper/UnipolarStepper_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>ArduinoUno, LaunchPadF5529</pre></p>
<b>Description</b><p><pre>Drive the unipolar stepper motor 28-BYJ48 that has 5 wires.
ULN2003 driver module is used for the purpose. It's also
possible to use the ULN2003 chip directly without the
dedicated module. There are different implementations in
this code for illustration:
0: Using Stepper library.
1: Half-wave drive from first principles.
2: Using third-party AccelStepper library.
3: With acceleration using AccelStepper library.
</pre></p>
</td>
</tr></table>


## Blynk-Blink
<table><tr>
<td>
<br><img src="NodeMCU/Blynk-Blink/Blynk-Blink_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>NodeMCU</pre></p>
<b>Description</b><p><pre>Control an LED manually from the Blynk app. This code can
be compiled and uploaded from Arduino IDE. Update the code
with your token, Wi-Fi SSID and password.
</pre></p>
</td>
</tr></table>


## Blink-Fade
<table><tr>
<td>
<br><img src="RaspberryPi/Blink-Fade/Blink-Fade_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>Raspberry Pi 2</pre></p>
<b>Description</b><p><pre>Use RPi.GPIO module to blink or fade an LED. Execution
switches between the two whenever a push button is pressed
and released. Fading uses software PWM since RPi.GPIO
module does not support hardware PWM. Note that RPi.GPIO 
is available by default on Raspbian Jessie.
</pre></p>
</td>
</tr></table>

