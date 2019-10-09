
// ISR for each encoder tick
// The function just increments a counter
void encoderISR() {

  // check if dist is reached
  if (dist != 0) {
    if (encoderAReads >= dist) {
      // turn motor off
      analogWrite(pwmPin, 0);
      // reset encoder ticks
      encoderAReads = 0;
      // reset distance
      dist = 0;
    }
  }
  encoderAReads++; // increment encoder ticks
}
