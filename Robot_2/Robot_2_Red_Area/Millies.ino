void Roller2(int rollerspeed, unsigned long duration) {
  if (!rollersRunning) {
    // If the rollers are not currently running, start them
    rollerStartTime = millis();
    rollersRunning = true;
    roller2.setSpeed(-rollerspeed1);
    roller1.setSpeed(rollerspeed2); // Assuming rollerspeed1 is defined elsewhere
//    Serial.println("Rollers Started");
  } else {
    // Calculate elapsed time since the start
    unsigned long elapsedTime = millis() - rollerStartTime;

    // Check if the duration has passed
    if (elapsedTime >= duration) {
      // If duration has passed, stop the rollers
      rollersRunning = false;
      rollerFlag = true;
      Rflag = false;
      rollerStartFlag = false;
      roller2.setSpeed(0);
      roller1.setSpeed(0);
      checkFlag = false;
//      Serial.println("Rollers Stopped");
    }
  }
}
void Roller(unsigned long duration2) {
  if (!rollersRunning) {
    // If the rollers are not currently running, start them
    rollerStartTime = millis();
    rollersRunning = true;
    roller2.setSpeed(-highSpeed);
    roller1.setSpeed(highSpeed); // Assuming rollerspeed1 is defined elsewhere
    //    Serial.println("Rollers Started");
  } else {
    // Calculate elapsed time since the start
    unsigned long elapsedTime = millis() - rollerStartTime;

    // Check if the duration has passed
    if (elapsedTime >= duration2) {
      // If duration has passed, stop the rollers
      rollersRunning = false;
      rollerStartFlag = false;
      ballFlag = true;
      roller2.setSpeed(0);
      roller1.setSpeed(0);
      //      Serial.println("Rollers Stopped");
    }
  }
}
void checkTime(unsigned long duration) {
  if (!isSignature) {
    // If the signature check is not currently running, start it
    checkingStartTime = millis();
    isSignature = true;
    Stop();
    signature_receive(Signature_pin1, Signature_pin2);
    Serial.println("Checking Started");

  } else {
    // Calculate elapsed time since the start
    unsigned long elapsedTime = millis() - checkingStartTime;

    // Check if the duration has passed
    if (elapsedTime >= duration) {
      // If duration has passed, end the signature check
      isSignature = false;
      CheckTimeFlag = false;
      checkFlag = true;
//      Serial.println("Checking Done");
    }
  }
}
void checkRflag() {
  if (Rflag == true && !RflagRunning) {
    // Start the timer if Rflag is 1 and timer is not already running
    RflagStartTime = millis();
    RflagRunning = true;
//    Serial.println("Rflag Timer Started");
  } else if (Rflag == true && RflagRunning) {
    // Check if 2 seconds (3000 milliseconds) have passed
    unsigned long elapsedTime = millis() - RflagStartTime;
    if (elapsedTime >= 3000) {
      // Reset Rflag after 3 seconds
      roller2.setSpeed(0);
      roller1.setSpeed(0);
      Rflag = false;
      ballFlag = false;
      anticlockwise(highSpeed);
      RflagRunning = false;
//      Serial.println("Rflag Timer Reset after 3 seconds");
    }
  } else if (Rflag == false && RflagRunning) {
    // Reset the timer if Rflag is set to 0 before 2 seconds
    RflagRunning = false;
    Serial.println("Rflag Timer Stopped");
  }
}
