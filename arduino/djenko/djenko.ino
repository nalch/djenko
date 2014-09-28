#include <LED.h>
#include <TimerOne.h>

byte incoming;
byte incomingByte = 0; // for incoming serial data

// green, yellow, red
LED leds[] = {LED(4), LED(3), LED(2)};
const short LEDS_SIZE = (sizeof(leds)/sizeof(LED));
const short led_none = -1;
const short led_green = 0;
const short led_yellow = 1;
const short led_red = 2;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  leds[led_green].on();
  leds[led_yellow].on();
  leds[led_red].on();
  
  delay(3000);
}

void loop() {

  if (Serial.available() > 0) {
    incoming = Serial.read();
  }

  if(incoming != incomingByte) {
    
    incomingByte = incoming;
    switch(incomingByte) {
    case 'g':
      light_led(led_green);
      break;
    case 'y':
      light_led(led_yellow);
      break;
    case 'r':
      light_led(led_red);
      break;
    case 'a':
      light_led(led_none);
      blink();
      break;
    }  
  
  }

}

void light_led(short led) {
  Timer1.detachInterrupt();
  for(short current_led = 0; current_led < LEDS_SIZE; current_led++) {
    led == current_led ? leds[current_led].on() : leds[current_led].off();
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
