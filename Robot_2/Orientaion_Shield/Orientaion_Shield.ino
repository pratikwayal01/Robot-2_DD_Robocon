/*
  ======================================================================
  Author: Pratik Wayal
  Date: 2024-07-05
  Description: This Arduino sketch is writen Robot-2 (Fully Automatic)
               for  DD Robocon 2024. this code is in three parts
               1)Master Code (Arduino Mega-1)
               2)Slave1 Code (Arduino Mega-2)
               3)Slave2 code (Arduino Uno with 9 Axis Shield)
    Sensors Attacched to the this Uno
    - Arduino 9 axis Orientation Shield.
  =======================================================================
*/

#include "Arduino_NineAxesMotion.h"
float Q;
int X, Y, Z;
NineAxesMotion mySensor;
unsigned long lastStreamTime = 0;
const int streamPeriod = 5;

void setup() {

  Serial.begin(9600);
  Wire.begin(8);
  mySensor.initSensor();
  mySensor.setOperationMode(OPERATION_MODE_NDOF);
  mySensor.setUpdateMode(MANUAL);
}
void loop() {
  if ((millis() - lastStreamTime) >= streamPeriod)
  {
    lastStreamTime = millis();
    mySensor.updateEuler();
    mySensor.updateCalibStatus();
    Q = mySensor.readEulerHeading();
    int S = Q;
    if (S < 360) {
//      Serial.println(S);
      split(S);
      Wire.beginTransmission(8);
      Wire.write(X);
      Wire.write(Y);
      Wire.write(Z);
      Wire.endTransmission();
    }
  }
}


int split(int num) {
  X = num / 100;
  int num1 = num % 100;
  Y = num1 / 10;
  Z = num1 % 10;

  return X, Y, Z;
}
