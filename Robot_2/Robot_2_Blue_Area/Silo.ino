int check_SiloSetpoint(int targetSilo) {
  if (targetSilo == true) {
    siloSetpoint = silo1;
  }
  else if (targetSilo == 2) {
    siloSetpoint = silo2;
  }
  else if (targetSilo == 3) {
    siloSetpoint = silo3;
  }
  else if (targetSilo == 4) {
    siloSetpoint = silo4;
  }
  else if (targetSilo == 5) {
    siloSetpoint = silo5;
  }
  return siloSetpoint;
}
int checkSilo() {
  if ((x_distance > minFirst && x_distance < maxFirst) ) {
    return 1;
  }
  else if ((x_distance > maxFirst && x_distance <= maxSecond)) {
    return 2;
  }
  else if ((x_distance > maxSecond && x_distance < maxThird) ) {
    return 3;
  }
  else if ((x_distance > maxThird && x_distance < maxFourth) ) {
    return 4;
  }
  else if ((x_distance > maxFourth && x_distance <= maxFifth)) {
    return 5;
  }
  return 3;
}
bool isStackFull(int stackNum) {
  return tf_input==true && silo == targetSilo && LSA_input == true;
}

//Works
int changeTargetSilo(int target) {
  for (int offset = 1; offset <= NUM_STACKS; offset++) {
    int newTarget = (target + offset - 1) % NUM_STACKS + 1;
    if (!siloFullStatus[newTarget]) {
//      Serial.print("Target Silo Changed To: ");
//      Serial.println(newTarget);
      return newTarget;
    }
  }

//  Serial.println("All nearby silos are full.");
  return -1; // Indicate all stacks are full
}
