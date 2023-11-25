#include <arduino-timer.h>
#define LED 13
const int lm35_pin = A0;	// LM35 PIN configured to A0 analogue PIN

auto timer = timer_create_default();

bool toggle_led(void *) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // keeping timer active
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configure D13 PIN as output
  Serial.begin(9600);
}
void loop() {
  int ADC_Value;
  float temp_val;
  ADC_Value = analogRead(lm35_pin);	// Read Temperature 
  temp_val = (ADC_Value * 5);	//Convert adc value to equivalent voltage 
  temp_val = (temp_val/10);	// LM35 gives output of 10mv/°C 
  switch (temp_val > 30)
  {
     case 1:{
        timer.every(500, toggle_led);
        } //blink at 500ms
       break;
     default:{
        timer.every(250, toggle_led);
       } //blink at 250ms
  }
  timer.tick();
}
