float pixyCheck() {
  static int i = 0;
  int j;
  char buf[64];
  int32_t panOffset, tiltOffset;

  // get active blocks from Pixy
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks )
  {
    i++;

    // calculate pan and tilt "errors" with respect to first object (blocks[0]),
    // which is the biggest object (they are sorted by size).
    panOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t)pixy.ccc.blocks[0].m_y - (int32_t)pixy.frameHeight / 2;

    // update loops
    panLoop.update(panOffset);
    tiltLoop.update(tiltOffset);

    // set pan and tilt servos
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
    cx = map(panLoop.m_command, 0, 500, -500, 0);
    return cx;
  }
  else if (tiltLoop.m_command < 200 && signature > 0) {
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(500, 700);
  }
  else {
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(500, 700);
  }
}
int checkID() {
  pixy.ccc.getBlocks();
  // If there are detected blocks, return the signature ID of the first block
  if (pixy.ccc.numBlocks > 0) {
    return pixy.ccc.blocks[0].m_signature;
  } else {
    // Return -1 if no blocks are detected
    return -1;
  }
}
void ball_follow() {
  double pixy_input = pixyCheck();
  computePID(pixy_input, kp, kd, ki, pixy_setpoint);
  if (signature > 0) {
    totalCorrect(ball_val, out, pixy_error);
    if ((y_distance < 40 && y_distance > 0) && (pixy_error >= -90 && pixy_error <= 90 && pixy_error != 0 )) {
      Rflag = true;
    }
  }
  else {
    SearchMotions();
  }
  //    Serial.println("Ball follow");
}

void SearchMotions() {
  if (x_distance < 150 && x_distance > 50) {
    left_move(search_val);
  }
  else {
    clockwise(lval);
  }
}
