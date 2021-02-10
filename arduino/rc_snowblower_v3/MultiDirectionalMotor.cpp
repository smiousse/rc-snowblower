#include "Arduino.h"
#include "MultiDirectionalMotor.h"

MultiDirectionalMotor::MultiDirectionalMotor(String name, int motorLeftForwardPin, int motorLeftReversePin, int motorRightForwardPin, int motorRightReversePin, int motorRightSpeedPin, int motorLeftSpeedPin){

  _name = name;
  _motorLeftForwardPin = motorLeftForwardPin;
  _motorLeftReversePin = motorLeftReversePin;
  _motorRightForwardPin = motorRightForwardPin;
  _motorRightReversePin = motorRightReversePin;
  _motorRightSpeedPin = motorRightSpeedPin;
  _motorLeftSpeedPin = motorLeftSpeedPin;

}

void MultiDirectionalMotor::init(){
  pinMode(_motorLeftForwardPin, OUTPUT);
  pinMode(_motorLeftReversePin, OUTPUT);
  pinMode(_motorRightForwardPin, OUTPUT);
  pinMode(_motorRightReversePin, OUTPUT);
  pinMode(_motorRightSpeedPin, OUTPUT);
  pinMode(_motorLeftSpeedPin, OUTPUT);
}

void MultiDirectionalMotor::forward(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);
}

void MultiDirectionalMotor::reverse(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);
}

void MultiDirectionalMotor::fullLeft(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);
}

void MultiDirectionalMotor::fullRight(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);
}

void MultiDirectionalMotor::forwardLeft(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);
}

void MultiDirectionalMotor::forwardRight(){
  digitalWrite(_motorLeftForwardPin,HIGH);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,HIGH);
  digitalWrite(_motorRightReversePin,LOW);
}

void MultiDirectionalMotor::reverseLeft(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);
}

void MultiDirectionalMotor::reverseRight(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,HIGH);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,HIGH);
}

void MultiDirectionalMotor::stop(){
  digitalWrite(_motorLeftForwardPin,LOW);
  digitalWrite(_motorLeftReversePin,LOW);
  digitalWrite(_motorRightForwardPin,LOW);
  digitalWrite(_motorRightReversePin,LOW);
}

void MultiDirectionalMotor::_debug(String debugValue){

}
