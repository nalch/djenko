#include <LED.h>
#include <TimerOne.h>

byte incoming;
byte incomingByte = 0; // for incoming serial data

// green, yellow, red
LED leds[] = {LED(4), LED(3), LED(2)};
const short LEDS_SIZE = (sizeof(leds)/sizeof(LED));
const short led_none = B000;
const short led_green = B100;
const short led_yellow = B010;
const short led_red = B001;
const short led_all = B111;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  light_leds(B111);
  
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
        light_leds(led_green);
        break;
      case 'y':
        light_leds(led_yellow);
        break;
      case 'r':
        light_leds(led_red);
        break;
      case 'a':
        light_leds(led_none);
        blink();
        break;
      }
    
    }
    
  }

}

void light_leds(byte led_mask) {
  byte current_led = 0;
  for (byte current_bit = 100; current_bit > 0; current_bit >>= 1) { //iterate through bit mask
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
