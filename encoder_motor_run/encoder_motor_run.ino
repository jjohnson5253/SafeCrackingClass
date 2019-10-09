
//
// Authors: Not Thieving Duck Overlords
// Created 9/16/2019
// Last edit by Jake 10/8/2019
//
// Description: This code drives a motor through pwm and dir pins with an option menu
// and has a homing function that stores flag position in eeprom
//

#include <EEPROM.h>

//TODO:
// write setMotorSpeed function
// write isFlagDetected Function
// write stop motor function
// write homing function
// get user input for how many ticks away from 0
// convert ticks away to encoder detections
// while(tick<encoderDetections);
// stopMotor function

// address in EEPROM to store flag position
#define flagPosEepromAddr 1

// Fault Flag Pins for motor driver
int FF1Pin = 12;
int FF1Val = 1;
int FF2Pin = 13;
int FF2Val = 1;

int encPinA = 2;
int encStateA = 0;
int encPinB = 3;
int encStateB = 0;

const int QRD1114_PIN = A0; // photogate output voltage

// pin for pwm
int pwmPin = 6;

// pin for direction
int dirPin = 5;

// var to store incoming serial data
int incomingByte = 0;

// var to count encoder reads
volatile int encoderAReads = 0;

// var to calculate dist in turnTo function and stop encoder in interrupt
volatile int dist = 0;

void setup() {

  // setup serial port
  Serial.begin(9600);

  // print menu
  printMenu();

  // photogate pin
  pinMode(QRD1114_PIN, INPUT);

  pinMode(encPinA, INPUT_PULLUP);

  // set pwm pin as an output pin
  pinMode(pwmPin, OUTPUT);

  // setup direction pin
  pinMode(dirPin, OUTPUT);

  // setup flag pins on motor driver
  pinMode(FF1Pin, INPUT);
  pinMode(FF2Pin, INPUT);

  // blink LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // turn motor counter-clockwise
  digitalWrite(dirPin, HIGH);

  // setup interrupt
  attachInterrupt(digitalPinToInterrupt(encPinA), encoderISR, RISING);

}

void loop() {

  //////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// Code for GUI ////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  
  // read serial
  if (Serial.available() > 0) {

    // read the incoming byte:
    incomingByte = Serial.read();

    // read incoming command and perform
    switch (incomingByte) {
      case 49: // 1 (turn on motor)
        // write pwm pin to 150 (255 = 5v)
        analogWrite(pwmPin, 25);
        break;

      case 50: // 2 (turn off motor)
        // write pwm pin low (turn off)
        analogWrite(pwmPin, 0);
        break;

      case 51: // 3 (turn motor CW)
        analogWrite(pwmPin, 0); // turn off motor
        delay(1000); // wait
        digitalWrite(dirPin, HIGH); // turn motor counter clockwise
        analogWrite(pwmPin, 50); // turn motor back on
        break;

      case 52: // 4 (turn motor CCW)
        analogWrite(pwmPin, 0); // turn off motor
        delay(1000); // wait
        digitalWrite(dirPin, LOW); // turn motor clockwise
        analogWrite(pwmPin, 50); // turn motor back on
        break;

      case 53: // 5
        homing();
        //turnTo(25,"CW");
        break;

      case 54: // 6
        Serial.println();
        Serial.println("Flag Position stored in EEPROM: ");
        Serial.print(EEPROM.read(flagPosEepromAddr));
        break;
    }

    // reprint menu
    printMenu();

    ///////////////////////////////////////////////////////////////////////////////////////
  }
}
