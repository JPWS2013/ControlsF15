#include <TimerOne.h>

volatile int val=0;
int val_copy=0;
float volts=0;
float ang=0;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ReadSensors);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  noInterrupts();
  val_copy=val;
  interrupts();
  
  volts=(val_copy/1023.0*5)-2.32;
  ang=volts*0.565;
  
 
  Serial.println(ang);

}

void ReadSensors(void)
{
  val=analogRead(0);
}

