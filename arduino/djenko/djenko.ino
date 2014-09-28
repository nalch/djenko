#include <LED.h>
#include <TimerOne.h>

byte incoming;
byte incomingByte = 0; // for incoming serial data

// green, yellow, red
LED leds[] = {LED(4), LED(3), LED(2)};
const byte LEDS_SIZE = (sizeof(leds)/sizeof(LED));
const byte LED_NONE= B000;
const byte LED_GREEN = B100;
const byte LED_YELLOW = B010;
const byte LED_RED = B001;
const byte LED_ALL = B111;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  light_leds(LED_ALL);
  
  blink();
  delay(5000);
  Timer1.detachInterrupt();
}

void loop() {

  if (Serial.available() > 0) {
    incoming = Serial.read();
  
    if(incoming != incomingByte) {
      
      incomingByte = incoming;
      if(incoming != 'a') {  // stop the blinking, if another led is to be lit
        Timer1.detachInterrupt();
      }
      
      switch(incomingByte) {
      case 'g':
        light_leds(LED_GREEN);
        break;
      case 'y':
        light_leds(LED_YELLOW);
        break;
      case 'r':
        light_leds(LED_RED);
        break;
      case 'a':
        light_leds(LED_NONE);
        blink();
        break;
      }
    
    }
    
  }

}

void light_leds(byte led_mask) {
  byte current_led = 0;
  for (byte current_bit = 1 << (LEDS_SIZE - 1); current_bit > 0; current_bit >>= 1) { //iterate through bit mask
    leds[current_led].setState(led_mask & current_bit);  // light led, if bit is set in parameter
    current_led++;
  }
}

void blink_callback() {
  for(short current_led = 0; current_led < LEDS_SIZE; current_led++) {
    leds[current_led].toggle();
  }
}

void blink() {
  Timer1.initialize();
  Timer1.attachInterrupt(blink_callback);
}
