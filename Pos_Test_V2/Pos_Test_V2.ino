#include <Servo.h>

Servo ST1;

volatile int val=0;
int val_copy=0;
float volts=0;
float ang=0;

float curr_err=0;
float one_err=0;
float two_err=0;
float one_out=0;
float two_out=0;
float angle=0;
float des_ang=-1.5;
float curr_out=0;
int motor_out=0;
int motor_diff=0;


void setup() {
  //Set the nointerrupt call so that setting the registers isn't interrupted by the interrupt
  noInterrupts();
  //set timer0 interrupt every 2ms (500Hz)
  TCCR0A = 0; //Set the TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  //set compare match register for 500Hz increments
  OCR0A=124;
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS02 bit for 256 prescaler (that gives us 124 counts per interrupt to achieve 2ms interrupt)
  TCCR0B |= (1 << CS02);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  interrupts();

  ST1.attach(9, 1000, 2000);
  ST1.write(90);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  noInterrupts();
  val_copy=val;
  //val=0;
  interrupts();

  one_err=curr_err;
  two_err=one_err;
  one_out=curr_out;
  two_out=one_out;
  
  volts=(val_copy*0.0049)-2.32;
  ang=volts/1.13;

  curr_err=des_ang-ang;
  curr_out= (1.662*one_out) - (0.6637*two_out) + (2.697*curr_err) - (5.255*one_err) + (2.559*two_err);

  motor_diff=curr_out*35;

  if (motor_diff>-25 && motor_diff<-3){
    motor_diff=-25;
  }

  if (motor_diff<25 && motor_diff>3){
    motor_diff=25;
  }
  
  motor_out=motor_diff+90;

  ST1.write(motor_out);
 
  Serial.println(ang);

}

ISR(TIMER0_COMPA_vect){//timer0 interrupt 500Hz and gets pot reading
  val=analogRead(0);
}

//void ReadSensors(void)
//{
//  val=analogRead(0);
//}

