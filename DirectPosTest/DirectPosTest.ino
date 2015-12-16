#include <Servo.h>

Servo ST1;
Servo ST2;

float raw_des_pos=0;
float raw_pos=0;
float des_pos=0;
float pos=0;
float err=0;
float motor_diff=0;
float motor_diff_raw=0;
int motor_out=0;

void setup() {
  // put your setup code here, to run once:

  ST1.attach(9, 1000, 2000);
  ST2.attach(10, 1000, 2000);
  ST1.write(90);
  ST2.write(0);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  raw_des_pos=analogRead(1);
  raw_pos=analogRead(0);
  pos=(raw_pos*0.0049)-2.32+0.1;
  des_pos=((raw_des_pos/1023.0*5.0)-2.5)/5.0*3.1415926;

  err=des_pos-pos;

  motor_diff_raw=err*35/1.5;

  if (motor_diff_raw>-25 && motor_diff_raw<-15){
    motor_diff=motor_diff_raw-5;
  }

  if (motor_diff_raw<25 && motor_diff_raw>15){
    motor_diff=motor_diff_raw+5;
  }
  
  motor_out=motor_diff+90;

  ST1.write(motor_out);
  Serial.println(pos);

}
