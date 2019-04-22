
# Overview
A collection of examples for getting started in the Internet of Things (IoT). This includes code, wiring diagrams and documentation. In the description of each example, we list supported/tested boards. The same code may work on other boards with no or minimal changes. Files are organized in the following manner:

* `admin`: Utilities for maintaining this repo.
* `Arduino`: Projects on Arduino and Energia. Most examples are about Arduino Uno and TI LaunchPadF5529.
* `NodeMCU`: Projects on NodeMCU including those that can be programmed via Arduino IDE.
* `RaspberryPi`: Projects on mostly Raspberry Pi 2 or 3, although examples may work with other variants.

Examples using other platforms such as Intel Edison, Broadcom WICED or ARM mbed may be added in future.

# Arduino/ (28 projects)
<table><tr>
<tr><td colspan=2><h3>1. ADXL345I2C</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/ADXL345I2C">ADXL345I2C</a></td>
<td><pre>Interface to the ADXL345 accelerometer via I2C.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>2. ADXL345SPI</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/ADXL345SPI">ADXL345SPI</a></td>
<td><pre>Interface to the ADXL345 accelerometer via SPI.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>3. Blink</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/Blink">Blink</a></td>
<td><pre>Blink two LEDs alternatively. One LED is on the board and
the other is connected externally.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>4. BuzzerPot</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/BuzzerPot">BuzzerPot</a></td>
<td><pre>Using a potentiometer, drive a buzzer. We illustrate two
variations:
DIRECT   : Buzzer is directly connected to potentiometer.
WITH_PWM : Buzzer is sampled by microcontroller, which then
uses PWM to drive the buzzer.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>5. DigitalRead</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/DigitalRead">DigitalRead</a></td>
<td><pre>Investigate the effect of pressing a push button by reading
the voltage as a digital value. The value is printed on the
serial monitor but also used to light up an LED.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>6. FC04-SoundSensor</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/FC04-SoundSensor">FC04-SoundSensor</a></td>
<td><pre>FC04 sound sensor is to read an analog value. Value is
used to drive an LED array that is supposed to light up to
indicate sound loudness. This sensor responds well to base
sounds (low frequency bands). In any case, adjust the
trimmer on the module to suit your application.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>7. HC05-AT-Cmds</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/HC05-AT-Cmds">HC05-AT-Cmds</a></td>
<td><pre>Put the Bluetooth module in AT command mode. Run a bunch of
commands to configure the module. Module must be forced to
enter AT command mode by long pressing the reset button
before powering it up.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>8. HC05-Bluetooth</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/HC05-Bluetooth">HC05-Bluetooth</a></td>
<td><pre>Send commands from an Android device via Bluetooth to turn
on/off or blink and LED. A suggested Android app is the
Bluetooth SPP Tools Pro.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>9. HCSR04-Ultrasonic</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/HCSR04-Ultrasonic">HCSR04-Ultrasonic</a></td>
<td><pre>Sense the distance of an object/obstacle using ultrasound.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>10. HallEffect3144</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/HallEffect3144">HallEffect3144</a></td>
<td><pre>Detect door open/close events using a hall effect sensor.
Note that the orientation of the magnet (North pole or
South pole) matters. This example shows how to write
interrupt code.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>11. IR-Proximity-Detection</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/IR-Proximity-Detection">IR-Proximity-Detection</a></td>
<td><pre>Use an IR LED and an IR photodiode to detect proximity of
an obstable. An indicator LED glows in response to the
proximity of the obstacle. This indicator can be programmed
as a digital or an analog output.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>12. IR-RemoteControl</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/IR-RemoteControl">IR-RemoteControl</a></td>
<td><pre>Use an IR receiver/decoder to decode and store commands
from a household remote control. Use an IR LED to send the
commands to the household gadget/appliance.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>13. LCD-2x16-Joystick</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LCD-2x16-Joystick">LCD-2x16-Joystick</a></td>
<td><pre>Read values from a joystick and display the same on a 2x16
line LCD module. LiquidCrystal library is used in this
example. 4-pin mode is used for the LCD. Since RW pin is
grounded, only write operation is possible.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>14. LDR</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LDR">LDR</a></td>
<td><pre>LDR is a light dependant resistor. Read the analog voltage
across the LDR and derive the resistance.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>15. LM35</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LM35">LM35</a></td>
<td><pre>Use analog input to read temperature measurement from LM35.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>16. LM35-7Segx3</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LM35-7Segx3">LM35-7Segx3</a></td>
<td><pre>Use LM35 to sense temperature that is displayed. 
Use 74HC595 shift register to control 3 7-segment displays.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>17. LedMatrix</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LedMatrix">LedMatrix</a></td>
<td><pre>Drive an 8x8 LED matrix without any IC.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>18. LedMatrix-Max7219</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LedMatrix-Max7219">LedMatrix-Max7219</a></td>
<td><pre>Drive one or more 8x8 LED matrices using MAX7219. SPI is
is used for interfacing. Two variants are presented below:
0: From first principles.
1: Two 8x8 matrices using LedControl library.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>19. LedStrip-ULN2003</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/LedStrip-ULN2003">LedStrip-ULN2003</a></td>
<td><pre>Drive an LED strip using Darlington array ULN2003. PWM is
used to control the colours. Hence, pins must be capable
of PWM out. Two implementations are illustrated.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>20. MCP3008</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/MCP3008">MCP3008</a></td>
<td><pre>Use LM35 to sense temperature that is displayed. 
External ADC 10-bit MCP3008 is used and read by Arduino
via SPI.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>21. MQ2-GasSensor</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/MQ2-GasSensor">MQ2-GasSensor</a></td>
<td><pre>Use MQ2 gas sensor module and read analog values. The code
also includes calibration. Since the mapping betweeen Rs
and PPM is non-linear no conversion to PPM is done at the
moment. No compensation has been included for current
humidity and temperature.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>22. PIR-MotionDetector</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/PIR-MotionDetector">PIR-MotionDetector</a></td>
<td><pre>Using a PIR module we detect motion. Debouncing is used in
such a way that current motion has to stop for a minimum
time interval before we record a new motion.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>23. RTC-IN1307</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/RTC-IN1307">RTC-IN1307</a></td>
<td><pre>Interface to Real-Time Clock (RTC) chip IN1307, which has
an I2C interface. DS1307 is an equivalent chip but is not
tested with this code. Code allows users to set the time
via UART. RTClib is used in this code.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>24. ReedSwitch</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/ReedSwitch">ReedSwitch</a></td>
<td><pre>Detect door open/close events using a reed switch.
This example shows how to write interrupt code.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>25. RgbLed</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/RgbLed">RgbLed</a></td>
<td><pre>Change colours on an RGB LED. PWM is used to control the
colours. Hence, pins must be capable of PWM out.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>26. SerialCmds</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/SerialCmds">SerialCmds</a></td>
<td><pre>Control an LED using commands "on" or "off" received on the
serial port. This is a simple illustration of how we can
control the system remotely using the serial interface.
Implementation assumes characters are buffered and sent
together as a single command. This is the case with Arduino
and Energia serial monitors. This won't work in Fritzing 
serial monitor since characters are sent as soon as they 
are typed.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>27. ServoPushbutton</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/ServoPushbutton">ServoPushbutton</a></td>
<td><pre>Control servo movement using push buttons.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>28. UnipolarStepper</h3></td></tr>
<tr>
<td style="width:200px"><a href="Arduino/UnipolarStepper">UnipolarStepper</a></td>
<td><pre>Drive the unipolar stepper motor 28-BYJ48 that has 5 wires.
ULN2003 driver module is used for the purpose. It's also
possible to use the ULN2003 chip directly without the
dedicated module. There are different implementations in
this code for illustration:
0: Using Stepper library.
1: Half-wave drive from first principles.
2: Using third-party AccelStepper library.
3: With acceleration using AccelStepper library.
</pre></td>
</tr>
</table>

# NodeMCU/ (3 projects)
<table><tr>
<tr><td colspan=2><h3>1. Blynk-Blink</h3></td></tr>
<tr>
<td style="width:200px"><a href="NodeMCU/Blynk-Blink">Blynk-Blink</a></td>
<td><pre>Control an LED manually from the Blynk app. This code can
be compiled and uploaded from Arduino IDE. Update the code
with your token, Wi-Fi SSID and password.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>2. Blynk-LM35</h3></td></tr>
<tr>
<td style="width:200px"><a href="NodeMCU/Blynk-LM35">Blynk-LM35</a></td>
<td><pre>Send temperature readings from LM35 and display the same
on the Blynk app.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>3. Blynk-RgbLed</h3></td></tr>
<tr>
<td style="width:200px"><a href="NodeMCU/Blynk-RgbLed">Blynk-RgbLed</a></td>
<td><pre>Control an LED manually from the Blynk app. This code can
be compiled and uploaded from Arduino IDE. Update the code
with your token, Wi-Fi SSID and password.
</pre></td>
</tr>
</table>

# RaspberryPi/ (7 projects)
<table><tr>
<tr><td colspan=2><h3>1. ADXL345-I2C</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/ADXL345-I2C">adxl345_i2c</a></td>
<td><pre>Interface Raspberry Pi with ADXL345 accelerometer via I2C.
We use the Adafruit Python ADXL345 for this purpose.
This can installed with "sudo pip3 install adafruit-adxl345"
See https://github.com/adafruit/Adafruit_Python_ADXL345
Ensure that I2C is enabled via raspi-config.
Ensure that line i2c-dev is present in file /etc/modules
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>2. Blink-Fade</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/Blink-Fade">blink_fade</a></td>
<td><pre>Use RPi.GPIO module to blink or fade an LED. 
Fading uses software PWM since RPi.GPIO module does not
support hardware PWM. Note that RPi.GPIO is available by
default on Raspbian Jessie and Stretch.
</pre></td>
</tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/Blink-Fade">toggle_uart</a></td>
<td><pre>Read commands from UART to control LED state.
Use gpiozero module to control the LED.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>3. LCD-Dashboard</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/LCD-Dashboard">lcd_dashboard</a></td>
<td><pre>We use tkinter package to display a GUI window on a 3.5"
480x320 LCD display from Waveshare.
App shows current time, Devopedia logo, and the latest
tech news. News is pulled via a free REST API service and 
it's use requires an API key. The key is expected to be
defined in an environment variable NEWS_API_KEY.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>4. LED-PushButton</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/LED-PushButton">led_pushbutton</a></td>
<td><pre>Use GPIO Zero module to control an LED. LED state toggles
whenever a push button is pressed and released.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>5. LM35-ADC</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/LM35-ADC">lm35_adc</a></td>
<td><pre>Interface Raspberry Pi with MCP3008 for ADC functionality.
LM35 temperature sensor is connected to CH1 of MCP3008.
MCP3008 is powered with 3.3V.
If environment variable TS_API_KEY is set, data is sent to
the ThingSpeak IoT cloud. REST API is used.
</pre></td>
</tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/LM35-ADC">lm35_adc_mqtt</a></td>
<td><pre>Interface Raspberry Pi with MCP3008 for ADC functionality.
LM35 temperature sensor is connected to CH1 of MCP3008.
MCP3008 is powered with 3.3V.
If environment variable TS_API_KEY is set, data is sent to
the ThingSpeak IoT cloud. MQTT is used.
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>6. SSD1306-BMP180</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/SSD1306-BMP180">ssd1306_bmp180</a></td>
<td><pre>Use BMP180 to obtain three sensor readings: temperature,
barometric pressure and altitude. BMP180 uses an I2C 
interface.
Show these readings on SSD1306 OLED display. This uses an
SPI interface.
RPI is used with the WaveShare Pioneer600 that contains
both BM180 and SSD1306. Code is adapted from examples at
https://www.waveshare.com/wiki/File:Pioneer600-Code.tar.gz
For this example, install Python packages (via pip3):
smbus, pillow
</pre></td>
</tr>
</table>

<table><tr>
<tr><td colspan=2><h3>7. WiringPi-PWM</h3></td></tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/WiringPi-PWM">WiringPi-PWM</a></td>
<td><pre>Use WiringPi C library to fade an LED using hardware PWM.
Compile as "gcc WiringPi-PWM.c -o pwm -Wall -lwiringPi"
or use the Makefile, "make all"
Run as "sudo ./pwm"
</pre></td>
</tr>
<tr>
<td style="width:200px"><a href="RaspberryPi/WiringPi-PWM">wiringpi_pwm</a></td>
<td><pre>Use WiringPi-Python binding of WiringPi C implementation.
See https://github.com/WiringPi/WiringPi-Python
This example shows HW PWM on GPIO18. To use HW PWM, run 
as "sudo python3 wiring_pwm.py" 
Code also shows the use of SW PWM, which is possible on
any GPIO pin. To use SW PWM, run as 
"python3 wiring_pwm.py sw"
</pre></td>
</tr>
</table>

