#include <Servo.h>
Servo ST1, ST2;

volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;
 void setup()
 {
   ST1.attach( 9, 1000, 2000);
   Serial.begin(9600);
   attachInterrupt(0, rpm_fun, RISING);
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
   
 }
 void loop()
 {
  ST1.write(0);
  
   if (half_revolutions >= 12) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     rpm = 60*1000/(millis() - timeold)*half_revolutions/12;
     timeold = millis();
     half_revolutions = 0;
     Serial.println(rpm,DEC);
   }
 }
 void rpm_fun()
 {
   half_revolutions++;
   //Each rotation, this interrupt function is run twice
 }
