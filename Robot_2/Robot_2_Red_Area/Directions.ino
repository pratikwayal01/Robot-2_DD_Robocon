void ball_forward(int ball_val, int out) {
  motor1.setSpeed(-ball_val);
  motor2.setSpeed(-ball_val);
  motor3.setSpeed(-ball_val);
  motor4.setSpeed(-ball_val);

  //  Serial.println("Ball Forward");
}
void forward(int val) {
  motor1.setSpeed(-val);
  motor2.setSpeed(-val);
  motor3.setSpeed(-val);
  motor4.setSpeed(-val);
  //  Serial.print(" Forward");
}
void backward(int val) {
  motor1.setSpeed(val);
  motor2.setSpeed(val);
  motor3.setSpeed(val);
  motor4.setSpeed(val);
}
void left_move(int turn_val) {

  motor1.setSpeed(turn_val);//Front L1
  motor2.setSpeed(-turn_val);//back L2
  motor3.setSpeed(-turn_val);//back R2
  motor4.setSpeed(turn_val);//Front R1
//  Serial.println("Left move");
}
void right_move(int turn_val) {
  motor1.setSpeed(-turn_val);//Front L1
  motor2.setSpeed(turn_val);//back L2
  motor3.setSpeed(turn_val);//back R2
  motor4.setSpeed(-turn_val);//Front R1
//  Serial.println("right move");
}
void clockwise(int val) {
  motor1.setSpeed(-val);
  motor2.setSpeed(-val);
  motor3.setSpeed(val);
  motor4.setSpeed(val);

}
void anticlockwise(int val) {
  motor1.setSpeed(val);
  motor2.setSpeed(val);
  motor3.setSpeed(-val);
  motor4.setSpeed(-val);

}

void Stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  //  Serial.print(" Stop");
}
