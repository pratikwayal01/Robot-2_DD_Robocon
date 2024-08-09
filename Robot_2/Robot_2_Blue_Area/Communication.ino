int receiveEvent(int howMany)
{
  while (1 < Wire.available())
  {
    int X = Wire.read();
    int Y = Wire.read();
    int Z = Wire.read();
    orientation = X * 100 + Y * 10 + Z;
  }
  if ( orientation > 180) {
    orientation =  orientation - 360;
  }
  Shield_PID(orientation,kp1, kd1, ki1, orientation_setpoint);
  return orientation;
}

int signature_receive(bool Signature_pin1, bool Signature_pin2) {
  if (Signature_pin1 == LOW && Signature_pin2 == HIGH ) {
    SignatureID = 2;
  }
  else if (Signature_pin2 == LOW && Signature_pin1 == HIGH) {
    SignatureID = 1;
  }
  else {
    SignatureID = 0;
  }
  return SignatureID;
}
