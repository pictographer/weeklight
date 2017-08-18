# weeklight
*firmware for a gadget lighting up the day of the week*

The purpose of this project was to help our little son get an idea of when his mommy would return from a trip and learn about work days vs weekends, etc. In the picture below the LEGO woman indicates mommy will return in two days on Friday.

Seven cool white LEDs are wired to a [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) (ARM Cortex-M0 development board) and mounted in a pill reminder box. Teensy pins 17 through 23 are each wired to the cathode of one of the LEDs. The 3.3V output of the Teensy LC is connected to a series resistor that is connected to the anodes of the LEDs. To avoid stressing the microcontroller IOs, only one LED is illuminated at a time. This also reduces the part count because one series resistor can be shared between the seven LEDs.

The Teensy LC listens for input via a USB-serial port connected to a computer and via a capacitive touch sensor on pin 3. The Teensy is able to measure capacitance relative to an internal reference. The human body has a dialectric constant well over ten times greater than air. This enables touch sensing with no additional external circuitry.

A serial input of '0' through '6' will illuminate the corresponding LED. LEDs earlier in the week will be illuminated dimly by lighting them a small fraction of the time. An input of 'f' or 'F' turns all the lights off. An input of 'a' or 'A' activates an alarm mode that rapidly cycles through the lights. This is used as a temperature alarm for the computer in a cabinet that controls the Teensy. At midnight each day, the computer signals the Teensy to display the new day.

A touch near pin 3 will advance to the next day of the week.

![Day of the Week Indicator photograph](https://github.com/pictographer/weeklight/blob/master/IMG_20170817_174136.jpg)
 
# Construction details
 
The LEDs were salvaged from a broken rope light. I drilled a hole in the back of each pill box to poke the LED in. The bottom of each box is lined with aluminum tape as a reflector. The sides are covered with white paper as a diffuser and to help distinguish one day from another. The wires are very fine AWG 30 and a strip of copper tape for the power. The Teesny is attached to the case by two pins soldered to the Teensy and inserted into small holes drilled in the side of case. The wires and Teensy are secured with hot melt glue. The voltage and current supplied by the USB connection is harmless, so the only disadvantage of having the Teensy exposed is that a child may press the program button thus taking the gadget out of its operational mode.

The cost to build this was about $25. A previous version used cardboard instead of a pill box. It would be possible to use a less expensive microprocessor, though that might drive up the development time.
