//Test the power down library
//Play a melody on a speaker connected to Pin 8
//Then enter low power mode with no wakeup. Arduino must be reset to wake up.
#include "LowPower.h"

void setup() {

  // iterate over the notes of the melody:
 /*
  for (int thisNote = 1; thisNote < 5; thisNote++) {

    int noteDuration = 1000;
    tone(8, thisNote*440, noteDuration); //Arguments are: Pin, Frequency (Hertz), Duration (ms)

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  */
}

void loop() {

  // Enter power down state with ADC and BOD module disabled.
    
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  //LowPower.powerDown(SLEEP_FOREVER,ADC_OFF, BOD_OFF);
  delay(10);
}
