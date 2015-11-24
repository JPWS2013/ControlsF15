
#include <Servo.h>
#include <TimerOne.h>

Servo ST1;

volatile int val=0;
int val_copy=0;
float volts=0;

float curr_err=0;
float one_err=0;
float two_err=0;
float one_out=0;
float two_out=0;
float angle=0;
float des_ang=0;
float curr_out=0;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ReadSensors);
  
  ST1.attach( 9, 1000, 2000);
  Serial.begin(9600);
  ST1.w

}

void loop() {
  // put your main code here, to run repeatedly:

  noInterrupts();
  val_copy=val;
  interrupts();

//  one_err=curr_err;
//  two_err=one_err;
//  one_out=curr_out;
//  two_out=one_out;
  
  volts=(val_copy/1023.0*5)-2.32;
  //curr_err=des_ang-(volts*0.565);
  //curr_out= (1.662*one_out) - (0.6637*two_out) + (2.697*curr_err) - (5.255*one_err) + (2.559*two_err);

  Serial.println(volts);

}

void ReadSensors(void)
{
  val=analogRead(0);
}

