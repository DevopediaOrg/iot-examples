# WiringPi-PWM
<table><tr>
<td>
<br><img src="WiringPi-PWM_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>Raspberry Pi 2, 3</pre></p>
<b>Description</b><p><pre>Use WiringPi C library to fade an LED using hardware PWM.
Compile as "gcc WiringPi-PWM.c -o pwm -Wall -lwiringPi"
or use the Makefile, "make all"
Run as "sudo ./pwm"
</pre></p>
</td>
</tr></table>

# wiringpi_pwm
<table><tr>
<td>
<br><img src="WiringPi-PWM_bb.png" width=320px>
</td>
<td>
<b>Boards</b><p><pre>Raspberry Pi 2, 3</pre></p>
<b>Description</b><p><pre>Use WiringPi-Python binding of WiringPi C implementation.
See https://github.com/WiringPi/WiringPi-Python
This example shows HW PWM on GPIO18. To use HW PWM, run 
as "sudo python3 wiring_pwm.py" 
Code also shows the use of SW PWM, which is possible on
any GPIO pin. To use SW PWM, run as 
"python3 wiring_pwm.py sw"
</pre></p>
</td>
</tr></table>

