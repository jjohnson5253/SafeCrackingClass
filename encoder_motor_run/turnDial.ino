void turnTo(int position, String dir) {

  // reset encoder ticks
  encoderAReads = 0;

  // calculate distance
  dist = position * 2100 / 100; // percentage of full rotation

  // turn motor off
  analogWrite(pwmPin, 0);

  // wait
  delay(1000);

  // start turning based off dir input
  if (dir == "CCW") {
    digitalWrite(dirPin, HIGH); // turn motor counter clockwise
  }
  else if (dir == "CW") {
    digitalWrite(dirPin, LOW); // turn motor clockwise
  }
  else {
    return; // exit function and don't do anything if no dir is selected
  }

  analogWrite(pwmPin, 50); // turn motor back on

  // the encoder ISR will handle turning off motor when turn to dist is reached

}
