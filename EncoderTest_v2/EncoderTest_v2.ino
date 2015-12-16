// Sweep Sample
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.

#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Servo ST1, ST2; // We'll name the Sabertooth servo channel objects ST1 and ST2.
                // For how to configure the Sabertooth, see the DIP Switch Wizard for
                //   http://www.dimensionengineering.com/datasheets/SabertoothDIPWizard/start.htm
                // Be sure to select RC Microcontroller Mode for use with this sample.
                //
                // Connections to make:
                //   Arduino Pin 9  ->  Sabertooth S1
                //   Arduino Pin 10 ->  Sabertooth S2
                //   Arduino GND    ->  Sabertooth 0V
                //   Arduino VIN    ->  Sabertooth 5V (OPTIONAL, if you want the Sabertooth to power the Arduino)
                //
                // Sabertooth accepts servo pulses from 1000 us to 2000 us.
                // We need to specify the pulse widths in attach(). 0 degrees will be full reverse, 180 degrees will be
                // full forward. Sending a servo command of 90 will stop the motor. Whether the servo pulses control
                // the motors individually or control throttle and turning depends on your mixed mode setting.

// Notice these attach() calls. The second and third arguments are important.
// With a single argument, the range is 44 to 141 degrees, with 92 being stopped.
// With all three arguments, we can use 0 to 180 degrees, with 90 being stopped.

volatile unsigned int counts;
unsigned int counts_copy;
unsigned int rpm;
unsigned long timeold;
unsigned long time_copy;

volatile float vel=0;
float vel_copy=0;

Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);
 
void setup()
{

//  noInterrupts();
//  //set timer0 interrupt every 15.4ms (65Hz)
//  TCCR0A = 0; //Set the TCCR0A register to 0
//  TCCR0B = 0;// same for TCCR0B
//  TCNT0  = 0;//initialize counter value to 0
//  //set compare match register for 500Hz increments
//  OCR0A=239;
//  // turn on CTC mode
//  TCCR0A |= (1 << WGM01);
//  // Set CS02 and CS00 bits for 1024 prescaler (that gives us 239 counts per interrupt to achieve 2ms interrupt)
//  TCCR0B |= (1 << CS02) | (1 << CS00);   
//  // enable timer compare interrupt
//  TIMSK0 |= (1 << OCIE0A);
//  interrupts();
  ST1.attach( 9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  //pinMode(2, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(3), rpm_fun, FALLING);
  Serial.begin(115200);

//  if(!gyro.begin())
//  {
//    /* There was a problem detecting the L3GD20 ... check your connections */
//    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }

//  noInterrupts();
//  ST2.write(90);
//  delay(1000);
//  interrupts();
  
  counts = 0;
  rpm = 0;
  timeold = 0;
}

void loop()
{
  
  ST2.write(0);
//
//  rpm=60000/(millis()-timeold)*counts/12;
//  timeold=millis();
//  counts=0;
//  Serial.println(rpm, DEC);

  //ST2.write(0);
  
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
    Serial.print(rpm,DEC);
    Serial.println(F(""));
    
  }

  //rpm_output=rpm/99;
}

void rpm_fun()
 {
   counts++;
   //Each rotation, this interrupt function is run 12 times
 }

// ISR(TIMER0_COMPA_vect){//timer0 interrupt 65Hz and gets velocity reading
//  sei();
//    /* Get a new sensor event */
//  sensors_event_t event;
//   
//  /* Display the results (gyrocope values in rad/s) */
//  gyro.getEvent(&event);
//  vel=event.gyro.z;
//
//  cli();
//  count++;
// }
