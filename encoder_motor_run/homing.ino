#include <EEPROM.h>

void homing() {

  // turn motor off
  analogWrite(pwmPin, 0);

  // wait
  delay(1000);
  
  // turn motor on
  analogWrite(pwmPin, 50);

  // stores value of photogate as voltage
  float proximityV = 0;

  // wait for photo gate to detect flag
  while (proximityV < 2.5) {
    int proximityADC = analogRead(QRD1114_PIN);
    proximityV = (float)proximityADC * 5.0 / 1023.0;
  }

  // turn motor off
  analogWrite(pwmPin, 0);

  Serial.println();
  Serial.println("Where to turn? Enter digit 0-99");
    
  // wait for input
  while(!Serial.available()){}

  int turnToDigit = Serial.parseInt();

  Serial.println(turnToDigit);
  
  turnTo(turnToDigit, "CCW");

  // turnToDigit is where the flag is
  EEPROM.write(flagPosEepromAddr,turnToDigit);
}
