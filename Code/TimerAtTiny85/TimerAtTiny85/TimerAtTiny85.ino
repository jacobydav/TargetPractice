/*This code is intended to run on the ATTiny85
 * 
 * Turn on an output for 30 seconds. Then go to low power mode
 * until the chip is reset.
 * This is used as a basic timer relay. It will turn on power for 30 seconds
 * for the Target Practice project by turning on a relay.
 */

 #include <avr/sleep.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC


//Output to turn on Relay
//IO Number 1 = Physical pin number 6 on ATTiny85
int outputPin = 1;

//The amount of time to leave the output on
long timeOn_ms = 60000L;

void setup() 
{
  pinMode(outputPin,OUTPUT);
  digitalWrite(outputPin,LOW);

  adc_disable(); // ADC uses ~320uA
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() 
{ 
     //Turn on the output which will trigger the relay
      digitalWrite(outputPin,HIGH);
        
     delay(timeOn_ms);

  //Turn off the output which will trigger the relay
      digitalWrite(outputPin,LOW);
  //low power mode begin, only to be awaken on reset
  sleep_enable();
  sleep_cpu();
}
