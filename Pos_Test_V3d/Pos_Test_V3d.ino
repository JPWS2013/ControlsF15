#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Servo ST1;
Servo ST2;

float curr_g=0;
float one_g=0;
float one_pos=0;
float curr_pos=0;

float curr_err=0;
float one_err=0;
float two_err=0;
float three_err=0;
float four_err=0;
float five_err=0;
float one_out=0;
float two_out=0;
float three_out=0;
float four_out=0;
float five_out=0;

float des_pos=0;
volatile float curr_out=0;
float curr_out_copy=0;
int motor_out=0;
float motor_diff=0;
float motor_diff_raw=0;

float vel=0;
//float vel_copy=0;

volatile int count=0;
int count_copy=0;

volatile unsigned int counts;
unsigned int counts_copy;
unsigned int rpm;
unsigned long timeold;
unsigned long time_copy;

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
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), rpm_fun, FALLING);
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
//  vel_copy=vel;
  curr_out_copy=curr_out;
  count_copy=count;
  interrupts();

//  if (count_copy>=180){
//    des_pos=-0.785;
//    count=0;
//  }
  
//  one_g=curr_g;
//  curr_g=vel_copy;
//  one_pos=curr_pos;
//
//  curr_pos=one_pos+0.007692*curr_g+0.007692*one_g;
//
//  two_err=one_err;
//  one_err=curr_err;
//  curr_err=des_pos-(curr_pos/2);
//  two_out=one_out;
//  one_out=curr_out;
//
//  curr_out=(0.4429*curr_err) - (0.8782*one_err) + (0.4353*two_err) + (1.877*one_out) - (0.8765*two_out);
   if (counts>=8){
    cli();
    counts_copy=counts;
    time_copy=millis()-timeold;
    timeold=millis();
    counts=0;
    sei();
    
    rpm = 60000/(time_copy)*counts_copy/12;
//    timeold = millis();
//    counts = 0;
//    Serial.print(rpm,DEC);
//    Serial.println(F(""));
    
  }
  motor_diff_raw=curr_out_copy*90;

    if (motor_diff_raw<-0.5){
    motor_diff=(motor_diff_raw+(1.5*(-25)))/1.5;
  }

  if (motor_diff_raw>0.5){
    motor_diff=(motor_diff_raw+(1.5*25))/1.5;
  }
  
//  if (motor_diff>-35 && motor_diff<-0.5){
//    motor_diff=-35;
//  }
//
//  if (motor_diff<35 && motor_diff>0.5){
//    motor_diff=35;
//  }
  
  motor_out=motor_diff+90;

  ST1.write(motor_out);
  ST2.write(0);

  Serial.println(rpm);
 
  //Serial.print(curr_out);Serial.print(",");Serial.print(curr_err);Serial.print(",");Serial.print(two_out);
  //Serial.println(" ");

 }

ISR(TIMER0_COMPA_vect){//timer0 interrupt 65Hz and gets velocity reading
  sei();
    /* Get a new sensor event */
  sensors_event_t event;
   
  /* Display the results (gyrocope values in rad/s) */
  gyro.getEvent(&event);
  vel=event.gyro.z;

  cli();

  one_g=curr_g;
  curr_g=vel;
  one_pos=curr_pos;

  curr_pos=one_pos+0.007692*curr_g+0.007692*one_g;

  five_err=four_err;
  four_err=three_err;
  three_err=two_err;
  two_err=one_err;
  one_err=curr_err;
  curr_err=des_pos-(curr_pos/2);
  five_out=four_out;
  four_out=three_out;
  three_out=two_out;
  two_out=one_out;
  one_out=curr_out;

//  curr_out=(0.09811*curr_err) - (0.1903*one_err) - (0.005797*two_err) + (0.1903*three_err) - (0.09231*four_err) + (3.487*one_out) - (4.542*two_out) + (2.619*three_out) - (0.5639*four_out);
//  curr_out=(0.1944*curr_err) - (0.005663*one_err) - (0.01204*two_err) + (0.01133*three_err) + (0.006019*four_err) - (0.005667*five_err) + (4.364*one_out)- (7.601*two_out) + (6.603*three_out) - (2.861*four_out) + (0.4946*five_out);
  curr_out=(0.1944*curr_err) - (0.5716*one_err) + (0.5601*two_err) - (0.1829*three_err) + (3.489*one_out)- (4.548*two_out) + (2.624*three_out) - (0.5655*four_out);
  count++;
}

void rpm_fun()
 {
   counts++;
   //Each rotation, this interrupt function is run 12 times
 }
