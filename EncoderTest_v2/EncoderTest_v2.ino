// Sweep Sample
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.

#include <Servo.h>

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

volatile byte counts;
unsigned int rpm;
unsigned long timeold;
 
void setup()
{
  ST1.attach( 9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  //pinMode(2, INPUT_PULLUP);
  
  //attachInterrupt(digitalPinToInterrupt(3), rpm_fun, FALLING);
  Serial.begin(115200);

  noInterrupts();
  ST1.write(90);
  delay(1000);
  interrupts();
  
  counts = 0;
  rpm = 0;
  timeold = 0;
}

void loop()
{
  
  ST1.write(90);
//
//  rpm=60000/(millis()-timeold)*counts/12;
//  timeold=millis();
//  counts=0;
//  Serial.println(rpm, DEC);

  //ST2.write(0);
  
  if (counts>=4){
    
    rpm = 60000/(millis() - timeold)*counts/12;
    timeold = millis();
    counts = 0;
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
