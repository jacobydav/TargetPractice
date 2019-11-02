/*
 * Nerf Gun Target Practice
 * 1. Wait for targets to be in place. We do this by checking the limit switches that detect the target position.
 * 2. Count down from 10 to 0 on the seven seg display
 * 3. Wait a random amount of time and then show a random target number (1,2,3)
 * 4. Wait for the target to get knocked down. Record the time between displaying the target number and when it gets knocked down.
 * 5. Repeat for all 3 targets.
 * 6. Show a final score based on targets that were hit and the time required to hit them.
 */
 
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <LowPower.h>
#include "pitches.h"

Adafruit_7segment matrix = Adafruit_7segment();

int targetInPosWaitTime_ms = 5000;   //milliseconds to wait for the targets to be in position
int targetInPosDelay_ms = 50;         //delay before checking that targets are in position
bool b_targetsInPos = false;          //boolean to indicate if targets are in position
int targ_pin[3] = {2,3,4};
long targetPracticeTimeMax_ms = 50000;    //max time to run the target practice
int sAudioPin = 8;                    //speaker output pin
int relayPin = 11;                    //shutdown relay output pin
//Penalty parameters begin
int wrongTargetPenalty = 33.33;      // points off if a target was hit before it became active
//To caluclate delay penalty
//Let targHitDelay = The number of seconds of delay between a target becoming active and when it is hit
//The penalty will be calulated as targHitDelay^targetXDelayPowPenalty
float targetDelayPowPenalty[3] = {1.4,1.5,1.4};  
float maxDelayPenalty = 26;   //Max delay penalty
int maxTargetActiveTime_ms = 10000;    //The max time a target will be active
//Penalty parameters end

void setup() {
  //1st thing to happen is to turn on the relay
  pinMode(relayPin,OUTPUT);    // Relay Signal Pin
  digitalWrite(relayPin,LOW);   //Low signal turns the relay on
   
  Serial.begin(9600);
  Serial.println("Target Practice Begin");

  pinMode(targ_pin[0],INPUT_PULLUP);
  pinMode(targ_pin[1],INPUT_PULLUP);
  pinMode(targ_pin[2],INPUT_PULLUP);
  pinMode(sAudioPin, OUTPUT);

  matrix.begin(0x70);

  //Get a seed for random numbers
  randomSeed(analogRead(0));
}

void loop() 
{
  //Check that all of the targets are in position
  checkTargetsInPos();
  //Begin a countdown
  showCountDown();
  //Begin target practice
  runTargetPractice();
  //Shutdown
  //Testing begin
  Serial.println("Shutting Down");
  Serial.flush();
  delay(250);
  //Testing end
  digitalWrite(relayPin,HIGH);  // shutdown the circuit
  //This code should never be reached because the relay should have opened the path to ground.
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
}

//Check that all of the targets are in position
//If they are not, then we will go into low power mode
void checkTargetsInPos()
{
  int targInPosCount = 0;       //Debounce by requiring the targets to be in pos for 3 consecutive checks
  //Start with all zeros display
   matrix.print(4444, DEC);  //show all fours    
   matrix.blinkRate(2);     //blink until the targets are in place
   matrix.writeDisplay();

  //Testing begin
  Serial.println("checkTargetsInPos begin");
  //delay(1000);
  //Testing end
   
  //Wait up to 10 seconds for the targets to be in position
  //Flash all 0s until targets are in position
  b_targetsInPos = false; 
  for(int i=0;i<targetInPosWaitTime_ms/targetInPosDelay_ms;i++)
  {
    //Testing begin
    int targ1State = digitalRead(targ_pin[0]);
    int targ2State = digitalRead(targ_pin[1]);
    int targ3State = digitalRead(targ_pin[2]);
    Serial.print(targ1State);Serial.print(",");
    Serial.print(targ2State);Serial.print(",");
    Serial.println(targ3State);
    //Testing end
    if(digitalRead(targ_pin[0])==LOW && digitalRead(targ_pin[1])==LOW && digitalRead(targ_pin[2])==LOW)
    {
      targInPosCount++;
      if(targInPosCount>=3)
      {
        b_targetsInPos = true;
        break;
      }
    }
    else
    {
      targInPosCount=0;
    }
      
    delay(targetInPosDelay_ms);
  }

  //Stop blinking
  matrix.clear();
   matrix.blinkRate(0);
   matrix.writeDisplay();

   //Testing begin
  Serial.println("checkTargetsInPos end");
  Serial.print("b_targetsInPos = "); Serial.println(b_targetsInPos, DEC);
  delay(1000);
  //Testing end
   
  //If the targets were never put in position  
  if(b_targetsInPos==false)
  {
    Serial.flush();
    delay(250);
    //Testing end
    digitalWrite(relayPin,HIGH);  // shutdown the circuit
    //This code should never be reached because the relay should have opened the path to ground.
    //Go into power save mode 
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  }
}

//Show a countdown on the display
void showCountDown()
{    
   //Testing begin
  Serial.println("showCountdown begin");
  //Testing end
  for(int i=5;i>0;i--)
  {
     matrix.writeDigitNum(0, i, false);
     matrix.writeDisplay();
     //Play a tone on each countdown
     tone(sAudioPin,NOTE_C4);
    delay(100);
    noTone(sAudioPin);
     delay(900);
  } 
   //Testing begin
  Serial.println("showCountdown end");
  //Testing end
}

//Run target practice
//Monitor the targets continuosly.
//Show current target on display
void runTargetPractice()
{ 
   //Testing begin
  Serial.println("runTargetPractice begin");
  delay(500);
  //Testing end
  //Randomly select the target order
  int activeTargetFirst=0;    //The target number that will be active first (1,2, or 3)
  int activeTargetSecond=0;   //The target number that will be active second (1,2, or 3)
  int activeTargetThird=0;    //The target number that will be active third (1,2, or 3)
  int waitTimeBegin=0;        //The time when the wait step began. Used by multiple wait states.
  int activeTargetWait=0;     //The amount of time to wait before making the next target active.
  float penaltyTotal=0;         //The amount of penalty from hitting the wrong target, etc
  activeTargetFirst=random(1,4);
  //2nd target must be different from the first
  activeTargetSecond=random(1,4);
  while(activeTargetSecond==activeTargetFirst)
    activeTargetSecond=random(1,4);
  //3rd target must be different from the first and second
  activeTargetThird=random(1,4);
  while(activeTargetThird==activeTargetSecond || activeTargetThird==activeTargetFirst)
    activeTargetThird=random(1,4);

  int currState = 110;
  
  //States (x=1,2,or 3 depending on if we are on First Target, Second Target, or Third Target):
  //0=none
  //x10=enter wait for targetFirst to become active (display blinking AAAA)
  //x15=monitor time remaining for target to become active
  //x20=display target on display
  //x30=wait for targetFirst to get hit
  //400=done
  
  for(long i=0;i<targetPracticeTimeMax_ms;i++)
  {
    switch (currState)
    {
      case 110:   //calculate time for targetFirst to become active
           //Testing begin
          Serial.println("state=110");
          //Testing end
          waitTimeBegin = i;
          activeTargetWait = random(2000,6000);
          //Testing begin
          Serial.print("activeTargetWait=");Serial.println(activeTargetWait);
          Serial.print("waitTimeBegin=");Serial.println(waitTimeBegin);
          //Testing end
          currState=115;
          matrix.print(0xAAAA, HEX);
          matrix.blinkRate(1);
          matrix.writeDisplay();
        break;
      case 115:     //monitor time remaining for targetFirst to become active
          //Testing begin
          //Serial.println("state=115");
         //Serial.print("i=");Serial.println(i);
          //Serial.print("waitTimeBegin+activeTargetWait=");Serial.println(waitTimeBegin+activeTargetWait);
          //Testing end
          if(i>waitTimeBegin+activeTargetWait)
            currState=120;
        break;
      case 120:       //display target on display
          //Testing begin
          Serial.println("state=120");
          //Testing end
          matrix.print(activeTargetFirst, DEC);
          matrix.blinkRate(0);
          matrix.writeDisplay();
          //record the time when the active target was displayed
          waitTimeBegin=i;
          //check if the target was already down before showing the number. That is a penalty
          if(digitalRead(targ_pin[activeTargetFirst-1])==HIGH)
          {
            delay(200);
            //play the fail sound
            playBadSound();
            delay(500);
            //Add to penalty
            penaltyTotal=penaltyTotal+wrongTargetPenalty;
            //Delay before moving to next target
            delay(1000);
            //Move on to second target
            currState=210;
          }
          else
          {
            currState=130;  //begin waiting for target to get hit
          }
        break;
      case 130:     //Wait for target to be hit or time to run out.
          //Testing begin
          //Serial.println("state=130");
          //Testing end
          if(digitalRead(targ_pin[activeTargetFirst-1])==HIGH || i-waitTimeBegin>maxTargetActiveTime_ms)
          {
            //get the time
            int delayTime_ms = i-waitTimeBegin;
            //Check if time ran out before the target was hit
            if(i-waitTimeBegin>maxTargetActiveTime_ms)
            {
              //Play bad sound
              playBadSound();
            }
            else
            {
              //play the hit sound
              playHitSound();
            }
            //calculate the penalty, this works the same if they hit the target or not
            float delayPenalty = getDelayPenalty(activeTargetFirst, delayTime_ms);
            //Add to penalty
            penaltyTotal=penaltyTotal+delayPenalty;
            //Delay before moving to next target
            delay(500);
            //Move to next target
            currState=210;
          }          
        break;
      case 210:
           //Testing begin
          Serial.println("state=210");
          //Testing end
          waitTimeBegin = i;
          activeTargetWait = random(2000,6000);
          //Testing begin
          Serial.print("activeTargetWait=");Serial.println(activeTargetWait);
          Serial.print("waitTimeBegin=");Serial.println(waitTimeBegin);
          //Testing end
          currState=215;
          matrix.print(0xBBBB, HEX);
          matrix.blinkRate(1);
          matrix.writeDisplay();
        break;
      case 215:        //monitor time remaining for targetSecond to become active  
          if(i>waitTimeBegin+activeTargetWait)
            currState=220;
        break;
      case 220:         //display target on display
          //Testing begin
          Serial.println("state=220");
          //Testing end
          matrix.print(activeTargetSecond, DEC);
          matrix.blinkRate(0);
          matrix.writeDisplay();
          //record the time when the active target was displayed
          waitTimeBegin=i;
          //check if the target was already down before showing the number. That is a penalty
          if(digitalRead(targ_pin[activeTargetSecond-1])==HIGH)
          {
            delay(200);
            //play the fail sound
            playBadSound();
            delay(500);
            //Add to penalty
            penaltyTotal=penaltyTotal+wrongTargetPenalty;
            //Delay before moving to next target
            delay(1000);
            //Move on to third target
            currState=310;
          }
          else
          {
            currState=230;  //begin waiting for target to get hit
          }
        break;
      case 230:   //Wait for target to be hit or time to run out.
          //Testing begin
          //Serial.println("state=230");
          //Testing end
          if(digitalRead(targ_pin[activeTargetSecond-1])==HIGH || i-waitTimeBegin>maxTargetActiveTime_ms)
          {
            //get the time
            int delayTime_ms = i-waitTimeBegin;
            //Check if time ran out before the target was hit
            if(i-waitTimeBegin>maxTargetActiveTime_ms)
            {
              //Play bad sound
              playBadSound();
            }
            else
            {
              //play the hit sound
              playHitSound();
            }
            //calculate the penalty, this works the same if they hit the target or not
            float delayPenalty = getDelayPenalty(activeTargetSecond, delayTime_ms);
            //Add to penalty
            penaltyTotal=penaltyTotal+delayPenalty;
            //Delay before moving to next target
            delay(500);
            //Move to next target
            currState=310;
          }         
        break;
      case 310:
           //Testing begin
          Serial.println("state=310");
          //Testing end
          waitTimeBegin = i;
          activeTargetWait = random(2000,6000);
          //Testing begin
          Serial.print("activeTargetWait=");Serial.println(activeTargetWait);
          Serial.print("waitTimeBegin=");Serial.println(waitTimeBegin);
          //Testing end
          currState=315;
          matrix.print(0xCCCC, HEX);
          matrix.blinkRate(1);
          matrix.writeDisplay();
        break;
      case 315:          //monitor time remaining for targetThird to become active
          if(i>waitTimeBegin+activeTargetWait)
            currState=320;
        break;
      case 320:         //display target on display
          //Testing begin
          Serial.println("state=320");
          //Testing end
          matrix.print(activeTargetThird, DEC);
          matrix.blinkRate(0);
          matrix.writeDisplay();
          //record the time when the active target was displayed
          waitTimeBegin=i;
          //check if the target was already down before showing the number. That is a penalty
          if(digitalRead(targ_pin[activeTargetThird-1])==HIGH)
          {
            delay(200);
            //play the fail sound
            playBadSound();
            delay(500);
            //Add to penalty
            penaltyTotal=penaltyTotal+wrongTargetPenalty;
            //Delay before moving to next target
            delay(1000);
            //Done
            currState=400;
          }
          else
          {
            currState=330;  //begin waiting for target to get hit
          }
        break;
      case 330: //Wait for target to be hit or time to run out.
          //Testing begin
          //Serial.println("state=330");
          //Testing end
          if(digitalRead(targ_pin[activeTargetThird-1])==HIGH || i-waitTimeBegin>maxTargetActiveTime_ms)
          {
            //get the time
            int delayTime_ms = i-waitTimeBegin;
            //Check if time ran out before the target was hit
            if(i-waitTimeBegin>maxTargetActiveTime_ms)
            {
              //Play bad sound
              playBadSound();
            }
            else
            {
              //play the hit sound
              playHitSound();
            }
            //calculate the penalty, this works the same if they hit the target or not
            float delayPenalty = getDelayPenalty(activeTargetThird, delayTime_ms);
            //Add to penalty
            penaltyTotal=penaltyTotal+delayPenalty;
            //Delay before moving to next target
            delay(500);
             //That was the last target, we are done.
            currState=400;
          } 
        break;
      case 400:
          //Clear the display
          matrix.clear();
          matrix.writeDisplay();
          delay(100);
          playFinalSound();
          //Calculate the final score
          float finalScore = 100.0F-penaltyTotal;


          
          //Get the final score as integer
          int finalScoreInt = (int)finalScore;    
          //Testing begin                 
          Serial.print("finalScore=");Serial.println(finalScore);
          //Testing end
          //show score by counting up to the final value
          for(int n=30;n>=1;n--)
          {
            int tempVal = finalScoreInt/n;
            matrix.print(tempVal);
            matrix.writeDisplay();
            delay(100);
          }
          
          //Final delay to let the player see their score
          delay(10000);
          //Testing end
          
          //end the loop
          i=targetPracticeTimeMax_ms;
        break;
    }
    
    
    delay(1);
  }

  //Testing begin
  Serial.println("runTargetPractice end");
  delay(500);
  //Testing end
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

//Calculate a penalty for the delay in hitting the target
//targIndex should be 1,2, or 3
float getDelayPenalty(int targIndex, int delay_ms)
{
  //Check that the target index is valid
  if(targIndex<1 || targIndex>3)
  {
    Serial.println("getDelayPenalty: Invalid target index");
    return 0;
  }
  //If the max time was reached, then we assume the target was not hit
  if(delay_ms>=maxTargetActiveTime_ms)
  {
    return maxDelayPenalty;
  }
  
  //Calculate the penalty using the exponent that corresponds to this target
  float delayFloat_s = (float)delay_ms/1000.0F;
  float delayPenalty = pow(delayFloat_s, targetDelayPowPenalty[targIndex-1]);
  //Testing begin
  Serial.print("delayFloat_s=");Serial.println(delayFloat_s);
  Serial.print("delayPenalty=");Serial.println(delayPenalty);
  //Testing end
  return delayPenalty;

}
