void Shield_correct(int shield_val, int output) {
  int newspeed5 = constrain(shield_val + output, -90, 90);
  int newspeed6 = constrain(shield_val - output, -90, 90);

  motor1.setSpeed(-newspeed5);
  motor2.setSpeed(-newspeed5);
  motor3.setSpeed(-newspeed6);
  motor4.setSpeed(-newspeed6);

//  Serial.print(" Shield correct");
}
void Back_Shield_correct(int shield_val, int output) {
  int newspeed15 = constrain(shield_val - output, -90, 90);
  int newspeed16 = constrain(shield_val + output, -90, 90);

  motor1.setSpeed(newspeed15);
  motor2.setSpeed(newspeed15);
  motor3.setSpeed(newspeed16);
  motor4.setSpeed(newspeed16);

//  Serial.print(" back Shield correct");
}
void tf_correct(int low_val, int dist) {
  int newspeed0 = constrain(low_val - dist, 0, 100);
  motor1.setSpeed(newspeed0);
  motor2.setSpeed(newspeed0);
  motor3.setSpeed(newspeed0);
  motor4.setSpeed(newspeed0);
//  Serial.println("TF Correct");
}
void tf_shield_correct(int orientation, int orientation_setpoint, int distance, int tf_setpoint, int output, int dist) {
  if ((orientation < (orientation_setpoint + 3)) && (orientation > (orientation_setpoint - 3))) {
    tf_PID(z_distance, fkp2, kd2, ki2, tf_setpoint);
    tf_correct(lval, dist);
  }
  else {
    backward(val);
    Back_Shield_correct(shield_val, output);
  }
}
void silo_correct(int turn_val, int silo_out) {
  if ((LSA_input == true) && (button_input1 == true && button_input2 == true) && (targetSilo == silo) && (silo_error >= -15 && silo_error <= 15) && (tf_input == false)) {
    siloFlag = true;
  }
  else if (silo_out > 0) {
    right_movePID(turn_val, silo_out);
  }
  else if (silo_out < 0) {
    left_movePID(turn_val, silo_out);
  }
}
void rightCorrect(int val, int out) {
  int newspeed1 = constrain(ball_val - out, -50, 50);
  int newspeed2 = constrain(ball_val + out, -50, 50);

  motor3.setSpeed(-newspeed1);
  motor4.setSpeed(-newspeed1);

  motor1.setSpeed(-newspeed2);
  motor2.setSpeed(-newspeed2);
  //  Serial.println("RightCorrect");
}
void leftCorrect(int ball_val, int out) {
  int newspeed3 = constrain(ball_val -  out, -50, 50);
  int newspeed4 = constrain(ball_val + out, -50, 50);

  motor3.setSpeed(-newspeed3);
  motor4.setSpeed(-newspeed3);
  motor1.setSpeed(-newspeed4);
  motor2.setSpeed(-newspeed4);
  //  Serial.println("leftCorrect");
}
void totalCorrect(int ball_val, int out, int pixy_error) {
  //  Serial.println("totalCorrect");
  if (pixy_error >= -100 && pixy_error <= 100 && pixy_error != 0 ) {
    ball_forward(ball_val, out);
    //    Serial.println("ballforward");
  }
  else if (out > 0) {
    rightCorrect(ball_val, out);
  }
  else if (out < 0) {
    leftCorrect(ball_val, out);
  }
}
void left_movePID(int turn_val, int silo_out) {
  int newspeed7 = constrain(turn_val - silo_out, -120, 120);
  int newspeed8 = constrain(turn_val - silo_out, -120, 120);
  // old constraints -80 to 80 working

  motor1.setSpeed(newspeed7);//Front L1
  motor2.setSpeed(-newspeed8);//back L2
  motor3.setSpeed(-newspeed8);//back R2
  motor4.setSpeed(newspeed7);//Front R1
//  Serial.println("Left move PID ");
}
void right_movePID(int turn_val, int silo_out) {
  int newspeed13 = constrain(turn_val + silo_out, -120, 120);
  int newspeed14 = constrain(turn_val + silo_out, -120, 120);
  // old constraints -80 to 80 working

  motor1.setSpeed(-newspeed13);//Front L1
  motor2.setSpeed(newspeed13);//back L2
  motor3.setSpeed(newspeed14);//back R2
  motor4.setSpeed(-newspeed14);//Front R1
//  Serial.print ("right move PID");
}
