#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Servo ST1;
Servo ST2;

//volatile int val=0;
//int val_copy=0;
//float volts=0;
//float ang=0;

float curr_g=0;
float one_g=0;
float one_pos=0;
float curr_pos=0;

float curr_err=0;
float one_err=0;
float two_err=0;
float one_out=0;
float two_out=0;

//float angle=0;
float des_pos=0;
float curr_out=0;
int motor_out=0;
int motor_diff=0;

volatile float vel=0;
float vel_copy=0;

volatile int count=0;
int count_copy=0;

Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void setup() {
  //Set the nointerrupt call so that setting the registers isn't interrupted by the interrupt
  noInterrupts();
  //set timer0 interrupt every 15.4ms (65Hz)
  TCCR0A = 0; //Set the TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  //set compare match register for 500Hz increments
  OCR0A=239;
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS02 and CS00 bits for 1024 prescaler (that gives us 239 counts per interrupt to achieve 2ms interrupt)
  TCCR0B |= (1 << CS02) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  interrupts();

  ST1.attach(9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  ST1.write(90);
  ST2.write(0);
  Serial.begin(9600);

    if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  noInterrupts();
  vel_copy=vel;
  count_copy=count;
  count=0;
  interrupts();

//  if (count_copy>=30){
//    des_pos=1.57;
//  }
  
  one_g=curr_g;
  curr_g=vel_copy;
  one_pos=curr_pos;

  curr_pos=one_pos+0.007692*curr_g+0.007692*one_g;

  two_err=one_err;
  one_err=curr_err;
  curr_err=des_pos-(curr_pos/2);
  two_out=one_out;
  one_out=curr_out;

  curr_out=(0.6555*curr_err) - (1.3*one_err) + (0.6443*two_err) + (1.877*one_out) - (0.8756*two_out);

  motor_diff=curr_out*35;

  if (motor_diff>-25 && motor_diff<-3){
    motor_diff=-25;
  }

  if (motor_diff<25 && motor_diff>3){
    motor_diff=25;
  }
  
  motor_out=motor_diff+90;

  ST1.write(motor_out);
  ST2.write(0);
 
  Serial.print(curr_out);Serial.print(",");Serial.print(curr_err);Serial.print(",");Serial.print(two_out);
  Serial.println(" ");

 }

ISR(TIMER0_COMPA_vect){//timer0 interrupt 65Hz and gets pot reading
  sei();
    /* Get a new sensor event */
  sensors_event_t event;
   
  /* Display the results (gyrocope values in rad/s) */
  gyro.getEvent(&event);
//  Serial.print(F("GYRO  "));
  vel=event.gyro.z;

  cli();
//  count++;
}

//void ReadSensors(void)
//{
//  val=analogRead(0);
//}

