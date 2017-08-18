# weeklight
Firmware for a gadget lighting up the day of the week

Seven cool white LEDs are wired to a Teensy LC and mounted in a pill reminder box. Teensy pins 17 through 23 are each wired to the cathode of one of the LEDs. The 3.3V output of the Teensy LC is connected to a series resistor that is connected to the anodes of the LEDs. To avoid stressing the microcontroller IOs, only one LED is illuminated at a time.

The Teensy LC listens for input via a USB-serial port and via a capacitive touch sensor on pin 3.

A serial input of '0' through '6' will illuminate the corresponding LED. LEDs earlier in the week will be illuminated dimly by lighting them a small fraction of the time.

A touch near pin 3 will advance to the next day of the week.

The Teensy LC is a low-cost ARM Cortex-M0 development board from http://pjrc.com.

 ![Day of the Week Indicator photograph](https://github.com/pictographer/weeklight/blob/master/IMG_20170817_174136.jpg)
