void readAndPrintMotorDriverFlags(){
  // read
  FF1Val = digitalRead(FF1Pin);
  FF2Val = digitalRead(FF2Pin);
  // print
  Serial.print("FF1 val: ");
  Serial.println(FF1Val,DEC);
  Serial.print("FF2 val: ");
  Serial.println(FF2Val,DEC);
}
