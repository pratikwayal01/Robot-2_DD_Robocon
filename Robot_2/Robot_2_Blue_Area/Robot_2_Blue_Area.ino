/*
  ======================================================================
  Author: Pratik Wayal
  Date: 2024-07-05
  Description: This Arduino sketch is writen Robot-2 (Fully Automatic)
               for  DD Robocon 2024. this code is in three parts
               1)Master Code (Arduino Mega-1)
               2)Slave1 Code (Arduino Mega-2)
               3)Slave2 code (Arduino Uno with 9 Axis Shield)
    Sensors Attacched to the Master Arduino Mega
    - Pixy2 Cam with SPI Communication
    - 3 Tf-Mini plus distance sendors (x,y,z)
      connected to the Srial 1,2,3
    - 3 freez Switch Buttons
  =======================================================================
*/
//================================| Libraries |================================
#include <SPI.h>
#include <Wire.h>
#include <Pixy2.h>
#include <PIDLoop.h>
#include "CytronMotorDriver.h"

Pixy2 pixy;

PIDLoop panLoop(400, 0, 400, true);
PIDLoop tiltLoop(500, 0, 500, true);

//================================| Pinouts |================================
CytronMD motor1(PWM_DIR, 7, 6);
CytronMD motor2(PWM_DIR, 9, 8);
CytronMD motor3(PWM_DIR, 3, 2);
CytronMD motor4(PWM_DIR, 5, 4);
CytronMD roller1(PWM_DIR, 11, 25);
CytronMD roller2(PWM_DIR, 12, 23);

#define button A9
#define button1 A10
#define button2 A11
#define roller_pin 22

#define LSA_pin 41
#define Signature_1 39
#define Signature_2 37
#define tf_pin 35

bool LSA_input = false;
bool Signature_pin1 = false;
bool Signature_pin2 = false;
bool tf_input = false;
int SignatureID = 0;
bool roller_button = 0;
/**
   @CytronMD motor(1-4)(PWM_DIR, *, *) these are 4 Moter pinouts.
   @CytronMD roller(1-2)(PWM_DIR, *, *) these are 2 Roller pinouts
   @button(0-2) are the button pins
   @LSA_pin is the digitalRead pin which read LSA data from Slave
   @Signature_pin1 and Signature_pin2 are two pins give signature
    from pixy connectd to the slave
   @tf_input gives wether the silo is full or not
*/
//================================| Mode |================================
int mod = 0; //****************************************************
//================================| TF-Mini |================================
#define X_DISTANCE Serial2
int x_distance = 0;

#define Y_DISTANCE Serial1
int y_distance = 0;

#define Z_DISTANCE Serial3
int z_distance = 0;

//================================|Millies|========================================

bool isSignature = false;
bool RflagRunning = false;
bool rollersRunning = false;
unsigned long checkingStartTime = 0;
unsigned long rollerStartTime = 0;
unsigned long Checkduration = 130;
unsigned long RflagStartTime = 0;
unsigned long silo_duration = 1500;
unsigned long duration1 = 2000;
unsigned long duration2 = 500;
//===================================|STACKS|====================================
const int NUM_STACKS = 5;
bool siloFullStatus[NUM_STACKS + 1] = {false};
//===============================|PID-shield|=========================================
double kp1 = 2.5;
double ki1 = 0.0;
double kd1 = 12.0;
int output = 0;
double P1 = 0;
double I1 = 0;
double D1 = 0;
int orientation = 0;
int orientation_error = 0;
int orientation_setpoint = 0;
int orientation_lastError = 0;

int signature = 0;
float cx = 0;
//====================================|Speeds|=======================================================
int val = 60;
int lval = 50;
int ball_val = 70;
int shield_val = 80;
int turnSpeed = 50;
int turn_val = 150;
int rollerspeed1 = 230;
int rollerspeed2 = 195;
int baseSpeed = 70;
int highSpeed = 255;
int search_val = 70;
int low_val = 20;
//=============================================| Flags |========================================================
bool forwardFlag = false;
bool turnFlag = false;
bool SFlag = false;
bool TFlag = false;
bool UFlag = false;
bool Rflag = false;
bool ballFlag = false;
bool backwardFlag = false;
bool wallFlag = false;
bool siloFlag = false;
bool rollerFlag = false;
bool backFlag = false;
bool IFlag = false;
bool checkFlag = false;
bool CheckTimeFlag = false;
bool modeFlag = false;
bool ballTurnFlag = false;
bool StopTurnFlag = false;
bool rollerStartFlag = false;

int targetSilo = 0;
int silo = 0;
//==============================|Functions|=============================================================
void Y_tfmini();
void X_tfmini();
void forward(int val);
void backward(int val);
void left(int val);
void right(int val);
void clockwise(int val);
void anticlockwise(int val);
void Stop();

//===========================================|Move PID|================================================
double kp3 = 15.0;
double ki3 = 0.0;
double kd3 = 5.0;//changed
int move_out = 0;
double P3 = 0;
double I3 = 0;
double D3 = 0;
int move_error = 0;
int move_setpoint = 0;
int move_lastError = 0;
//======================================|PIXY PID|=================================================
float kp = 4;
float ki = 0;
float kd = 10;
int out = 0;

double pixy_error = 0;
double pixy_lastError = 0;
double pixy_input = 0;
double inp = 0;
double P = 0;
double I = 0;
double D = 0;
int pixy_setpoint = 0;
bool button_input = false;
bool button_input1 = false;
bool button_input2 = false;
//==========================================|Tf-mini PID|=============================================
float kp2 = 0.4;
float fkp2 = 0.10;
float kd2 = 0;
float ki2 = 0;
double P2 = 0;
double I2 = 0;
double D2 = 0;
int dist = 0;
int tf_error = 0;
int tf_setpoint = 5;
int tf_lastError = 0;
//==============================|Silo_PID|====================================================================
float kp4 = 20;
float ki4 = 0;
float kd4 = 10;
int siloSetpoint = 0;
int silo_out = 0;
double silo_error = 0;
double silo_lastError = 0;
double P4 = 0;
double I4 = 0;
double D4 = 0;
//=========================================|Silo Distance Setpoints|===================================
//----------silo limits----------------
int minFirst = 0;
int silo1 = 25;
int maxFirst = 130;
int silo2 = 145;
int maxSecond = 230;
int silo3 = 245;
int maxThird = 310;
int silo4 = 325;
int maxFourth = 385;
int silo5 = 400;
int maxFifth = 420;
//==========================================|Setup|===================================================
void setup() {
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);
  X_DISTANCE.begin(115200);
  Y_DISTANCE.begin(115200);
  Z_DISTANCE.begin(115200);
  Serial.begin(9600);
  pixy.init();
  pixy.changeProg("color_connected_components");

  panLoop.reset();
  tiltLoop.reset();
  pixy.setServos(500, 700);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  //======================================|PinModes|===============================================
  pinMode(button, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(LSA_pin, INPUT_PULLUP);
  pinMode(Signature_1, INPUT_PULLUP);
  pinMode(Signature_2, INPUT_PULLUP);
  pinMode(tf_pin, INPUT_PULLUP);
  pinMode(roller_button, INPUT_PULLUP);
}

void loop() {
  signature = checkID();
  signature_receive(Signature_pin1, Signature_pin2);
  silo = checkSilo();
  X_tfmini();
  Y_tfmini();
  Z_tfmini();
  LSA_input = digitalRead(LSA_pin);
  tf_input = digitalRead(tf_pin);
  Signature_pin1 = digitalRead(Signature_1);
  Signature_pin2 = digitalRead(Signature_2);
  button_input = digitalRead(button);
  button_input1 = digitalRead(button1);
  button_input2 = digitalRead(button2);
  roller_button = digitalRead(roller_pin);
  if (roller_button == HIGH) {
    roller2.setSpeed(-highSpeed);
    roller1.setSpeed(highSpeed);
  }
  else if (mod == 0) {
    if (forwardFlag == false) {
      tf_shield_correct(orientation, orientation_setpoint, z_distance, tf_setpoint, output, dist);
      if ((z_distance > 20 && z_distance < 50)) {
        forwardFlag = true;
        orientation_setpoint = -90;
        mod++;
      }
    }
  }
  else if (mod == 1) {
    if (orientation_setpoint == -90 && turnFlag == false) {
      Back_Shield_correct(turnSpeed, output);
      if (orientation == -90) {
        turnFlag = true;
      }
    }
    else if ( turnFlag  == true) {
      backward(val);
      Back_Shield_correct(shield_val, output);
      if ((z_distance > 160 && z_distance < 240) && (x_distance < 700 && x_distance > 60) ) {
        orientation_setpoint = 0;
        mod++;
        turnFlag = false;
      }
    }
  }
  else if (mod == 2) {
    if (orientation_setpoint == 0 && SFlag == false) {
      Back_Shield_correct(turnSpeed, output);
      if (orientation == 0) {
        SFlag  = true;
      }
    }
    else if (SFlag == true) {
      Back_Shield_correct(shield_val, output);
      backward(val);
      if ((z_distance < 60  && z_distance > 30)) {
        orientation_setpoint = -80;
        mod++;
        SFlag = false;
      }
    }
  }
  else if (mod == 3) {
    if (TFlag == false && orientation_setpoint == -90) {
      Back_Shield_correct(-shield_val, output);
      if ((orientation == -80)) {
        TFlag = true;
      }
    }
    else if (TFlag == true && UFlag == false) {
      Back_Shield_correct(-val, output);
      forward(val);
      if (y_distance < 150 && y_distance > 0) {
        UFlag = true;
      }
    }
    else if (UFlag == true && IFlag == false) {
      orientation_setpoint = 0;
      Back_Shield_correct(-turnSpeed, output);
      if (orientation == 0) {
        IFlag = true;
      }
    }
    if (IFlag == true && SFlag == false) {
      Back_Shield_correct(-val, output);
      forward(low_val);
      if ((y_distance < 50 && y_distance > 0) || signature > 0) {
        IFlag = false;
        SFlag = true;
        mod++;
      }
    }
  }
  if (mod == 4) {
    siloFlag = false;
    rollerFlag = false;
    backFlag = false;
    SFlag  = false;
    backwardFlag = false;
    if (ballFlag == false) {
      ball_follow();
    }
    if (Rflag == true) {
      ballFlag = true;
      roller2.setSpeed(-rollerspeed1);
      if (button_input == HIGH) {
        roller1.setSpeed(0);
        roller2.setSpeed(0);
        CheckTimeFlag = true;
        Rflag = false;
      }
      checkRflag();
    }
    else if (CheckTimeFlag == true && Rflag == false) {
      checkTime(Checkduration) ;
    }
    else if (checkFlag == true) {
      if (SignatureID == 2) {
        rollerStartFlag = true;
      }
      if (rollerStartFlag == true) {
        orientation_setpoint = 0;
        Back_Shield_correct(-shield_val, output);
        Roller(duration2);
      }
      else if (SignatureID == 0 && modeFlag == false) {
        ballFlag = false;
        mod = 4;
      }
      else if (SignatureID == 1 && CheckTimeFlag == false) {
        modeFlag = true;
        checkFlag = false;
        Rflag = false;
        ballFlag = true;
        orientation_setpoint = -90;
      }
    }

    if (ballFlag == true &&  modeFlag == true) {
      panLoop.reset();
      tiltLoop.reset();
      pixy.setServos(500, 700);
      mod++;
    }
  }
  else if (mod == 5) {
    if (backwardFlag == false) {
      if ((z_distance < 10 && z_distance >= 0) && (button_input1 == false || button_input2 == false) && StopTurnFlag == false) {
        ballTurnFlag = true;
      }
      else if ((z_distance < 180 && z_distance > 0) && LSA_input == true) {
        ballTurnFlag = false;
        StopTurnFlag = true;
      }
      if (ballTurnFlag == true) {
        if (button_input1 == true || button_input2 == true) {
          //          Serial.println("Function IF stuck");
          StopTurnFlag = true;
          ballTurnFlag = false;
        }
        else {
          //          Serial.println("Function else  stuck");
          if (z_distance > 20 && z_distance != 0) {
            ballTurnFlag = false;
          }
          else if (x_distance < 40) {
            right_move(val);
          }
          else {
            left_move(val);
          }
        }
      }
      else {
        if ((orientation < -85 && orientation > -95)) {
          tf_PID(z_distance, kp2, kd2, ki2, tf_setpoint);
          tf_correct(low_val, dist);
        }
        else {
          backward(val);
          Back_Shield_correct(shield_val, output);
        }
      }
      if (button_input1 == true && button_input2 == true) {
        targetSilo = silo;
        siloSetpoint = check_SiloSetpoint(targetSilo);
        ballTurnFlag = false;
        modeFlag = false;
        StopTurnFlag = false;
        wallFlag = true;
        backwardFlag = true;
        ballFlag = false;
        mod++;
      }
    }
  }
  else if (mod == 6) {
    if (wallFlag == true) {
      if ((LSA_input == true) && (button_input1 == true && button_input2 == true) && (targetSilo == silo)) {
        if (tf_input == true) {
          targetSilo = changeTargetSilo(targetSilo);
          siloSetpoint = check_SiloSetpoint(targetSilo);
        }
        else {
          siloFlag = true;
        }
      }
      if (button_input1 == true && button_input2 == true) {
        siloPID(x_distance, kp4, kd4, ki4, siloSetpoint);
        silo_correct(turn_val, silo_out);
      }
      else {
        move_setpoint = orientation;
        Back_Shield_correct(baseSpeed, move_out);
      }
    }
    //=====================================

    if (siloFlag == true) {
      wallFlag = false;
      Stop();// to  be tested
      Roller2(rollerspeed2, silo_duration);
    }
    if (rollerFlag == true) {
      orientation_setpoint = -90;
      mod++;
    }
  }
  if (mod == 7) {
    if (backFlag == false) {
      Back_Shield_correct(-shield_val, output);
      forward(val);
      if ((y_distance > 0 && y_distance < 150 && y_distance != 0)) {
        pixy_error = 0;
        Stop();
        backFlag = true;
      }
    }
    if (backFlag == true) {
      mod = 4;
    }
  }
  //  Debugging();
}
