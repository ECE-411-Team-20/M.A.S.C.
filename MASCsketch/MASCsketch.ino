/*
M.A.S.C.

This program is designed to control an automated
mask.

-The mask must be able to detect when it needs to 
  close to prevent the user contracting any airborne 
  diseases. 
-The mask will be able to detect it based on the 
  distance of the user to another human, in which 
  the mask will close upon close proximity to 
  someone else. 
-The mask must close when the user is walking. 
  The mask must open when nobody is near them. 
-The mask must be a portable device that can 
  fit on the user’s face. 
-The mask must be as lightweight as possible 
  and comfortable on the wearer’s head. 
-The mask must allow the user to breathe.


*Requirements aboveSpecified
If a heat signature moves within 3 meters of the user,
the mask will close.

If we sense motion over a certain amount that 
might indicate walking movement, the mask will close.

If no one is around AND acceleration in X or Y direction 
is under () meters per second squared, the mask will open.
*/

#include "Wire.h"     // I2C communication library

//Passive InfraRed Motion Sensor Pin
#define sensorPin 18      // package pin4 PD2(INT0) PCINT18

//Servo Actuator Pin
#define servoPin 19       // package pin5 PD3(INT1) PCINT19 PWM

const int MPU_ADDR = 0x68;    //I2C address of the MPU-6050 Accelerometer


/*
//Don't really need all of them,
//just displaying register addresses for reference

//MPU-6050 registers for Accelerometer
const int ACCEL_XOUT_H = 0x3B;
const int ACCEL_XOUT_L = 0x3C;
const int ACCEL_YOUT_H = 0x3D;
const int ACCEL_YOUT_L = 0x3E;
const int ACCEL_ZOUT_H = 0x3F;
const int ACCEL_ZOUT_L = 0x40;

//MPU-6050 registers for temperature sensor
const int TEMP_OUT_H = 0x41;
const int TEMP_OUT_L = 0x42;

//MPU-6050 registers for Gyroscope
const int GYRO_XOUT_H = 0x43;
const int GYRO_XOUT_L = 0x44;
const int GYRO_YOUT_H = 0x45;
const int GYRO_YOUT_L = 0x46;
const int GYRO_ZOUT_H = 0x47;
const int GYRO_ZOUT_L = 0x48;
*/

//16 bit integers for sensor values
int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int16_t temperature;
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);   //begins transmission to 
  Wire.write(0x6B);     // PWR_MGMT_1 register
  Wire.write(0);        // set CLKSEL to 0 which turns on internal 8MHz oscillator
  Wire.endTransmission(true); 
}

void loop() {
  
  Wire.beginTransmission(MPU_ADDR);
  
  Wire.write(ACCEL_XOUT_H);             // This is the first register in the data registers, 
                                        // we begin reading here                                   
  Wire.endTransmission(false);          // sends restart message to MPU-6050 and keeps connection open
  
  Wire.requestFrom(MPU_ADDR, 14, true); // request data from 14 byte registers and send stop message.

  //read in all data from MPU-6050
  accel_x = Wire.read()<<8 | Wire.read();   //reads ACCEL_XOUT_H and ACCEL_XOUT_L registers
  accel_y = Wire.read()<<8 | Wire.read();   //reads ACCEL_YOUT_H and ACCEL_YOUT_L registers
  accel_z = Wire.read()<<8 | Wire.read();   //reads ACCEL_ZOUT_H and ACCEL_ZOUT_L registers
  temperature = Wire.read()<<8 | Wire.read();   //reads TEMP_OUT_H and TEMP_OUT_L registers
  gyro_x = Wire.read()<<8 | Wire.read();    //reads GYRO_ZOUT_H and GYRO_ZOUT_L registers
  gyro_y = Wire.read()<<8 | Wire.read();    //reads GYRO_ZOUT_H and GYRO_ZOUT_L registers
  gyro_z = Wire.read()<<8 | Wire.read();    //reads GYRO_ZOUT_H and GYRO_ZOUT_L registers
  
  //print to console all data from MPU-6050
  Serial.print("Accelerometer (X, Y, Z) = (");
  Serial.print(accel_x); Serial.print(", ");
  Serial.print(accel_y); Serial.print(", ");
  Serial.print(accel_z); Serial.println(")");

  Serial.print("Gyroscope (X, Y, Z) = (");
  Serial.print(gyro_x); Serial.print(", ");
  Serial.print(gyro_y); Serial.print(", ");
  Serial.print(gyro_z); Serial.println(")");

  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.println();
}
