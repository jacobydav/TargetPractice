//Test sounds for TargetPractice
#include "pitches.h"

int sAudioPin = 8;                    //speaker output pin

void setup() {
  // put your setup code here, to run once:
   pinMode(sAudioPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //playFinalSound();

  //delay(5000);

  //playBadSound();

  playHitSound();
  delay(10000);
}


void playFinalSound()
{
  int NOTE_SUSTAIN = 50;
  for(uint8_t nLoop = 0;nLoop < 2;nLoop ++)
  {
    tone(sAudioPin,NOTE_A5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_B5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_B5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_C5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_E5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_D5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_E5);
    delay(NOTE_SUSTAIN);
    tone(sAudioPin,NOTE_E5);
    delay(NOTE_SUSTAIN);
  }
  noTone(sAudioPin);
}

void playHitSound()
{
  for(uint8_t nLoop = 0;nLoop < 1;nLoop ++)
  {
    tone(sAudioPin,NOTE_A4);
    delay(75);
    tone(sAudioPin,NOTE_C4);
    delay(100);
    tone(sAudioPin,NOTE_A5);
    delay(200);
  }
  noTone(sAudioPin);
}

void playBadSound()
{
    tone(sAudioPin,NOTE_G4);
    delay(250);
    tone(sAudioPin,NOTE_C4);
    delay(500);
    noTone(sAudioPin);
}
