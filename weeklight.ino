// -*-c++-*-
// Gadget to display the day of the week
//
// Seven cool white LEDs are wired to a Teensy LC and mounted in a
// pill reminder box. Teensy pins 17 through 23 are each wired to the
// cathode of one of the LEDs. The 3.3V output of the Teensy LC is
// connected to a series resistor that is connected to the anodes of
// the LEDs. To avoid stressing the microcontroller IOs, only one LED
// is illuminated at a time.
//
// The Teensy LC listens for input via a USB-serial port and via a
// capacitive touch sensor on pin 3.
//
// A serial input of '0' through '6' will illuminate the corresponding LED.
// LEDs earlier in the week will be illuminated dimly by lighting them a
// small fraction of the time.
//
// A touch near pin 3 will advance to the next day of the week.

// Teensy LC pin mapping
const int sunday = 17;
const int saturday = 23;

// Blink delay
const int blink_ms = 250;

// Day names for console feedback
const char* const dayNames[] = {
   "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

// Measured capacitance for pin 3 without touch plus a margin.
const int touchThreshold3 = 410;

const int debounce_ms = 200;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
   for (int i = sunday; i <= saturday; ++i) {
      pinMode(i, OUTPUT);
      digitalWriteFast(i, 1);
   }
   Serial.begin(9600);
   delay(1000);
   Serial.println("Main source file: " __FILE__ "\n"
      "Enter 0 to 6 for Sunday to Saturday, or f for off, or a for alarm.\n");
}

void loop() {
   static int day = saturday;
   static bool alarm = false;

   // Fetch a command from the serial port.
   int count = Serial.available();
   char byte = -1;
   if (count) {
      for (int i = 0; i < count; ++i) {
         byte = Serial.read();
         switch (byte) {
         case '\n': case '\r':
            // Ignore line endings.
            break;
         case '0': case '1': case '2': case '3': case '4': case '5': case '6':
         {
            int dayOrdinal = byte - '0';
            Serial.printf("Day: %d - %s\n", dayOrdinal, dayNames[dayOrdinal]);
            day = dayOrdinal + sunday;  // Convert to pin number.
            break;
         }
         case 'a': case 'A':
            alarm = true;
            break;
         case 'f': case 'F':
            day = sunday - 1;  // All LEDs off.
            alarm = false;
            Serial.println("All off.");
            break;
         case 't': case 'T':
            Serial.printf("Touch read pin 3: %d\n", touchRead(3));
            break;
         default:
            Serial.println("Expecting 0 to 6 for Sunday to Saturday, "
                           "or 'f' for off.");
         }
      }
   }
   // Poll for a touch.
   if (touchThreshold3 < touchRead(3)) {  // Measured threshold for this gadget.
      digitalWriteFast(LED_BUILTIN, 1);  // Turn on the Teensy LED.
      ++day;
      if (saturday < day) {
         day = sunday;
      }
      delay(debounce_ms);  // Acknowledge touch with a blink and debounce.
   } else {
      digitalWriteFast(LED_BUILTIN, 0);  // Turn off Teensy LED.
   }

   // Update the lights.

   // The lights before the current day will be dimly illuminated. The
   // current day will be brightly illuminated.
   for (int i = sunday; i <= day; ++i) {
      digitalWriteFast(i, 0);  // Create a path to ground to turn on the LED.
      if (i == day) {
         delay(1);
      }
      digitalWriteFast(i, 1);  // Turn the LED back off.
   }
   // An alarm is indicated by cycling through each light for a quarter
   // of a second.
   if (alarm) {
      digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
      for (int i = sunday; i <= saturday; ++i) {
         digitalWriteFast(i, 0);
         delay(blink_ms);
         digitalWriteFast(i, 1);
         delay(blink_ms);
      }
   }
}
