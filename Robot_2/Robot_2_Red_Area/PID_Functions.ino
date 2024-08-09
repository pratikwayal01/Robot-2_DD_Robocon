double Shield_PID(double orientation_input, double kp1, double kd1, double ki1, int orientation_setpoint) {
  orientation_error = orientation_setpoint - orientation_input;
  P1 = kp1 * orientation_error;
  D1 = kd1 * (orientation_lastError - orientation_error);
  I1 = ki1 * (orientation_error + I1);

  orientation_lastError = orientation_error;
  output = P1 + I1 + D1;
  //    Serial.println(out);
  return output;
}
double computePID(double inp, double kp, double kd , double ki, int pixy_setpoint) {

  pixy_error = pixy_setpoint - inp;
  P = kp * pixy_error;
  D = kd * (pixy_lastError - pixy_error);
  I = ki * (pixy_error + I);

  pixy_lastError = pixy_error;
  out = P + I + D;
  //    Serial.println(out);
  return out;
}
double movePID(double orientation_input, double kp3, double kd3, double ki3, int move_setpoint) {
  move_error = move_setpoint - orientation_input;
  P3 = kp3 * move_error;
  D3 = kd3 * (orientation_lastError - orientation_error);
  I3 = ki3 * (orientation_error + I1);

  move_lastError = move_error;
  move_out = P3 + I3 + D3;
  //    Serial.println(out);
  return move_out;
}
double siloPID(double distance, double kp4, double kd4, double ki4, int siloSetpoint) {
  silo_error = siloSetpoint - distance;
  P4 = kp4 * silo_error;
  D4 = kd4 * (silo_lastError - silo_error);
  I4 = ki4 * (silo_error + I4);

  silo_lastError = silo_error;
  silo_out = P4 + I4 + D4;
  //    Serial.println(out);
  return silo_out;
}
double tf_PID(int distance, float kp2, float kd2, float ki2, int tf_setpoint) {
  tf_error = tf_setpoint - distance;
  P2 = kp2 * tf_error;
  D2 = kd2 * (tf_lastError - tf_error);
  I2 = ki2 * (tf_error + I2);
  tf_lastError = tf_error;
  dist = P2 + I2 + D2;
  return dist;
}
