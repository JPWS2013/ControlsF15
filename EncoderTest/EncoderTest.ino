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

byte counts;
volatile short rpm;
unsigned int timeold;
//unsigned int time_mins;
byte rpm_output;
//volatile boolean show;
 
void setup()
{
  ST1.attach( 9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  pinMode(13, OUTPUT);

  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(3), rpm_fun, FALLING);
  counts = 0;
  rpm = 0;
  timeold = 0;
  //show=false;
}

void loop()
{
  ST1.write(65);
  //Serial.println(show);

  rpm_output=rpm/99;
  Serial.println(rpm_output);

  
  
}

void rpm_fun()
 {
   counts++;
   //Each rotation, this interrupt function is run twice
   
   if (counts >= 12) { 
     //show=true;
     //Update RPM every 12 counts (1 revolution)
     
     //time_mins=(millis() - timeold)/(1000.0*60.0);
     //Serial.println(time_mins);
     
     rpm = counts*60000/(millis()-timeold);
     
     timeold = millis();
     
     //Serial.println(timeold);
     
     counts = 0;
     
     //rpm_output=rpm/99;
   }
 }
