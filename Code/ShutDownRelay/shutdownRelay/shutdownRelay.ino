//  www.zolalab.com.br  -  By Eduardo Zola  -  2016


void setup() 
{
   pinMode(11,OUTPUT);    // Relay Signal Pin
   digitalWrite(11,LOW);   //Low signal turns the relay on

   pinMode(8,OUTPUT);     // buzzer & LED  (start with buzzer on)
   digitalWrite(8,HIGH);  

   pinMode(13,OUTPUT);   // LED built-in Arduino
   digitalWrite(13,HIGH);

   delay(50);           
   digitalWrite(8,LOW);   // turn off buzzer


   delay(5000);   // wait for 5 seconds to shutdown the circuit


   for(int i = 0;i<3;i++) {digitalWrite(8,HIGH);delay(80);digitalWrite(8,LOW);delay(600);};   // beeps
   digitalWrite(8,HIGH);delay(1000);digitalWrite(8,LOW);
   
   digitalWrite(11,HIGH);  // shutdown the circuit
   
}

void loop() 
{

}
