#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

/* Assign a unique ID to the sensors */
/*Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);*/
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void displaySensorDetails(void)
{
  sensor_t sensor;

//  gyro.getSensor(&sensor);
//  Serial.println(F("------------- GYROSCOPE -----------"));
//  Serial.print  (F("Sensor:       ")); Serial.println(sensor.name);
//  Serial.print  (F("Driver Ver:   ")); Serial.println(sensor.version);
//  Serial.print  (F("Unique ID:    ")); Serial.println(sensor.sensor_id);
//  Serial.print  (F("Max Value:    ")); Serial.print(sensor.max_value); Serial.println(F(" rad/s"));
//  Serial.print  (F("Min Value:    ")); Serial.print(sensor.min_value); Serial.println(F(" rad/s"));
//  Serial.print  (F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println(F(" rad/s"));
//  Serial.println(F("------------------------------------"));
//  Serial.println(F(""));

  delay(500);
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Adafruit 9DOF Tester")); Serial.println("");
  
  /* Initialise the sensors */
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
   
  /* Display the results (gyrocope values in rad/s) */
  gyro.getEvent(&event);
//  Serial.print(F("GYRO  "));
  Serial.print(event.gyro.x); Serial.print(",");Serial.print(event.gyro.y);Serial.print(",");Serial.print(event.gyro.z);
  
  Serial.println(F(""));
  delay(100);
}
