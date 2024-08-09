/*
  ======================================================================
  Author: Pratik Wayal
  Date: 2024-07-05
  Description: This Arduino sketch is writen Robot-2 (Fully Automatic)
               for  DD Robocon 2024. this code is in three parts
               1)Master Code (Arduino Mega-1)
               2)Slave1 Code (Arduino Mega-2)
               3)Slave2 code (Arduino Uno with 9 Axis Shield)
    Sensors Attacched to this Slave Arduino Mega 
    - Pixy2 Cam with SPI Communication
    - 1 Tf-Mini plus distance sendors (z)
      connected to the Srial 3
    - 1 LSA08 Attached to Serial1
  =======================================================================
*/
#include <LSA08.h>
#include <Pixy2.h>

// This is the main Pixy object
Pixy2 pixy;

int SignatureID = 0;
#define LSASerial Serial1
LSA08 L;

#define Z_DISTANCE Serial3
int z_distance = 0;
bool tf_out = 0;

int LSA_input = 0;
bool LSA_out = 0;

#define LSA_pin 37
#define Signature_1 39
#define Signature_2 41
#define tf_pin 43
/**
   @LSA_pin is the digitalRead pin which send LSA data from Slave to master
   @Signature_pin1 and Signature_pin2 are two pins give signature
    from pixy connectd to the slave
   @tf_input gives wether the silo is full or not
*/
void setup() {
  Serial.begin(9600);
  //  Serial.print("Starting...\n");
  pixy.init();
  pixy.changeProg("color_connected_components");
  LSASerial.begin(38400);
  L.AttachSerial(&LSASerial);
  Serial3.begin(115200);
  Z_DISTANCE.begin(115200);
  //===============================================
  pinMode(LSA_pin, OUTPUT);
  pinMode(Signature_1, OUTPUT);
  pinMode(Signature_2, OUTPUT);
  pinMode(tf_pin, OUTPUT);
  digitalWrite(LSA_pin, LOW);
  digitalWrite(Signature_1, LOW);
  digitalWrite(Signature_2, LOW);
  digitalWrite(tf_pin, LOW);
}

void loop() {
  Z_tfmini();
  SignatureID = checkID();
  LSA_input = L.ReadLSA();
  LSA_out = LSA_Encode(LSA_input);
  tf_out = tf_Encode(z_distance);
  //    Serial.print(" z_distance: "); Serial.print(z_distance);
  //    Serial.print(" tf_out: "); Serial.print(tf_out);
  //  Serial.print(" LSA_input: "); Serial.print(LSA_input);
  //  Serial.print(" LSA_out: "); Serial.print(LSA_out);
  //  Serial.print(" signature: "); Serial.print(SignatureID);
  //      Serial.println();
  LSA_send(LSA_out);
  tf_send(tf_out);
  signature_send(SignatureID);
}
int checkID() {
  pixy.ccc.getBlocks();
  // If there are detected blocks, return the signature ID of the first block
  if (pixy.ccc.numBlocks > 0) {
    return pixy.ccc.blocks[0].m_signature;
  } else {
    // Return 0 if no blocks are detected
    return 0;
  }
}
bool LSA_Encode(int LSA_input) {
  return (LSA_input > 10 && LSA_input < 40);
}
void LSA_send(bool LSA_out) {
  if (LSA_out == 1) {
    digitalWrite(LSA_pin, HIGH);
  }
  else {
    digitalWrite(LSA_pin, LOW);
  }
}
void tf_send(bool tf_out) {
  if (tf_out == 1) {
    digitalWrite(tf_pin, HIGH);
  }
  else {
    digitalWrite(tf_pin, LOW);
  }
}
void signature_send(int SignatureID) {
  if (SignatureID == 1) {
    digitalWrite(Signature_1, HIGH);
    digitalWrite(Signature_2, LOW);
  }
  else if (SignatureID == 2) {
    digitalWrite(Signature_2, HIGH);
    digitalWrite(Signature_1, LOW);
  }
  else {
    digitalWrite(Signature_1, LOW);
    digitalWrite(Signature_2, LOW);
  }
}
void Z_tfmini()
{
  while (Z_DISTANCE.available() >= 9)
  {
    if ((0x59 == Z_DISTANCE.read()) && (0x59 == Z_DISTANCE.read()))
    {
      unsigned int t1z =  Z_DISTANCE.read();
      unsigned int t2z = Z_DISTANCE.read();
      t2z <<= 8;
      t2z += t1z;
      z_distance = t2z;
      t1z = Z_DISTANCE.read();
      t2z = Z_DISTANCE.read();
      t2z <<= 8;
      t2z += t1z;
    }
  }
}
bool tf_Encode(int z_distance) {
  return (z_distance > 0 && z_distance < 50);
}
